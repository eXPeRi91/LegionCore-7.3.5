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
#include "OutdoorPvPHP.h"
#include "OutdoorPvP.h"
#include "Packets/WorldStatePackets.h"
#include "Player.h"
#include "WorldPacket.h"
#include "World.h"
#include "ObjectMgr.h"
#include "Language.h"

const uint32 HP_LANG_LOSE_A[HP_TOWER_NUM] = {LANG_OPVP_HP_LOSE_BROKENHILL_A, LANG_OPVP_HP_LOSE_OVERLOOK_A, LANG_OPVP_HP_LOSE_STADIUM_A};

const uint32 HP_LANG_LOSE_H[HP_TOWER_NUM] = {LANG_OPVP_HP_LOSE_BROKENHILL_H, LANG_OPVP_HP_LOSE_OVERLOOK_H, LANG_OPVP_HP_LOSE_STADIUM_H};

const uint32 HP_LANG_CAPTURE_A[HP_TOWER_NUM] = {LANG_OPVP_HP_CAPTURE_BROKENHILL_A, LANG_OPVP_HP_CAPTURE_OVERLOOK_A, LANG_OPVP_HP_CAPTURE_STADIUM_A};

const uint32 HP_LANG_CAPTURE_H[HP_TOWER_NUM] = {LANG_OPVP_HP_CAPTURE_BROKENHILL_H, LANG_OPVP_HP_CAPTURE_OVERLOOK_H, LANG_OPVP_HP_CAPTURE_STADIUM_H};

OPvpCapturePointHP::OPvpCapturePointHP(OutdoorPvp* pvp, OutdoorPvpHPTowerType type)
: OPvpCapturePoint(pvp), m_TowerType(type)
{
    SetCapturePointData(HPCapturePoints[type].entry,
        HPCapturePoints[type].map,
        HPCapturePoints[type].x,
        HPCapturePoints[type].y,
        HPCapturePoints[type].z,
        HPCapturePoints[type].o,
        HPCapturePoints[type].rot0,
        HPCapturePoints[type].rot1,
        HPCapturePoints[type].rot2,
        HPCapturePoints[type].rot3);
    AddObject(type,
        HPTowerFlags[type].entry,
        HPTowerFlags[type].map,
        HPTowerFlags[type].x,
        HPTowerFlags[type].y,
        HPTowerFlags[type].z,
        HPTowerFlags[type].o,
        HPTowerFlags[type].rot0,
        HPTowerFlags[type].rot1,
        HPTowerFlags[type].rot2,
        HPTowerFlags[type].rot3);
}

OutdoorPvpHP::OutdoorPvpHP()
{
    m_TypeId = OUTDOOR_PVP_HP;
}

bool OutdoorPvpHP::SetupOutdoorPvp()
{
    // add the zones affected by the PvP buff
    if (!m_zonesRegistered)
        for (int i = 0; i < OutdoorPvpHPBuffZonesNum; ++i)
            RegisterZone(OutdoorPvpHPBuffZones[i]);

    m_zonesRegistered = true;
    
    return true;
}

void OutdoorPvpHP::Initialize(uint32 zone)
{
    if (m_zonesRegistered)
        return;

    m_zonesRegistered = true;

    m_AllianceTowersControlled = 0;
    m_HordeTowersControlled = 0;

    AddCapturePoint(new OPvpCapturePointHP(this, HP_TOWER_BROKEN_HILL));

    AddCapturePoint(new OPvpCapturePointHP(this, HP_TOWER_OVERLOOK));

    AddCapturePoint(new OPvpCapturePointHP(this, HP_TOWER_STADIUM));
}

void OutdoorPvpHP::HandlePlayerEnterZone(ObjectGuid guid, uint32 zone)
{
    Player* player = ObjectAccessor::GetObjectInMap(guid, m_map, (Player*)nullptr);
    if (!player)
        return;

    // add buffs
    if (player->GetTeam() == ALLIANCE)
    {
        if (m_AllianceTowersControlled >= 3)
            player->CastSpell(player, AllianceBuff, true);
    }
    else
    {
        if (m_HordeTowersControlled >= 3)
            player->CastSpell(player, HordeBuff, true);
    }

    OutdoorPvp::HandlePlayerEnterZone(guid, zone);
}

void OutdoorPvpHP::HandlePlayerLeaveZone(ObjectGuid guid, uint32 zone)
{
    Player* player = ObjectAccessor::GetObjectInMap(guid, m_map, (Player*)nullptr);
    if (!player)
        return;

    // remove buffs
    if (player->GetTeam() == ALLIANCE)
        player->RemoveAurasDueToSpell(AllianceBuff);
    else
        player->RemoveAurasDueToSpell(HordeBuff);

    OutdoorPvp::HandlePlayerLeaveZone(guid, zone);
}

bool OutdoorPvpHP::Update(uint32 diff)
{
    bool changed = OutdoorPvp::Update(diff);
    if (changed)
    {
        if (m_AllianceTowersControlled == 3)
            TeamApplyBuff(TEAM_ALLIANCE, AllianceBuff, HordeBuff);
        else if (m_HordeTowersControlled == 3)
            TeamApplyBuff(TEAM_HORDE, HordeBuff, AllianceBuff);
        else
        {
            TeamCastSpell(TEAM_ALLIANCE, -AllianceBuff);
            TeamCastSpell(TEAM_HORDE, -HordeBuff);
        }
        SendUpdateWorldState(HP_UI_TOWER_COUNT_A, m_AllianceTowersControlled);
        SendUpdateWorldState(HP_UI_TOWER_COUNT_H, m_HordeTowersControlled);
    }
    return changed;
}

void OutdoorPvpHP::SendRemoveWorldStates(Player* player)
{
    player->SendUpdateWorldState(HP_UI_TOWER_DISPLAY_A, 0);
    player->SendUpdateWorldState(HP_UI_TOWER_DISPLAY_H, 0);
    player->SendUpdateWorldState(HP_UI_TOWER_COUNT_H, 0);
    player->SendUpdateWorldState(HP_UI_TOWER_COUNT_A, 0);
    player->SendUpdateWorldState(HP_UI_TOWER_SLIDER_N, 0);
    player->SendUpdateWorldState(HP_UI_TOWER_SLIDER_POS, 0);
    player->SendUpdateWorldState(HP_UI_TOWER_SLIDER_DISPLAY, 0);
    for (int i = 0; i < HP_TOWER_NUM; ++i)
    {
        player->SendUpdateWorldState(HP_MAP_N[i], 0);
        player->SendUpdateWorldState(HP_MAP_A[i], 0);
        player->SendUpdateWorldState(HP_MAP_H[i], 0);
    }
}

void OutdoorPvpHP::FillInitialWorldStates(WorldPackets::WorldState::InitWorldStates& packet)
{
    packet.Worldstates.emplace_back(HP_UI_TOWER_DISPLAY_A, 1);
    packet.Worldstates.emplace_back(HP_UI_TOWER_DISPLAY_H, 1);
    packet.Worldstates.emplace_back(HP_UI_TOWER_COUNT_A, m_AllianceTowersControlled);
    packet.Worldstates.emplace_back(HP_UI_TOWER_COUNT_H, m_HordeTowersControlled);
    packet.Worldstates.emplace_back(HP_UI_TOWER_SLIDER_DISPLAY, 0);
    packet.Worldstates.emplace_back(HP_UI_TOWER_SLIDER_POS, 50);
    packet.Worldstates.emplace_back(HP_UI_TOWER_SLIDER_N, 100);

    for (auto itr = m_capturePoints.begin(); itr != m_capturePoints.end(); ++itr)
        itr->second->FillInitialWorldStates(packet);
}

void OPvpCapturePointHP::ChangeState()
{
    uint32 field = 0;
    switch (m_OldState)
    {
    case OBJECTIVESTATE_NEUTRAL:
        field = HP_MAP_N[m_TowerType];
        break;
    case OBJECTIVESTATE_ALLIANCE:
        field = HP_MAP_A[m_TowerType];
        if (uint32 alliance_towers = ((OutdoorPvpHP*)m_Pvp)->GetAllianceTowersControlled())
            ((OutdoorPvpHP*)m_Pvp)->SetAllianceTowersControlled(--alliance_towers);
        sWorld->SendZoneText(OutdoorPvpHPBuffZones[0], sObjectMgr->GetTrinityStringForDBCLocale(HP_LANG_LOSE_A[m_TowerType]));
        break;
    case OBJECTIVESTATE_HORDE:
        field = HP_MAP_H[m_TowerType];
        if (uint32 horde_towers = ((OutdoorPvpHP*)m_Pvp)->GetHordeTowersControlled())
            ((OutdoorPvpHP*)m_Pvp)->SetHordeTowersControlled(--horde_towers);
        sWorld->SendZoneText(OutdoorPvpHPBuffZones[0], sObjectMgr->GetTrinityStringForDBCLocale(HP_LANG_LOSE_H[m_TowerType]));
        break;
    case OBJECTIVESTATE_NEUTRAL_ALLIANCE_CHALLENGE:
        field = HP_MAP_N[m_TowerType];
        break;
    case OBJECTIVESTATE_NEUTRAL_HORDE_CHALLENGE:
        field = HP_MAP_N[m_TowerType];
        break;
    case OBJECTIVESTATE_ALLIANCE_HORDE_CHALLENGE:
        field = HP_MAP_A[m_TowerType];
        break;
    case OBJECTIVESTATE_HORDE_ALLIANCE_CHALLENGE:
        field = HP_MAP_H[m_TowerType];
        break;
    }

    // send world state update
    if (field)
    {
        m_Pvp->SendUpdateWorldState(field, 0);
        field = 0;
    }
    uint32 artkit = 21;
    uint32 artkit2 = HP_TowerArtKit_N[m_TowerType];
    switch (m_State)
    {
    case OBJECTIVESTATE_NEUTRAL:
        field = HP_MAP_N[m_TowerType];
        break;
    case OBJECTIVESTATE_ALLIANCE:
    {
        field = HP_MAP_A[m_TowerType];
        artkit = 2;
        artkit2 = HP_TowerArtKit_A[m_TowerType];
        uint32 alliance_towers = ((OutdoorPvpHP*)m_Pvp)->GetAllianceTowersControlled();
        if (alliance_towers < 3)
            ((OutdoorPvpHP*)m_Pvp)->SetAllianceTowersControlled(++alliance_towers);
        sWorld->SendZoneText(OutdoorPvpHPBuffZones[0], sObjectMgr->GetTrinityStringForDBCLocale(HP_LANG_CAPTURE_A[m_TowerType]));
        break;
    }
    case OBJECTIVESTATE_HORDE:
    {
        field = HP_MAP_H[m_TowerType];
        artkit = 1;
        artkit2 = HP_TowerArtKit_H[m_TowerType];
        uint32 horde_towers = ((OutdoorPvpHP*)m_Pvp)->GetHordeTowersControlled();
        if (horde_towers < 3)
            ((OutdoorPvpHP*)m_Pvp)->SetHordeTowersControlled(++horde_towers);
        sWorld->SendZoneText(OutdoorPvpHPBuffZones[0], sObjectMgr->GetTrinityStringForDBCLocale(HP_LANG_CAPTURE_H[m_TowerType]));
        break;
    }
    case OBJECTIVESTATE_NEUTRAL_ALLIANCE_CHALLENGE:
        field = HP_MAP_N[m_TowerType];
        break;
    case OBJECTIVESTATE_NEUTRAL_HORDE_CHALLENGE:
        field = HP_MAP_N[m_TowerType];
        break;
    case OBJECTIVESTATE_ALLIANCE_HORDE_CHALLENGE:
        field = HP_MAP_A[m_TowerType];
        artkit = 2;
        artkit2 = HP_TowerArtKit_A[m_TowerType];
        break;
    case OBJECTIVESTATE_HORDE_ALLIANCE_CHALLENGE:
        field = HP_MAP_H[m_TowerType];
        artkit = 1;
        artkit2 = HP_TowerArtKit_H[m_TowerType];
        break;
    }

    if (GameObject* flag = sObjectAccessor->FindGameObject(m_capturePointGUID))
        flag->SetGoArtKit(artkit);

    if (GameObject* flag2 = HashMapHolder<GameObject>::Find(m_Objects[m_TowerType]))
        flag2->SetGoArtKit(artkit2);

    // send world state update
    if (field)
        m_Pvp->SendUpdateWorldState(field, 1);

    // complete quest objective
    if (m_State == OBJECTIVESTATE_ALLIANCE || m_State == OBJECTIVESTATE_HORDE)
        SendObjectiveComplete(HP_CREDITMARKER[m_TowerType], ObjectGuid::Empty);
}

void OPvpCapturePointHP::SendChangePhase()
{
    SendUpdateWorldState(HP_UI_TOWER_SLIDER_N, m_neutralValuePct);
    // send these updates to only the ones in this objective
    uint32 phase = (uint32)ceil((m_value + m_maxValue) / (2 * m_maxValue) * 100.0f);
    SendUpdateWorldState(HP_UI_TOWER_SLIDER_POS, phase);
    // send this too, sometimes the slider disappears, dunno why :(
    SendUpdateWorldState(HP_UI_TOWER_SLIDER_DISPLAY, 1);
}

void OPvpCapturePointHP::FillInitialWorldStates(WorldPackets::WorldState::InitWorldStates& packet)
{
    switch (m_State)
    {
        case OBJECTIVESTATE_ALLIANCE:
        case OBJECTIVESTATE_ALLIANCE_HORDE_CHALLENGE:
            packet.Worldstates.emplace_back(static_cast<WorldStates>(HP_MAP_N[m_TowerType]), 0);
            packet.Worldstates.emplace_back(static_cast<WorldStates>(HP_MAP_A[m_TowerType]), 1);
            packet.Worldstates.emplace_back(static_cast<WorldStates>(HP_MAP_H[m_TowerType]), 0);
            break;
        case OBJECTIVESTATE_HORDE:
        case OBJECTIVESTATE_HORDE_ALLIANCE_CHALLENGE:
            packet.Worldstates.emplace_back(static_cast<WorldStates>(HP_MAP_N[m_TowerType]), 0);
            packet.Worldstates.emplace_back(static_cast<WorldStates>(HP_MAP_A[m_TowerType]), 0);
            packet.Worldstates.emplace_back(static_cast<WorldStates>(HP_MAP_H[m_TowerType]), 1);
            break;
        case OBJECTIVESTATE_NEUTRAL:
        case OBJECTIVESTATE_NEUTRAL_ALLIANCE_CHALLENGE:
        case OBJECTIVESTATE_NEUTRAL_HORDE_CHALLENGE:
        default:
            packet.Worldstates.emplace_back(static_cast<WorldStates>(HP_MAP_N[m_TowerType]), 1);
            packet.Worldstates.emplace_back(static_cast<WorldStates>(HP_MAP_A[m_TowerType]), 0);
            packet.Worldstates.emplace_back(static_cast<WorldStates>(HP_MAP_H[m_TowerType]), 0);
            break;
    }
}

bool OPvpCapturePointHP::HandlePlayerEnter(Player* player)
{
    if (OPvpCapturePoint::HandlePlayerEnter(player))
    {
        player->SendUpdateWorldState(HP_UI_TOWER_SLIDER_DISPLAY, 1);
        player->SendUpdateWorldState(HP_UI_TOWER_SLIDER_POS, ceil((m_value + m_maxValue) / (2 * m_maxValue) * 100.0f));
        player->SendUpdateWorldState(HP_UI_TOWER_SLIDER_N, m_neutralValuePct);
        return true;
    }
    return false;
}

void OPvpCapturePointHP::HandlePlayerLeave(Player* player)
{
    player->SendUpdateWorldState(HP_UI_TOWER_SLIDER_DISPLAY, 0);
    OPvpCapturePoint::HandlePlayerLeave(player);
}

void OutdoorPvpHP::HandleKillImpl(Player* player, Unit* killed)
{
    if (killed->GetTypeId() != TYPEID_PLAYER)
        return;

    if (player->GetTeam() == ALLIANCE && killed->ToPlayer()->GetTeam() != ALLIANCE)
        player->CastSpell(player, AlliancePlayerKillReward, true);
    else if (player->GetTeam() == HORDE && killed->ToPlayer()->GetTeam() != HORDE)
        player->CastSpell(player, HordePlayerKillReward, true);
}

uint32 OutdoorPvpHP::GetAllianceTowersControlled() const
{
    return m_AllianceTowersControlled;
}

void OutdoorPvpHP::SetAllianceTowersControlled(uint32 count)
{
    m_AllianceTowersControlled = count;
}

uint32 OutdoorPvpHP::GetHordeTowersControlled() const
{
    return m_HordeTowersControlled;
}

void OutdoorPvpHP::SetHordeTowersControlled(uint32 count)
{
    m_HordeTowersControlled = count;
}

class OutdoorPvp_hellfire_peninsula : public OutdoorPvpScript
{
    public:

        OutdoorPvp_hellfire_peninsula()
            : OutdoorPvpScript("outdoorpvp_hp")
        {
        }

        OutdoorPvp* GetOutdoorPvp() const override
        {
            return new OutdoorPvpHP();
        }
};

void AddSC_outdoorpvp_hp()
{
    new OutdoorPvp_hellfire_peninsula();
}
