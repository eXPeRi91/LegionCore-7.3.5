/*
* Copyright (C) 2024 SoulSeekkor <https://www.soulseekkor.com>
* Copyright (C) 2012 CVMagic <http://www.trinitycore.org/f/topic/6551-vas-autobalance/>
* Copyright (C) 2008-2010 TrinityCore <http://www.trinitycore.org/>
* Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
* Copyright (C) 1985-2010 {VAS} KalCorp  <http://vasserver.dyndns.org/>
*
* This file is part of the TrinityCore Project. See AUTHORS file for Copyright information
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 2 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along
* with this program. If not, see <http://www.gnu.org/licenses/>.
* Script Name: DungeonBalance
* Original Authors: SoulSeekkor (based on KalCorp and Vaughner's work)
* Maintainer(s): SoulSeekkor
* Description: This script is intended to scale damage received and dealt based on number of players.  Nothing more, nothing less.
*              This used AutoBalance as a template to make a simpler version for LegionCore, those authors deserve the real credit!
*
*/

#include "Chat.h"
#include "Configuration/Config.h"
#include "Log.h"
#include "Map.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "SpellInfo.h"
#include "Unit.h"
#include "World.h"

static bool enabled, announce, playerChangeNotify, dungeonScaleDownXP;

class DungeonBalance_Helpers
{
public:
    static bool IsGarrisonMap(Map* map)
    {
        bool garrison = false;

        switch (map->GetId())
        {
            case 1158:  // Alliance Lvl 1
            case 1331:  // Alliance Lvl 2
            case 1159:  // Alliance Lvl 3
            case 1473:  // Alliance Shipyard
            case 1482:  // Alliance Shipyard - Submarine
            case 1483:  // Alliance Shipyard - Destroyer
            case 1485:  // Alliance Shipyard - Battleship
            case 1496:  // Alliance Shipyard - Carrier
            case 1152:  // Horde Lvl 1
            case 1330:  // Horde Lvl 2
            case 1153:  // Horde Lvl 3
            case 1474:  // Horde Shipyard
            case 1486:  // Horde Shipyard - Carrier
            case 1487:  // Horde Shipyard - Submarine
            case 1488:  // Horde Shipyard - Destroyer
            case 1497:  // Horde Shipyard - Battleship
                garrison = true;
                break;
            default: break;
        }

        return garrison;
    }
};

class DungeonBalance_WorldScript : public WorldScript
{
public:
    DungeonBalance_WorldScript() : WorldScript("DungeonBalance_WorldScript") {}

    void OnConfigLoad(bool /*reload*/) override
    {
        Initialize();
    }

    void Initialize()
    {
        enabled = sConfigMgr->GetBoolDefault("DungeonBalance.Enable", 0);
        announce = enabled && sConfigMgr->GetBoolDefault("DungeonBalance.Announce", 1);
        playerChangeNotify = sConfigMgr->GetBoolDefault("DungeonBalance.PlayerChangeNotify", 1);
        dungeonScaleDownXP = sConfigMgr->GetBoolDefault("DungeonBalance.DungeonScaleDownXP", 1);
    }
};

class DungeonBalance_PlayerScript : public PlayerScript
{
public:
    DungeonBalance_PlayerScript() : PlayerScript("DungeonBalance_PlayerScript") { }

    void OnLogin(Player* Player, bool /*firstLogin*/) override
    {
        if (announce)
            ChatHandler(Player->GetSession()).SendSysMessage("This server is running the |cff4CFF00DungeonBalance |rmodule.");
    }

    void OnGiveXP(Player* player, uint32& amount, Unit* victim) override
    {
        if (dungeonScaleDownXP && player && victim)
        {
            Map* map = player->GetMap();

            if ((map->IsDungeon() || map->IsRaidOrHeroicDungeon()) && !DungeonBalance_Helpers::IsGarrisonMap(player->GetMap()))
            {
                TC_LOG_INFO(LOG_FILTER_DUNGEONBALANCE, "[DB - %s] Prospective incoming XP of %u from killing %s.", player->GetName(), amount, victim->GetName());

                uint16 maxPlayerCount = map->GetMapMaxPlayers();

                if (maxPlayerCount == 10 || maxPlayerCount == 0)
                    maxPlayerCount = 5;

                uint32 playerCount = map->GetPlayerCount();

                // Adjust so that 1 or 2 player is not a ridiculous way to get XP
                if (playerCount == 1)
                    maxPlayerCount = 15;
                else if (playerCount == 2)
                    maxPlayerCount = 10;

                float xpMult = float(playerCount) / float(maxPlayerCount);
                uint32 newAmount = uint32(amount * xpMult);
                
                if (victim)
                {
                    if (xpMult == 1)
                        TC_LOG_INFO(LOG_FILTER_DUNGEONBALANCE, "[DB - %s] XP amount of %u unchanged (%.3f multiplier) for killing %s.", player->GetName(), amount, xpMult, victim->GetName());
                    else
                        TC_LOG_INFO(LOG_FILTER_DUNGEONBALANCE, "[DB - %s] XP reduced from %u to %u (%.3f multiplier) for killing %s.", player->GetName(), amount, newAmount, xpMult, victim->GetName());
                }
                else
                {
                    if (xpMult == 1)
                        TC_LOG_INFO(LOG_FILTER_DUNGEONBALANCE, "[DB - %s] XP amount of %u unchanged (%.3f multiplier).", player->GetName(), amount, xpMult);
                    else
                        TC_LOG_INFO(LOG_FILTER_DUNGEONBALANCE, "[DB - %s] XP reduced from %u to %u (%.3f multiplier).", player->GetName(), amount, newAmount, xpMult);
                }

                amount = uint32(amount * xpMult);
            }
        }
    }
};

class DungeonBalance_UnitScript : public UnitScript {
public:
    DungeonBalance_UnitScript() : UnitScript("DungeonBalance_UnitScript") { }

    void ModifyPeriodicDamageAurasTick(Unit* target, Unit* attacker, float& damage, SpellInfo const* spellInfo) override
    {
        uint32 convertedDamage = static_cast<uint32>(damage);
        convertedDamage = _Modifier_DealDamage(target, attacker, damage, false, "periodic damage");
        damage = static_cast<float>(convertedDamage);
    }

    void ModifySpellDamageTaken(Unit* target, Unit* attacker, float& damage, SpellInfo const* spellInfo) override
    {
        uint32 convertedDamage = static_cast<uint32>(damage);
        convertedDamage = _Modifier_DealDamage(target, attacker, convertedDamage, false, "spell damage");
        damage = static_cast<float>(convertedDamage);
    }

    void ModifyMeleeDamage(Unit* target, Unit* attacker, uint32& damage) override
    {
        damage = _Modifier_DealDamage(target, attacker, damage, false, "melee damage");
    }

    void ModifyHealReceived(Unit* target, Unit* attacker, float& amount, SpellInfo const* spellInfo) override
    {
        uint32 convertedAmount = static_cast<uint32>(amount);
        convertedAmount = _Modifier_DealDamage(target, attacker, convertedAmount, true, "heal");
        amount = static_cast<float>(convertedAmount);
    }

    uint32 _Modifier_DealDamage(Unit* target, Unit* attacker, uint32 damage, bool heal, std::string type)
    {
        if (!enabled || !attacker || !attacker->IsInWorld() || !(attacker->GetMap()->IsDungeon() || attacker->GetMap()->IsRaidOrHeroicDungeon()) || DungeonBalance_Helpers::IsGarrisonMap(attacker->GetMap()))
            return damage;

        int8 maxPlayerCount = attacker->GetMap()->GetMapMaxPlayers();
        float playerCount = attacker->GetMap()->GetPlayerCount();

        //TC_LOG_INFO(LOG_FILTER_DUNGEONBALANCE, "Initial maxPlayerCount is %u.", maxPlayerCount);

        if (maxPlayerCount == 10 || maxPlayerCount == 0)
            maxPlayerCount = 5;

        if (playerCount == 1)
        {
            switch (maxPlayerCount)
            {
                case 5:
                    playerCount = 0.5f;
                    break;
                default:
                    playerCount = 0.25f;
            }
        }
        else if (playerCount == 2 && maxPlayerCount == 5)
            playerCount = .75f;
        else if (playerCount >= (maxPlayerCount * .75) && playerCount <= (maxPlayerCount * .9))
            playerCount = maxPlayerCount * .9;

        if ((attacker->IsPlayer() && (!target->IsPlayer() || heal)) || (attacker->IsControlledByPlayer() && (attacker->isHunterPet() || attacker->isPet() || attacker->isSummon())))
        {
            // Player
            std::string actionTaken;
            if (damage < static_cast<uint32>(damage * float(maxPlayerCount / playerCount)))
                actionTaken = "increased";
            else
                actionTaken = "decreased";

            TC_LOG_INFO(LOG_FILTER_DUNGEONBALANCE, "[DB - %s] Player %s to %s %s from % u to % u(player count of % .2f was used).", attacker->GetName(), type, target->GetName(), actionTaken, damage, static_cast<uint32>(damage * float(maxPlayerCount / playerCount)), playerCount);

            return static_cast<uint32>(damage * float(maxPlayerCount / playerCount));
        }
        else
        {
            // Enemy
            std::string actionTaken;
            if (damage < static_cast<uint32>(damage * float(playerCount / maxPlayerCount)))
                actionTaken = "increased";
            else
                actionTaken = "decreased";

            TC_LOG_INFO(LOG_FILTER_DUNGEONBALANCE, "[DB - %s] Enemy %s to %s %s from %u to %u (player count of %.2f was used).", attacker->GetName(), type, target->GetName(), actionTaken, damage, static_cast<uint32>(damage * float(playerCount / maxPlayerCount)), playerCount);

            return static_cast<uint32>(damage * float(playerCount / maxPlayerCount));
        }
    }
};

class DungeonBalance_AllMapScript : public AllMapScript
{
public:
    DungeonBalance_AllMapScript() : AllMapScript("DungeonBalance_AllMapScript") { }

    void OnPlayerEnterAll(Map* map, Player* player)
    {
        if (!enabled || !playerChangeNotify || !map || !player || !(map->IsDungeon() || map->IsRaidOrHeroicDungeon()) || DungeonBalance_Helpers::IsGarrisonMap(map))
            return;

        Map::PlayerList const& playerList = map->GetPlayers();
        if (!playerList.isEmpty())
        {
            for (Map::PlayerList::const_iterator playerIteration = playerList.begin(); playerIteration != playerList.end(); ++playerIteration)
            {
                if (Player* playerHandle = playerIteration->getSource())
                {
                    ChatHandler chatHandle = ChatHandler(playerHandle->GetSession());
                    chatHandle.PSendSysMessage("|cffFF0000 [DungeonBalance]|r|cffFF8000 %s entered the Instance %s. Auto setting player count to %u |r",
                        player->GetName(), map->GetMapName(), map->GetPlayerCount());
                }
            }
        }
    }

    void OnPlayerLeaveAll(Map* map, Player* player)
    {
        if (!enabled || !playerChangeNotify || !player || !(map->IsDungeon() || map->IsRaidOrHeroicDungeon()) || DungeonBalance_Helpers::IsGarrisonMap(map))
            return;

        Map::PlayerList const& playerList = map->GetPlayers();
        if (!playerList.isEmpty())
        {
            for (Map::PlayerList::const_iterator playerIteration = playerList.begin(); playerIteration != playerList.end(); ++playerIteration)
            {
                if (Player* playerHandle = playerIteration->getSource())
                {
                    ChatHandler chatHandle = ChatHandler(playerHandle->GetSession());
                    chatHandle.PSendSysMessage("|cffFF0000 [-DungeonBalance]|r|cffFF8000 %s left the Instance %s. Auto setting player count to %u |r",
                        player->GetName(), map->GetMapName(), map->GetPlayerCount());
                }
            }
        }
    }

};

void AddSC_DungeonBalance()
{
    new DungeonBalance_WorldScript;
    new DungeonBalance_PlayerScript;
    new DungeonBalance_UnitScript;
    new DungeonBalance_AllMapScript;
}