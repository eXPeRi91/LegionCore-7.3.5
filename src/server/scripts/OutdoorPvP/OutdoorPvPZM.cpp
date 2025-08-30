/*
 * Copyright (C) 2008-2012 TrinityCore <https://www.trinitycore.org/>
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
 * with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include "ScriptMgr.h"
#include "OutdoorPvpZM.h"
#include "ObjectMgr.h"
#include "OutdoorPvPMgr.h"
#include "Player.h"
#include "Creature.h"
#include "ObjectAccessor.h"
#include "GossipDef.h"
#include "World.h"
#include "Packets/WorldStatePackets.h"

OPvpCapturePointZM_Beacon::OPvpCapturePointZM_Beacon(OutdoorPvp* pvp, ZM_BeaconType type)
: OPvpCapturePoint(pvp), m_TowerType(type), m_TowerState(ZM_TOWERSTATE_N)
{
    SetCapturePointData(ZMCapturePoints[type].entry, ZMCapturePoints[type].map, ZMCapturePoints[type].x, ZMCapturePoints[type].y, ZMCapturePoints[type].z, ZMCapturePoints[type].o, ZMCapturePoints[type].rot0, ZMCapturePoints[type].rot1, ZMCapturePoints[type].rot2, ZMCapturePoints[type].rot3);
}

void OPvpCapturePointZM_Beacon::FillInitialWorldStates(WorldPackets::WorldState::InitWorldStates& packet)
{
    packet.Worldstates.emplace_back(static_cast<WorldStates>(ZMBeaconInfo[m_TowerType].ui_tower_n), bool(m_TowerState & ZM_TOWERSTATE_N));
    packet.Worldstates.emplace_back(static_cast<WorldStates>(ZMBeaconInfo[m_TowerType].map_tower_n), bool(m_TowerState & ZM_TOWERSTATE_N));
    packet.Worldstates.emplace_back(static_cast<WorldStates>(ZMBeaconInfo[m_TowerType].ui_tower_a), bool(m_TowerState & ZM_TOWERSTATE_A));
    packet.Worldstates.emplace_back(static_cast<WorldStates>(ZMBeaconInfo[m_TowerType].map_tower_a), bool(m_TowerState & ZM_TOWERSTATE_A));
    packet.Worldstates.emplace_back(static_cast<WorldStates>(ZMBeaconInfo[m_TowerType].ui_tower_h), bool(m_TowerState & ZM_TOWERSTATE_H));
    packet.Worldstates.emplace_back(static_cast<WorldStates>(ZMBeaconInfo[m_TowerType].map_tower_h), bool(m_TowerState & ZM_TOWERSTATE_H));
}

void OPvpCapturePointZM_Beacon::UpdateTowerState()
{
    m_Pvp->SendUpdateWorldState(WorldStates(ZMBeaconInfo[m_TowerType].ui_tower_n), uint32(bool(m_TowerState & ZM_TOWERSTATE_N)));
    m_Pvp->SendUpdateWorldState(WorldStates(ZMBeaconInfo[m_TowerType].map_tower_n), uint32(bool(m_TowerState & ZM_TOWERSTATE_N)));
    m_Pvp->SendUpdateWorldState(WorldStates(ZMBeaconInfo[m_TowerType].ui_tower_a), uint32(bool(m_TowerState & ZM_TOWERSTATE_A)));
    m_Pvp->SendUpdateWorldState(WorldStates(ZMBeaconInfo[m_TowerType].map_tower_a), uint32(bool(m_TowerState & ZM_TOWERSTATE_A)));
    m_Pvp->SendUpdateWorldState(WorldStates(ZMBeaconInfo[m_TowerType].ui_tower_h), uint32(bool(m_TowerState & ZM_TOWERSTATE_H)));
    m_Pvp->SendUpdateWorldState(WorldStates(ZMBeaconInfo[m_TowerType].map_tower_h), uint32(bool(m_TowerState & ZM_TOWERSTATE_H)));
}

bool OPvpCapturePointZM_Beacon::HandlePlayerEnter(Player* player)
{
    if (OPvpCapturePoint::HandlePlayerEnter(player))
    {
        player->SendUpdateWorldState(ZMBeaconInfo[m_TowerType].slider_disp, 1);
        uint32 phase = (uint32)ceil((m_value + m_maxValue) / (2 * m_maxValue) * 100.0f);
        player->SendUpdateWorldState(ZMBeaconInfo[m_TowerType].slider_pos, phase);
        player->SendUpdateWorldState(ZMBeaconInfo[m_TowerType].slider_n, m_neutralValuePct);
        return true;
    }
    return false;
}

void OPvpCapturePointZM_Beacon::HandlePlayerLeave(Player* player)
{
    player->SendUpdateWorldState(ZMBeaconInfo[m_TowerType].slider_disp, 0);
    OPvpCapturePoint::HandlePlayerLeave(player);
}

void OPvpCapturePointZM_Beacon::ChangeState()
{
    // if changing from controlling alliance to horde
    if (m_OldState == OBJECTIVESTATE_ALLIANCE)
    {
        if (uint32 alliance_towers = ((OutdoorPvpZM*)m_Pvp)->GetAllianceTowersControlled())
            ((OutdoorPvpZM*)m_Pvp)->SetAllianceTowersControlled(--alliance_towers);
        sWorld->SendZoneText(ZM_GRAVEYARD_ZONE, sObjectMgr->GetTrinityStringForDBCLocale(ZMBeaconLoseA[m_TowerType]));
    }
    // if changing from controlling horde to alliance
    else if (m_OldState == OBJECTIVESTATE_HORDE)
    {
        if (uint32 horde_towers = ((OutdoorPvpZM*)m_Pvp)->GetHordeTowersControlled())
            ((OutdoorPvpZM*)m_Pvp)->SetHordeTowersControlled(--horde_towers);
        sWorld->SendZoneText(ZM_GRAVEYARD_ZONE, sObjectMgr->GetTrinityStringForDBCLocale(ZMBeaconLoseH[m_TowerType]));
    }

    switch (m_State)
    {
        case OBJECTIVESTATE_ALLIANCE:
        {
            m_TowerState = ZM_TOWERSTATE_A;
            uint32 alliance_towers = ((OutdoorPvpZM*)m_Pvp)->GetAllianceTowersControlled();
            if (alliance_towers < ZM_NUM_BEACONS)
                ((OutdoorPvpZM*)m_Pvp)->SetAllianceTowersControlled(++alliance_towers);
            sWorld->SendZoneText(ZM_GRAVEYARD_ZONE, sObjectMgr->GetTrinityStringForDBCLocale(ZMBeaconCaptureA[m_TowerType]));
            break;
        }
        case OBJECTIVESTATE_HORDE:
        {
            m_TowerState = ZM_TOWERSTATE_H;
            uint32 horde_towers = ((OutdoorPvpZM*)m_Pvp)->GetHordeTowersControlled();
            if (horde_towers < ZM_NUM_BEACONS)
                ((OutdoorPvpZM*)m_Pvp)->SetHordeTowersControlled(++horde_towers);
            sWorld->SendZoneText(ZM_GRAVEYARD_ZONE, sObjectMgr->GetTrinityStringForDBCLocale(ZMBeaconCaptureH[m_TowerType]));
            break;
        }
        case OBJECTIVESTATE_NEUTRAL:
        case OBJECTIVESTATE_NEUTRAL_ALLIANCE_CHALLENGE:
        case OBJECTIVESTATE_NEUTRAL_HORDE_CHALLENGE:
        case OBJECTIVESTATE_ALLIANCE_HORDE_CHALLENGE:
        case OBJECTIVESTATE_HORDE_ALLIANCE_CHALLENGE:
            m_TowerState = ZM_TOWERSTATE_N;
            break;
    }

    UpdateTowerState();
}

void OPvpCapturePointZM_Beacon::SendChangePhase()
{
    // send this too, sometimes the slider disappears, dunno why :(
    SendUpdateWorldState(ZMBeaconInfo[m_TowerType].slider_disp, 1);
    // send these updates to only the ones in this objective
    uint32 phase = (uint32)ceil((m_value + m_maxValue) / (2 * m_maxValue) * 100.0f);
    SendUpdateWorldState(ZMBeaconInfo[m_TowerType].slider_pos, phase);
    SendUpdateWorldState(ZMBeaconInfo[m_TowerType].slider_n, m_neutralValuePct);
}

bool OutdoorPvpZM::Update(uint32 diff)
{
    bool changed = OutdoorPvp::Update(diff);
    if (changed)
    {
        if (m_AllianceTowersControlled == ZM_NUM_BEACONS)
            m_GraveYard->SetBeaconState(ALLIANCE);
        else if (m_HordeTowersControlled == ZM_NUM_BEACONS)
            m_GraveYard->SetBeaconState(HORDE);
        else
            m_GraveYard->SetBeaconState(0);
    }
    return changed;
}

void OutdoorPvpZM::HandlePlayerEnterZone(ObjectGuid guid, uint32 zone)
{
    Player* player = ObjectAccessor::GetObjectInMap(guid, m_map, (Player*)nullptr);
    if (!player)
        return;

    if (player->GetTeam() == ALLIANCE)
    {
        if (m_GraveYard->GetGraveYardState() & ZM_GRAVEYARD_A)
            player->CastSpell(player, ZM_CAPTURE_BUFF, true);
    }
    else
    {
        if (m_GraveYard->GetGraveYardState() & ZM_GRAVEYARD_H)
            player->CastSpell(player, ZM_CAPTURE_BUFF, true);
    }
    OutdoorPvp::HandlePlayerEnterZone(guid, zone);
}

void OutdoorPvpZM::HandlePlayerLeaveZone(ObjectGuid guid, uint32 zone)
{
    Player* player = ObjectAccessor::GetObjectInMap(guid, m_map, (Player*)nullptr);
    if (!player)
        return;

    // remove buffs
    player->RemoveAurasDueToSpell(ZM_CAPTURE_BUFF);
    // remove flag
    player->RemoveAurasDueToSpell(ZM_BATTLE_STANDARD_A);
    player->RemoveAurasDueToSpell(ZM_BATTLE_STANDARD_H);
    OutdoorPvp::HandlePlayerLeaveZone(guid, zone);
}

OutdoorPvpZM::OutdoorPvpZM()
{
    m_TypeId = OUTDOOR_PVP_ZM;
    m_GraveYard = NULL;
    m_AllianceTowersControlled = 0;
    m_HordeTowersControlled = 0;
}

bool OutdoorPvpZM::SetupOutdoorPvp()
{
    // add the zones affected by the PvP buff
    if (!m_zonesRegistered)
        for (uint8 i = 0; i < OutdoorPvpZMBuffZonesNum; ++i)
            RegisterZone(OutdoorPvpZMBuffZones[i]);

    m_zonesRegistered = true;

    return true;
}

void OutdoorPvpZM::Initialize(uint32 zone)
{
    if (m_zonesRegistered)
        return;
    m_zonesRegistered = true;

    m_AllianceTowersControlled = 0;
    m_HordeTowersControlled = 0;

    AddCapturePoint(new OPvpCapturePointZM_Beacon(this, ZM_BEACON_WEST));
    AddCapturePoint(new OPvpCapturePointZM_Beacon(this, ZM_BEACON_EAST));
    m_GraveYard = new OPvpCapturePointZM_GraveYard(this);
    AddCapturePoint(m_GraveYard); // though the update function isn't used, the handleusego is!

}
void OutdoorPvpZM::HandleKillImpl(Player* player, Unit* killed)
{
    if (killed->GetTypeId() != TYPEID_PLAYER)
        return;

    if (player->GetTeam() == ALLIANCE && killed->ToPlayer()->GetTeam() != ALLIANCE)
        player->CastSpell(player, ZM_AlliancePlayerKillReward, true);
    else if (player->GetTeam() == HORDE && killed->ToPlayer()->GetTeam() != HORDE)
        player->CastSpell(player, ZM_HordePlayerKillReward, true);
}

bool OPvpCapturePointZM_GraveYard::Update(uint32 /*diff*/)
{
    bool retval = m_State != m_OldState;
    m_State = m_OldState;
    return retval;
}

int32 OPvpCapturePointZM_GraveYard::HandleOpenGo(Player* player, ObjectGuid guid)
{
    int32 retval = OPvpCapturePoint::HandleOpenGo(player, guid);
    if (retval >= 0)
    {
        if (player->HasAura(ZM_BATTLE_STANDARD_A) && m_GraveYardState != ZM_GRAVEYARD_A)
        {
            if (m_GraveYardState == ZM_GRAVEYARD_H)
                sWorld->SendZoneText(ZM_GRAVEYARD_ZONE, sObjectMgr->GetTrinityStringForDBCLocale(LANG_OPVP_ZM_LOSE_GY_H));
            m_GraveYardState = ZM_GRAVEYARD_A;
            DelObject(0);   // only one gotype is used in the whole outdoor PvP, no need to call it a constant
            AddObject(0, ZM_Banner_A.entry, ZM_Banner_A.map, ZM_Banner_A.x, ZM_Banner_A.y, ZM_Banner_A.z, ZM_Banner_A.o, ZM_Banner_A.rot0, ZM_Banner_A.rot1, ZM_Banner_A.rot2, ZM_Banner_A.rot3);
            sObjectMgr->RemoveGraveYardLink(ZM_GRAVEYARD_ID, ZM_GRAVEYARD_ZONE, HORDE);          // rem gy
            sObjectMgr->AddGraveYardLink(ZM_GRAVEYARD_ID, ZM_GRAVEYARD_ZONE, ALLIANCE, false);   // add gy
            m_Pvp->TeamApplyBuff(TEAM_ALLIANCE, ZM_CAPTURE_BUFF);
            player->RemoveAurasDueToSpell(ZM_BATTLE_STANDARD_A);
            sWorld->SendZoneText(ZM_GRAVEYARD_ZONE, sObjectMgr->GetTrinityStringForDBCLocale(LANG_OPVP_ZM_CAPTURE_GY_A));
        }
        else if (player->HasAura(ZM_BATTLE_STANDARD_H) && m_GraveYardState != ZM_GRAVEYARD_H)
        {
            if (m_GraveYardState == ZM_GRAVEYARD_A)
                sWorld->SendZoneText(ZM_GRAVEYARD_ZONE, sObjectMgr->GetTrinityStringForDBCLocale(LANG_OPVP_ZM_LOSE_GY_A));
            m_GraveYardState = ZM_GRAVEYARD_H;
            DelObject(0);   // only one gotype is used in the whole outdoor PvP, no need to call it a constant
            AddObject(0, ZM_Banner_H.entry, ZM_Banner_H.map, ZM_Banner_H.x, ZM_Banner_H.y, ZM_Banner_H.z, ZM_Banner_H.o, ZM_Banner_H.rot0, ZM_Banner_H.rot1, ZM_Banner_H.rot2, ZM_Banner_H.rot3);
            sObjectMgr->RemoveGraveYardLink(ZM_GRAVEYARD_ID, ZM_GRAVEYARD_ZONE, ALLIANCE);          // rem gy
            sObjectMgr->AddGraveYardLink(ZM_GRAVEYARD_ID, ZM_GRAVEYARD_ZONE, HORDE, false);   // add gy
            m_Pvp->TeamApplyBuff(TEAM_HORDE, ZM_CAPTURE_BUFF);
            player->RemoveAurasDueToSpell(ZM_BATTLE_STANDARD_H);
            sWorld->SendZoneText(ZM_GRAVEYARD_ZONE, sObjectMgr->GetTrinityStringForDBCLocale(LANG_OPVP_ZM_CAPTURE_GY_H));
        }
        UpdateTowerState();
    }
    return retval;
}

OPvpCapturePointZM_GraveYard::OPvpCapturePointZM_GraveYard(OutdoorPvp* Pvp)
: OPvpCapturePoint(Pvp)
{
    m_BothControllingFaction = 0;
    m_GraveYardState = ZM_GRAVEYARD_N;
    m_FlagCarrierGUID.Clear();
    // add field scouts here
    AddCreature(ZM_ALLIANCE_FIELD_SCOUT, ZM_AllianceFieldScout.entry, ZM_AllianceFieldScout.teamval, ZM_AllianceFieldScout.map, ZM_AllianceFieldScout.x, ZM_AllianceFieldScout.y, ZM_AllianceFieldScout.z, ZM_AllianceFieldScout.o);
    AddCreature(ZM_HORDE_FIELD_SCOUT, ZM_HordeFieldScout.entry, ZM_HordeFieldScout.teamval, ZM_HordeFieldScout.map, ZM_HordeFieldScout.x, ZM_HordeFieldScout.y, ZM_HordeFieldScout.z, ZM_HordeFieldScout.o);
    // add neutral banner
    AddObject(0, ZM_Banner_N.entry, ZM_Banner_N.map, ZM_Banner_N.x, ZM_Banner_N.y, ZM_Banner_N.z, ZM_Banner_N.o, ZM_Banner_N.rot0, ZM_Banner_N.rot1, ZM_Banner_N.rot2, ZM_Banner_N.rot3);
}

void OPvpCapturePointZM_GraveYard::UpdateTowerState()
{
    m_Pvp->SendUpdateWorldState(ZM_MAP_GRAVEYARD_N, uint32(bool(m_GraveYardState & ZM_GRAVEYARD_N)));
    m_Pvp->SendUpdateWorldState(ZM_MAP_GRAVEYARD_H, uint32(bool(m_GraveYardState & ZM_GRAVEYARD_H)));
    m_Pvp->SendUpdateWorldState(ZM_MAP_GRAVEYARD_A, uint32(bool(m_GraveYardState & ZM_GRAVEYARD_A)));

    m_Pvp->SendUpdateWorldState(ZM_MAP_ALLIANCE_FLAG_READY, uint32(m_BothControllingFaction == ALLIANCE));
    m_Pvp->SendUpdateWorldState(ZM_MAP_ALLIANCE_FLAG_NOT_READY, uint32(m_BothControllingFaction != ALLIANCE));
    m_Pvp->SendUpdateWorldState(ZM_MAP_HORDE_FLAG_READY, uint32(m_BothControllingFaction == HORDE));
    m_Pvp->SendUpdateWorldState(ZM_MAP_HORDE_FLAG_NOT_READY, uint32(m_BothControllingFaction != HORDE));
}

void OPvpCapturePointZM_GraveYard::FillInitialWorldStates(WorldPackets::WorldState::InitWorldStates& packet)
{
    packet.Worldstates.emplace_back(ZM_MAP_GRAVEYARD_N, bool(m_GraveYardState & ZM_GRAVEYARD_N));
    packet.Worldstates.emplace_back(ZM_MAP_GRAVEYARD_H, bool(m_GraveYardState & ZM_GRAVEYARD_H));
    packet.Worldstates.emplace_back(ZM_MAP_GRAVEYARD_A, bool(m_GraveYardState & ZM_GRAVEYARD_A));

    packet.Worldstates.emplace_back(ZM_MAP_ALLIANCE_FLAG_READY, m_BothControllingFaction == ALLIANCE);
    packet.Worldstates.emplace_back(ZM_MAP_ALLIANCE_FLAG_NOT_READY, m_BothControllingFaction != ALLIANCE);
    packet.Worldstates.emplace_back(ZM_MAP_HORDE_FLAG_READY, m_BothControllingFaction == HORDE);
    packet.Worldstates.emplace_back(ZM_MAP_HORDE_FLAG_NOT_READY, m_BothControllingFaction != HORDE);
}

void OPvpCapturePointZM_GraveYard::SetBeaconState(uint32 controlling_faction)
{
    // nothing to do here
    if (m_BothControllingFaction == controlling_faction)
        return;
    m_BothControllingFaction = controlling_faction;

    switch (controlling_faction)
    {
    case ALLIANCE:
        // if ally already controls the gy and taken back both beacons, return, nothing to do for us
        if (m_GraveYardState & ZM_GRAVEYARD_A)
            return;
        // ally doesn't control the gy, but controls the side beacons -> add gossip option, add neutral banner
        break;
    case HORDE:
        // if horde already controls the gy and taken back both beacons, return, nothing to do for us
        if (m_GraveYardState & ZM_GRAVEYARD_H)
            return;
        // horde doesn't control the gy, but controls the side beacons -> add gossip option, add neutral banner
        break;
    default:
        // if the graveyard is not neutral, then leave it that way
        // if the graveyard is neutral, then we have to dispel the buff from the flag carrier
        if (m_GraveYardState & ZM_GRAVEYARD_N)
        {
            // gy was neutral, thus neutral banner was spawned, it is possible that someone was taking the flag to the gy
            if (m_FlagCarrierGUID)
            {
                // remove flag from carrier, reset flag carrier guid
                Player* p = ObjectAccessor::FindPlayer(m_FlagCarrierGUID);
                if (p)
                {
                   p->RemoveAurasDueToSpell(ZM_BATTLE_STANDARD_A);
                   p->RemoveAurasDueToSpell(ZM_BATTLE_STANDARD_H);
                }
                m_FlagCarrierGUID.Clear();
            }
        }
        break;
    }
    // send worldstateupdate
    UpdateTowerState();
}

bool OPvpCapturePointZM_GraveYard::CanTalkTo(Player* player, Creature* c, GossipMenuItems const& /*gso*/)
{
    ObjectGuid guid = c->GetGUID();
    std::map<ObjectGuid, uint32>::iterator itr = m_CreatureTypes.find(guid);
    if (itr != m_CreatureTypes.end())
    {
        if (itr->second == ZM_ALLIANCE_FIELD_SCOUT && player->GetTeam() == ALLIANCE && m_BothControllingFaction == ALLIANCE && !m_FlagCarrierGUID && m_GraveYardState != ZM_GRAVEYARD_A)
            return true;
        else if (itr->second == ZM_HORDE_FIELD_SCOUT && player->GetTeam() == HORDE && m_BothControllingFaction == HORDE && !m_FlagCarrierGUID && m_GraveYardState != ZM_GRAVEYARD_H)
            return true;
    }
    return false;
}

bool OPvpCapturePointZM_GraveYard::HandleGossipOption(Player* player, ObjectGuid guid, uint32 /*gossipid*/)
{
    std::map<ObjectGuid, uint32>::iterator itr = m_CreatureTypes.find(guid);
    if (itr != m_CreatureTypes.end())
    {
        Creature* cr = HashMapHolder<Creature>::Find(guid);
        if (!cr)
            return true;
        // if the flag is already taken, then return
        if (m_FlagCarrierGUID)
            return true;
        if (itr->second == ZM_ALLIANCE_FIELD_SCOUT)
        {
            cr->CastSpell(player, ZM_BATTLE_STANDARD_A, true);
            m_FlagCarrierGUID = player->GetGUID();
        }
        else if (itr->second == ZM_HORDE_FIELD_SCOUT)
        {
            cr->CastSpell(player, ZM_BATTLE_STANDARD_H, true);
            m_FlagCarrierGUID = player->GetGUID();
        }
        UpdateTowerState();
        player->PlayerTalkClass->SendCloseGossip();
        return true;
    }
    return false;
}

bool OPvpCapturePointZM_GraveYard::HandleDropFlag(Player* /*player*/, uint32 spellId)
{
    switch (spellId)
    {
        case ZM_BATTLE_STANDARD_A:
        case ZM_BATTLE_STANDARD_H:
            m_FlagCarrierGUID.Clear();
            return true;
    }
    return false;
}

uint32 OPvpCapturePointZM_GraveYard::GetGraveYardState() const
{
    return m_GraveYardState;
}

uint32 OutdoorPvpZM::GetAllianceTowersControlled() const
{
    return m_AllianceTowersControlled;
}

void OutdoorPvpZM::SetAllianceTowersControlled(uint32 count)
{
    m_AllianceTowersControlled = count;
}

uint32 OutdoorPvpZM::GetHordeTowersControlled() const
{
    return m_HordeTowersControlled;
}

void OutdoorPvpZM::SetHordeTowersControlled(uint32 count)
{
    m_HordeTowersControlled = count;
}

void OutdoorPvpZM::FillInitialWorldStates(WorldPackets::WorldState::InitWorldStates& packet)
{
    packet.Worldstates.emplace_back(ZM_WORLDSTATE_UNK_1, 1);
    for (auto itr = m_capturePoints.begin(); itr != m_capturePoints.end(); ++itr)
        itr->second->FillInitialWorldStates(packet);
}

void OutdoorPvpZM::SendRemoveWorldStates(Player* player)
{
    player->SendUpdateWorldState(ZM_UI_TOWER_SLIDER_N_W, 0);
    player->SendUpdateWorldState(ZM_UI_TOWER_SLIDER_POS_W, 0);
    player->SendUpdateWorldState(ZM_UI_TOWER_SLIDER_DISPLAY_W, 0);
    player->SendUpdateWorldState(ZM_UI_TOWER_SLIDER_N_E, 0);
    player->SendUpdateWorldState(ZM_UI_TOWER_SLIDER_POS_E, 0);
    player->SendUpdateWorldState(ZM_UI_TOWER_SLIDER_DISPLAY_E, 0);
    player->SendUpdateWorldState(ZM_WORLDSTATE_UNK_1, 1);
    player->SendUpdateWorldState(ZM_UI_TOWER_EAST_N, 0);
    player->SendUpdateWorldState(ZM_UI_TOWER_EAST_H, 0);
    player->SendUpdateWorldState(ZM_UI_TOWER_EAST_A, 0);
    player->SendUpdateWorldState(ZM_UI_TOWER_WEST_N, 0);
    player->SendUpdateWorldState(ZM_UI_TOWER_WEST_H, 0);
    player->SendUpdateWorldState(ZM_UI_TOWER_WEST_A, 0);
    player->SendUpdateWorldState(ZM_MAP_TOWER_EAST_N, 0);
    player->SendUpdateWorldState(ZM_MAP_TOWER_EAST_H, 0);
    player->SendUpdateWorldState(ZM_MAP_TOWER_EAST_A, 0);
    player->SendUpdateWorldState(ZM_MAP_GRAVEYARD_H, 0);
    player->SendUpdateWorldState(ZM_MAP_GRAVEYARD_A, 0);
    player->SendUpdateWorldState(ZM_MAP_GRAVEYARD_N, 0);
    player->SendUpdateWorldState(ZM_MAP_TOWER_WEST_N, 0);
    player->SendUpdateWorldState(ZM_MAP_TOWER_WEST_H, 0);
    player->SendUpdateWorldState(ZM_MAP_TOWER_WEST_A, 0);
    player->SendUpdateWorldState(ZM_MAP_HORDE_FLAG_READY, 0);
    player->SendUpdateWorldState(ZM_MAP_HORDE_FLAG_NOT_READY, 0);
    player->SendUpdateWorldState(ZM_MAP_ALLIANCE_FLAG_NOT_READY, 0);
    player->SendUpdateWorldState(ZM_MAP_ALLIANCE_FLAG_READY, 0);
}

class OutdoorPvp_zangarmarsh : public OutdoorPvpScript
{
    public:

        OutdoorPvp_zangarmarsh()
            : OutdoorPvpScript("outdoorpvp_zm")
        {
        }

        OutdoorPvp* GetOutdoorPvp() const override
        {
            return new OutdoorPvpZM();
        }
};

void AddSC_outdoorpvp_zm()
{
    new OutdoorPvp_zangarmarsh();
}
