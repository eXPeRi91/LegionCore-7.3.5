/*
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
* Script Name: AutoBalance
* Original Authors: KalCorp and Vaughner
* Maintainer(s): CVMagic
* Original Script Name: VAS.AutoBalance
* Description: This script is intended to scale based on number of players, instance mobs & world bosses' health, mana, and damage.
*
* Touched up by SPP MDic for Trinitycore Custom Changes Branch
* Touched up again by SoulSeekkor for LegionCore
*/

#include "Configuration/Config.h"
#include "Unit.h"
#include "Chat.h"
#include "Creature.h"
#include "Player.h"
#include "ObjectMgr.h"
#include "MapManager.h"
#include "World.h"
#include "LFGMgr.h"
#include "Log.h"
#include "Map.h"
#include "ScriptMgr.h"
#include "Language.h"
#include <vector>
#include "Log.h"
#include "Group.h"
#include "DataMap.h"
#include "DB2Stores.h"

class AutoBalanceCreatureInfo : public DataMap::Base {
public:
    AutoBalanceCreatureInfo() {}

    AutoBalanceCreatureInfo(uint32 count, float dmg, float hpRate, float manaRate, float armorRate, uint8 selLevel) :
        instancePlayerCount(count), selectedLevel(selLevel), DamageMultiplier(dmg), HealthMultiplier(hpRate), ManaMultiplier(manaRate),
        ArmorMultiplier(armorRate) {}

    uint32 instancePlayerCount = 0;
    uint8 selectedLevel = 0;
    // this is used to detect creatures that update their entry
    uint32 entry = 0;
    float DamageMultiplier = 1;
    float HealthMultiplier = 1;
    float ManaMultiplier = 1;
    float ArmorMultiplier = 1;

};

class AutoBalanceMapInfo : public DataMap::Base {
public:
    AutoBalanceMapInfo() {}

    AutoBalanceMapInfo(uint32 count, uint8 selLevel) : playerCount(count) {}

    uint32 playerCount = 0;
};

// The map values correspond with the .AutoBalance.XX.Name entries in the configuration file.
static std::map<int, int> forcedCreatureIds;
static int8 PlayerCountDifficultyOffset;
static bool enabled, announce, LevelEndGameBoost, PlayerChangeNotify, DungeonScaleDownXP;
static float globalRate, healthMultiplier, manaMultiplier, armorMultiplier, damageMultiplier, MinHPModifier, MinManaModifier, MinDamageModifier,
    InflectionPoint, InflectionPointRaid, InflectionPointRaid10M, InflectionPointRaid25M, InflectionPointRaid30M, InflectionPointHeroic, InflectionPointRaidHeroic,
    InflectionPointRaid10MHeroic, InflectionPointRaid25MHeroic, InflectionPointRaid30MHeroic, BossInflectionMult;

// Used for reading the string from the configuration file to for those creatures who need to be scaled for XX number of players.
void LoadForcedCreatureIdsFromString(std::string creatureIds, int forcedPlayerCount) {
    std::string delimitedValue;
    std::stringstream creatureIdsStream;

    creatureIdsStream.str(creatureIds);
    // Process each Creature ID in the string, delimited by the comma - ","
    while (std::getline(creatureIdsStream, delimitedValue, ','))
    {
        int creatureId = atoi(delimitedValue.c_str());
        if (creatureId >= 0)
        {
            forcedCreatureIds[creatureId] = forcedPlayerCount;
        }
    }
}

class AutoBalance_WorldScript : public WorldScript
{
public:
    AutoBalance_WorldScript() : WorldScript("AutoBalance_WorldScript") {}

    void OnConfigLoad(bool /*reload*/) override
    {
        SetInitialWorldSettings();
    }

    void OnStartup() override { }

    void SetInitialWorldSettings() override
    {
        forcedCreatureIds.clear();
        LoadForcedCreatureIdsFromString(sConfigMgr->GetStringDefault("AutoBalance.ForcedID40", ""), 40);
        LoadForcedCreatureIdsFromString(sConfigMgr->GetStringDefault("AutoBalance.ForcedID25", ""), 25);
        LoadForcedCreatureIdsFromString(sConfigMgr->GetStringDefault("AutoBalance.ForcedID10", ""), 10);
        LoadForcedCreatureIdsFromString(sConfigMgr->GetStringDefault("AutoBalance.ForcedID5", ""), 5);
        LoadForcedCreatureIdsFromString(sConfigMgr->GetStringDefault("AutoBalance.ForcedID2", ""), 2);
        LoadForcedCreatureIdsFromString(sConfigMgr->GetStringDefault("AutoBalance.DisabledID", ""), 0);

        enabled = sConfigMgr->GetBoolDefault("AutoBalance.enable", 0);
        announce = enabled && sConfigMgr->GetBoolDefault("AutoBalanceAnnounce.enable", 1);
        LevelEndGameBoost = sConfigMgr->GetBoolDefault("AutoBalance.LevelEndGameBoost", 1);
        PlayerChangeNotify = sConfigMgr->GetBoolDefault("AutoBalance.PlayerChangeNotify", 1);
        DungeonScaleDownXP = sConfigMgr->GetBoolDefault("AutoBalance.DungeonScaleDownXP", 1);

        PlayerCountDifficultyOffset = sConfigMgr->GetIntDefault("AutoBalance.playerCountDifficultyOffset", 0);

        InflectionPoint = sConfigMgr->GetFloatDefault("AutoBalance.InflectionPoint", 0.5f);
        InflectionPointRaid = sConfigMgr->GetFloatDefault("AutoBalance.InflectionPointRaid", InflectionPoint);
        InflectionPointRaid30M = sConfigMgr->GetFloatDefault("AutoBalance.InflectionPointRaid30M", InflectionPointRaid);
        InflectionPointRaid25M = sConfigMgr->GetFloatDefault("AutoBalance.InflectionPointRaid25M", InflectionPointRaid);
        InflectionPointRaid10M = sConfigMgr->GetFloatDefault("AutoBalance.InflectionPointRaid10M", InflectionPointRaid);
        InflectionPointHeroic = sConfigMgr->GetFloatDefault("AutoBalance.InflectionPointHeroic", InflectionPoint);
        InflectionPointRaidHeroic = sConfigMgr->GetFloatDefault("AutoBalance.InflectionPointRaidHeroic", InflectionPointRaid);
        InflectionPointRaid30MHeroic = sConfigMgr->GetFloatDefault("AutoBalance.InflectionPointRaid30MHeroic", InflectionPointRaid30M);
        InflectionPointRaid25MHeroic = sConfigMgr->GetFloatDefault("AutoBalance.InflectionPointRaid25MHeroic", InflectionPointRaid25M);
        InflectionPointRaid10MHeroic = sConfigMgr->GetFloatDefault("AutoBalance.InflectionPointRaid10MHeroic", InflectionPointRaid10M);
        BossInflectionMult = sConfigMgr->GetFloatDefault("AutoBalance.BossInflectionMult", 1.0f);
        globalRate = sConfigMgr->GetFloatDefault("AutoBalance.rate.global", 1.0f);
        healthMultiplier = sConfigMgr->GetFloatDefault("AutoBalance.rate.health", 1.0f);
        manaMultiplier = sConfigMgr->GetFloatDefault("AutoBalance.rate.mana", 1.0f);
        armorMultiplier = sConfigMgr->GetFloatDefault("AutoBalance.rate.armor", 1.0f);
        damageMultiplier = sConfigMgr->GetFloatDefault("AutoBalance.rate.damage", 1.0f);
        MinHPModifier = sConfigMgr->GetFloatDefault("AutoBalance.MinHPModifier", 0.1f);
        MinManaModifier = sConfigMgr->GetFloatDefault("AutoBalance.MinManaModifier", 0.1f);
        MinDamageModifier = sConfigMgr->GetFloatDefault("AutoBalance.MinDamageModifier", 0.1f);
    }
};

class AutoBalance_PlayerScript : public PlayerScript
{
public:
    AutoBalance_PlayerScript() : PlayerScript("AutoBalance_PlayerScript") { }

    void OnLogin(Player* Player, bool /*firstLogin*/) override
    {
        if (announce)
        {
            ChatHandler(Player->GetSession()).SendSysMessage("This server is running the |cff4CFF00AutoBalance |rmodule.");
        }
    }

    void OnGiveXP(Player* player, uint32& amount, Unit* victim) override
    {
        TC_LOG_INFO(LOG_FILTER_AUTOBALANCE, "Incoming XP of %u for player %s from killing %s.", amount, player->GetName(), victim->GetName());

        if (DungeonScaleDownXP && player)
        {
            Map* map = player->GetMap();
            
            if (map->IsDungeon())
            {
                float xpMult = float(map->GetPlayerCount()) / float(map->GetMapMaxPlayers());
                uint32 newAmount = uint32(amount * xpMult);
                
                if (victim)
                    TC_LOG_INFO(LOG_FILTER_AUTOBALANCE, "XP for player %s reduced from %u to %u (%.3f multiplier) for killing %s.", player->GetName(), amount, newAmount, xpMult, victim->GetName());

                amount = uint32(amount * xpMult);
            }
        }
    }
};

class AutoBalance_UnitScript : public UnitScript {
public:
    AutoBalance_UnitScript() : UnitScript("AutoBalance_UnitScript") { }

    //    uint32 DealDamage(Unit *AttackerUnit, Unit *playerVictim, uint32 damage, DamageEffectType /*damagetype*/) {
    //        return _Modifier_DealDamage(playerVictim, AttackerUnit, damage);
    //    }

    void ModifyPeriodicDamageAurasTick(Unit* target, Unit* attacker, uint32& damage) override
    {
        damage = _Modifier_DealDamage(target, attacker, damage);
    }

    void ModifySpellDamageTaken(Unit* target, Unit* attacker, float& damage) override
    {
        uint32 convertedDamage = static_cast<uint32>(damage);
        convertedDamage = _Modifier_DealDamage(target, attacker, convertedDamage);
        damage = static_cast<float>(convertedDamage);
    }

    void ModifyMeleeDamage(Unit* target, Unit* attacker, uint32& damage) override
    {
        damage = _Modifier_DealDamage(target, attacker, damage);
    }

    void ModifyHealReceived(Unit* target, Unit* attacker, uint32& amount) override
    {
        amount = _Modifier_DealDamage(target, attacker, amount);
    }

    uint32 _Modifier_DealDamage(Unit* target, Unit* attacker, uint32 damage)
    {
        if (!enabled || !attacker || !attacker->IsInWorld() || !attacker->GetMap()->IsDungeon())
        {
            return damage;
        }

        int8 maxPlayerCount = attacker->GetMap()->GetMapMaxPlayers();
        float playerCount = attacker->GetMap()->GetPlayerCount();

        if (playerCount == 1)
        {
            switch (maxPlayerCount)
            {
                case 5:
                    playerCount = 0.5f;
                    break;
                default:
                    playerCount = 0.15f;
            }
        }
        else if (playerCount == 2 && maxPlayerCount == 5)
            playerCount = 1.5f;
        else if (playerCount == (maxPlayerCount * .75))
            playerCount = maxPlayerCount * .85;

        if (attacker->IsPlayer() || (attacker->IsControlledByPlayer() && (attacker->isHunterPet() || attacker->isPet() || attacker->isSummon())))
        {
            // Player
            TC_LOG_INFO(LOG_FILTER_AUTOBALANCE, "Damage dealt by %s updated for %s from %u to %u.", attacker->GetName(), target->GetName(), damage, (int)(damage * float(maxPlayerCount / playerCount)));

            return damage * float(maxPlayerCount / playerCount);
        }
        else
        {
            // Enemy
            TC_LOG_INFO(LOG_FILTER_AUTOBALANCE, "Damage dealt by %s updated for %s from %u to %u.", attacker->GetName(), target->GetName(), damage, (int)(damage * float(playerCount / maxPlayerCount)));

            return damage * float(playerCount / maxPlayerCount);
        }
    }
};

class AutoBalance_AllMapScript : public AllMapScript
{
public:
    AutoBalance_AllMapScript() : AllMapScript("AutoBalance_AllMapScript") { }

    void OnPlayerEnterAll(Map* map, Player* player)
    {
        if (!enabled || !map->IsDungeon())
        {
            return;
        }

        if (PlayerChangeNotify && player)
        {
            Map::PlayerList const& playerList = map->GetPlayers();
            if (!playerList.isEmpty())
            {
                for (Map::PlayerList::const_iterator playerIteration = playerList.begin(); playerIteration != playerList.end(); ++playerIteration)
                {
                    if (Player* playerHandle = playerIteration->getSource())
                    {
                        ChatHandler chatHandle = ChatHandler(playerHandle->GetSession());
                        chatHandle.PSendSysMessage("|cffFF0000 [AutoBalance]|r|cffFF8000 %s entered the Instance %s. Auto setting player count to %u |r",
                            player->GetName(), map->GetMapName(), map->GetPlayerCount());
                    }
                }
            }
        }
    }

    void OnPlayerLeaveAll(Map* map, Player* player)
    {
        if (!enabled || !map->IsDungeon())
        {
            return;
        }

        if (PlayerChangeNotify && player)
        {
            Map::PlayerList const& playerList = map->GetPlayers();
            if (!playerList.isEmpty())
            {
                for (Map::PlayerList::const_iterator playerIteration = playerList.begin(); playerIteration != playerList.end(); ++playerIteration)
                {
                    if (Player* playerHandle = playerIteration->getSource())
                    {
                        ChatHandler chatHandle = ChatHandler(playerHandle->GetSession());
                        chatHandle.PSendSysMessage("|cffFF0000 [-AutoBalance]|r|cffFF8000 %s left the Instance %s. Auto setting player count to %u |r",
                            player->GetName(), map->GetMapName(), map->GetPlayerCount());
                    }
                }
            }
        }
    }
};

class AutoBalance_AllCreatureScript : public AllCreatureScript {
public:
    AutoBalance_AllCreatureScript() : AllCreatureScript("AutoBalance_AllCreatureScript") { }

    void Creature_SelectLevel(const CreatureTemplate* /*creatureTemplate*/, Creature* creature) override
    {
        ModifyCreatureAttributes(creature, true);
    }

    void OnAllCreatureUpdate(Creature* creature, uint32 /*diff*/) override
    {
        ModifyCreatureAttributes(creature);
    }

    void ModifyCreatureAttributes(Creature* creature, bool resetSelLevel = false)
    {
        return;

        if (!enabled || !creature || !creature->GetMap() || !creature->GetMap()->IsDungeon())
        {
            return;
        }

        if (creature->IsControlledByPlayer() && (creature->isHunterPet() || creature->isPet() || creature->isSummon()))
        {
            return;
        }

        // avoid stats changing for critters and dead creatures
        if (creature->getLevel() <= 5 || !creature->isAlive())
        {
            return;
        }

        AutoBalanceMapInfo* mapABInfo = creature->GetMap()->CustomData.GetDefault<AutoBalanceMapInfo>("AutoBalanceMapInfo");

        CreatureTemplate const* creatureTemplate = creature->GetCreatureTemplate();
        InstanceMap* instanceMap = ((InstanceMap*)sMapMgr->FindMap(creature->GetMapId(), creature->GetInstanceId()));
        uint32 maxNumberOfPlayers = instanceMap->GetMaxPlayers();

        AutoBalanceCreatureInfo* creatureABInfo = creature->CustomData.GetDefault<AutoBalanceCreatureInfo>("AutoBalanceCreatureInfo");
        // force resetting selected level.
        // this is also a "workaround" to fix bug of not recalculated
        // attributes when UpdateEntry has been used.
        // TODO: It's better and faster to implement a core hook
        // in that position and force a recalculation then
        if ((creatureABInfo->entry != 0 && creatureABInfo->entry != creature->GetEntry()) || resetSelLevel)
        {
            // force a recalculation
            creatureABInfo->selectedLevel = 0;
        }

        uint32 curCount = mapABInfo->playerCount + PlayerCountDifficultyOffset;

        // already scaled
        if (creatureABInfo->selectedLevel > 0)
        {
            if (creatureABInfo->instancePlayerCount == curCount)
            {
                return;
            }
        }

        creatureABInfo->instancePlayerCount = curCount;
        // no players in map, do not modify attributes
        if (!creatureABInfo->instancePlayerCount)
        {
            return;
        }

        creatureABInfo->selectedLevel = creature->getLevel();

        //CreatureBaseStats const* origCreatureStats = sObjectMgr->GetCreatureBaseStats(originalLevel, creatureTemplate->unit_class);
        //CreatureBaseStats const* creatureStats = sObjectMgr->GetCreatureBaseStats(creatureABInfo->selectedLevel, creatureTemplate->unit_class);

        //uint32 baseHealth = origCreatureStats->GenerateHealth(creatureTemplate);
        //uint32 baseMana = origCreatureStats->GenerateMana(creatureTemplate);
        //uint32 scaledHealth = 0;
        //uint32 scaledMana = 0;

        //// Note: InflectionPoint handle the number of players required to get 50% health.
        ////       you'd adjust this to raise or lower the hp modifier for per additional player in a non-whole group.
        ////
        ////       diff modify the rate of percentage increase between
        ////       number of players. Generally the closer to the value of 1 you have this
        ////       the less gradual the rate will be. For example in a 5 man it would take 3
        ////       total players to face a mob at full health.
        ////
        ////       The +1 and /2 values raise the TanH function to a positive range and make
        ////       sure the modifier never goes above the value or 1.0 or below 0.
        ////
        //float defaultMultiplier = 1.0f;
        //if (creatureABInfo->instancePlayerCount < maxNumberOfPlayers)
        //{
        //    float inflectionValue = (float)maxNumberOfPlayers;

        //    if (instanceMap->IsHeroic())
        //    {
        //        if (instanceMap->IsRaid())
        //        {
        //            switch (instanceMap->GetMaxPlayers())
        //            {
        //            case 10:
        //                inflectionValue *= InflectionPointRaid10MHeroic;
        //                break;
        //            case 25:
        //                inflectionValue *= InflectionPointRaid25MHeroic;
        //                break;
        //            case 30:
        //                inflectionValue *= InflectionPointRaid30MHeroic;
        //                break;
        //            default:
        //                inflectionValue *= InflectionPointRaidHeroic;
        //            }
        //        }
        //        else
        //        {
        //            inflectionValue *= InflectionPointHeroic;
        //        }
        //    }
        //    else
        //    {
        //        if (instanceMap->IsRaid())
        //        {
        //            switch (instanceMap->GetMaxPlayers())
        //            {
        //            case 10:
        //                inflectionValue *= InflectionPointRaid10M;
        //                break;
        //            case 25:
        //                inflectionValue *= InflectionPointRaid25M;
        //                break;
        //            case 30:
        //                inflectionValue *= InflectionPointRaid30M;
        //                break;
        //            default:
        //                inflectionValue *= InflectionPointRaid;

        //            }
        //        }
        //        else
        //        {
        //            inflectionValue *= InflectionPoint;
        //        }
        //    }
        //    if (creature->IsDungeonBoss())
        //    {
        //        inflectionValue *= BossInflectionMult;
        //    }

        //    float diff = ((float)maxNumberOfPlayers / 5) * 1.5f;
        //    defaultMultiplier = (tanh(((float)creatureABInfo->instancePlayerCount - inflectionValue) / diff) + 1.0f) / 2.0f;
        //}

        //creatureABInfo->HealthMultiplier = healthMultiplier * defaultMultiplier * globalRate;

        //if (creatureABInfo->HealthMultiplier <= MinHPModifier)
        //{
        //    creatureABInfo->HealthMultiplier = MinHPModifier;
        //}

        //float hpStatsRate = 1.0f;

        //creatureABInfo->HealthMultiplier *= hpStatsRate;
        //scaledHealth = round(((float)baseHealth * creatureABInfo->HealthMultiplier) + 1.0f);

        //// Getting the list of Classes in this group
        //// This will be used later on to determine what additional scaling will be required based on the ratio of tank/dps/healer
        //// Update playerClassList with the list of all the participating Classes
        //// GetPlayerClassList(creature, playerClassList);

        //float manaStatsRate = 1.0f;

        //creatureABInfo->ManaMultiplier = manaStatsRate * manaMultiplier * defaultMultiplier * globalRate;
        //if (creatureABInfo->ManaMultiplier <= MinManaModifier)
        //{
        //    creatureABInfo->ManaMultiplier = MinManaModifier;
        //}

        //scaledMana = round(baseMana * creatureABInfo->ManaMultiplier);
        //float damageMul = defaultMultiplier * globalRate * damageMultiplier;
        //// Can not be less then Min_D_Mod
        //if (damageMul <= MinDamageModifier)
        //{
        //    damageMul = MinDamageModifier;
        //}

        //creatureABInfo->ArmorMultiplier = defaultMultiplier * globalRate * armorMultiplier;
        //uint32 newBaseArmor = round(creatureABInfo->ArmorMultiplier *
        //    (skipLevel ? origCreatureStats->GenerateArmor(creatureTemplate) : creatureStats->GenerateArmor(creatureTemplate)));
        //uint32 prevMaxHealth = creature->GetMaxHealth();
        //uint32 prevMaxPower = creature->GetMaxPower(POWER_MANA);
        //uint32 prevHealth = creature->GetHealth();
        //uint32 prevPower = creature->GetPower(POWER_MANA);
        //Powers pType = creature->getPowerType();

        //creature->SetArmor(newBaseArmor);
        //creature->SetStatFlatModifier(UNIT_MOD_ARMOR, FLAT_BASE_VALUE, (float)newBaseArmor);
        //creature->SetCreateHealth(scaledHealth);
        //creature->SetMaxHealth(scaledHealth);
        //creature->ResetPlayerDamageReq();
        //creature->SetCreateMana(scaledMana);
        //creature->SetMaxPower(POWER_MANA, scaledMana);
        //creature->SetStatFlatModifier(UNIT_MOD_ENERGY, FLAT_BASE_VALUE, (float)100.0f);
        //creature->SetStatFlatModifier(UNIT_MOD_RAGE, FLAT_BASE_VALUE, (float)100.0f);
        //creature->SetStatFlatModifier(UNIT_MOD_HEALTH, FLAT_BASE_VALUE, (float)scaledHealth);
        //creature->SetStatFlatModifier(UNIT_MOD_MANA, FLAT_BASE_VALUE, (float)scaledMana);
        //creatureABInfo->DamageMultiplier = damageMul;

        //uint32 scaledCurHealth = prevHealth && prevMaxHealth ? float(scaledHealth) / float(prevMaxHealth) * float(prevHealth) : 0;
        //uint32 scaledCurPower = prevPower && prevMaxPower ? float(scaledMana) / float(prevMaxPower) * float(prevPower) : 0;

        //creature->SetHealth(scaledCurHealth);
        //if (pType == POWER_MANA)
        //{
        //    creature->SetPower(POWER_MANA, scaledCurPower);
        //}
        //else
        //{
        //    // fix creatures with different power types
        //    creature->setPowerType(pType);
        //}
        
        float playerMultiplier = (float)curCount / (float)instanceMap->GetMaxPlayers();

        uint32 prevMaxHealth = creature->GetMaxHealth();
        uint32 prevMaxPower = creature->GetMaxPower(Powers::POWER_MANA);
        uint32 prevHealth = creature->GetHealth();
        uint32 prevPower = creature->GetPower(Powers::POWER_MANA);

        uint32 prevCreateHealth = creature->GetCreateHealth();

        // armor
        float armorMult = globalRate * armorMultiplier * playerMultiplier;

        uint32 prevArmor = creature->GetArmor();
        uint32 armor = round(armorMult * (float)prevArmor);

        creature->SetArmor(armor);
        creature->SetModifierValue(UNIT_MOD_ARMOR, BASE_VALUE, static_cast<float>(armor));

        // health
        float healthMult = globalRate * healthMultiplier * playerMultiplier;

        uint64 health = round(healthMult * (float)prevHealth);
        uint64 maxHealth = round(healthMult * float(creature->GetMaxHealth()));

        creature->SetCreateHealth(health);
        creature->SetMaxHealth(maxHealth);
        creature->ResetPlayerDamageReq();
        creature->SetModifierValue(UNIT_MOD_HEALTH, BASE_VALUE, static_cast<float>(health));

        creature->SetHealth(float(health) / float(prevMaxHealth) * float(prevHealth));

        // mana
        float manaMult = globalRate * manaMultiplier * playerMultiplier;

        uint64 mana = round(manaMult * float(creature->GetCreateMana()));

        creature->SetCreateMana(mana);
        creature->SetMaxPower(Powers::POWER_MANA, mana);
        creature->SetModifierValue(UNIT_MOD_MANA, BASE_VALUE, static_cast<float>(mana));

        // damage (this is used above to modify the damage dealt later)
        float damageMult = globalRate * damageMultiplier * playerMultiplier;
        creatureABInfo->DamageMultiplier = damageMult;

        // other stats
        creature->SetModifierValue(UNIT_MOD_ENERGY, BASE_VALUE, (float)100.0f);
        //creature->SetModifierValue(UNIT_MOD_RAGE, BASE_VALUE, (float)100.0f);

        switch (creature->getClass())
        {
            case CLASS_WARRIOR:
                creature->setPowerType(POWER_RAGE);
                //SetMaxPower(POWER_RAGE, GetCreatePowers(POWER_RAGE));
                //SetPower(POWER_RAGE, GetCreatePowers(POWER_RAGE));
                break;
            case CLASS_ROGUE:
                creature->setPowerType(POWER_ENERGY);
                creature->SetMaxPower(POWER_ENERGY, creature->GetCreatePowers(POWER_ENERGY));
                creature->SetPower(POWER_ENERGY, creature->GetCreatePowers(POWER_ENERGY));
                break;
            default:
                creature->setPowerType(POWER_MANA);
                creature->SetMaxPower(POWER_MANA, mana);
                creature->SetPower(POWER_MANA, mana);
                break;
        }

        // update all stats, do NOT use UpdateAllStats() it will break health/damage!
        creature->UpdateAttackPowerAndDamage();
        creature->UpdateAttackPowerAndDamage(true);

        TC_LOG_INFO(LOG_FILTER_AUTOBALANCE, "Modification complete for %s.  PlayerMult: %.3f  DamageMult: %.3f  BaseHealth: %u  OldBaseHealth: %u  ArmorMult: %.3f  Armor: %u  prevArmor: %u  SelLvl: %u  HolyResist: %u", creature->GetName(), playerMultiplier, damageMult, health, prevHealth, armorMult, armor, prevArmor, creatureABInfo->selectedLevel, creature->GetResistance(SPELL_SCHOOL_HOLY));
    }
};

void AddSC_AutoBalance()
{
    new AutoBalance_WorldScript;
    new AutoBalance_PlayerScript;
    new AutoBalance_UnitScript;
    new AutoBalance_AllCreatureScript;
    new AutoBalance_AllMapScript;
}