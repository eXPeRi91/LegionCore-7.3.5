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

#include "OutdoorPvpMgr.h"
#include "ObjectMgr.h"
#include "Player.h"
#include "DisableMgr.h"
#include "ScriptMgr.h"
#include "DatabaseEnv.h"

OutdoorPvpMgr::OutdoorPvpMgr()
{
    m_UpdateTimer = 0;
}

void OutdoorPvpMgr::Die()
{
    for (auto v : m_OutdoorPvpSet)
        delete v;

    for (auto v : m_OutdoorPvpDatas)
        delete v.second;
}

OutdoorPvpMgr* OutdoorPvpMgr::instance()
{
    static OutdoorPvpMgr instance;
    return &instance;
}

void OutdoorPvpMgr::InitOutdoorPvp()
{
    uint32 oldMSTime = getMSTime();

    //                                                 0       1
    QueryResult result = WorldDatabase.Query("SELECT TypeId, ScriptName FROM outdoorpvp_template");

    if (!result)
    {
        TC_LOG_ERROR(LOG_FILTER_SERVER_LOADING, ">> Loaded 0 outdoor PvP definitions. DB table `outdoorpvp_template` is empty.");
        return;
    }

    uint32 count = 0;
    uint32 typeId = 0;

    do
    {
        Field* fields = result->Fetch();

        typeId = fields[0].GetUInt8();

        if (DisableMgr::IsDisabledFor(DISABLE_TYPE_OUTDOORPVP, typeId))
            continue;

        if (typeId >= MAX_OUTDOORPVP_TYPES)
        {
            TC_LOG_ERROR(LOG_FILTER_SQL, "Invalid OutdoorPvpTypes value %u in outdoorpvp_template; skipped.", typeId);
            continue;
        }

        OutdoorPvpData* data = new OutdoorPvpData();
        OutdoorPvpTypes realTypeId = OutdoorPvpTypes(typeId);
        data->TypeId = realTypeId;
        data->ScriptId = sObjectMgr->GetScriptId(fields[1].GetCString());
        m_OutdoorPvpDatas[realTypeId] = data;

        ++count;
    }
    while (result->NextRow());

    for (uint8 i = 1; i < MAX_OUTDOORPVP_TYPES; ++i)
    {
        OutdoorPvpDataMap::iterator iter = m_OutdoorPvpDatas.find(OutdoorPvpTypes(i));
        if (iter == m_OutdoorPvpDatas.end())
        {
            //TC_LOG_ERROR(LOG_FILTER_SQL, "Could not initialize OutdoorPvP object for type ID %u; no entry in database.", uint32(i));
            continue;
        }

        OutdoorPvp* Pvp = sScriptMgr->CreateOutdoorPvp(iter->second);
        if (!Pvp)
        {
            TC_LOG_ERROR(LOG_FILTER_OUTDOORPVP, "Could not initialize OutdoorPvP object for type ID %u; got nullptr pointer from script.", uint32(i));
            continue;
        }

        if (!Pvp->SetupOutdoorPvp())
        {
            TC_LOG_ERROR(LOG_FILTER_OUTDOORPVP, "Could not initialize OutdoorPvP object for type ID %u; SetupOutdoorPvp failed.", uint32(i));
            delete Pvp;
            continue;
        }

        m_OutdoorPvpSet.push_back(Pvp);
    }

    TC_LOG_INFO(LOG_FILTER_SERVER_LOADING, ">> Loaded %u outdoor PvP definitions in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

void OutdoorPvpMgr::AddZone(uint32 zoneid, OutdoorPvp* handle)
{
    m_OutdoorPvpZone[zoneid] = handle;
    if (AreaTableEntry const* areaEntry = sAreaTableStore.LookupEntry(zoneid))
    {
        m_OutdoorPvpMap[areaEntry->ContinentID].insert(handle);

        MapEntry const* entry = sMapStore.LookupEntry(areaEntry->ContinentID);
        if (!entry)
            return;

        handle->m_zoneSet.insert(areaEntry->ParentAreaID ? areaEntry->ParentAreaID : zoneid);

        if (Map* map = entry->CanCreatedZone() ? sMapMgr->FindMap(areaEntry->ContinentID, zoneid) : sMapMgr->CreateBaseMap(areaEntry->ContinentID))
        {
            if (!map->OutdoorPvpList)
                map->OutdoorPvpList = GetOutdoorPvpMap(areaEntry->ContinentID);
            handle->SetMap(map);
            handle->Initialize(zoneid);
        }
    }
}

std::set<OutdoorPvp*>* OutdoorPvpMgr::GetOutdoorPvpMap(uint32 ContinentID)
{
    return Trinity::Containers::MapGetValuePtr(m_OutdoorPvpMap, ContinentID);
}

void OutdoorPvpMgr::HandlePlayerEnterZone(ObjectGuid guid, uint32 zoneid)
{
    OutdoorPvpZone::iterator itr = m_OutdoorPvpZone.find(zoneid);
    if (itr == m_OutdoorPvpZone.end())
        return;

    itr->second->HandlePlayerEnterZone(guid, zoneid);
}

void OutdoorPvpMgr::HandlePlayerLeaveZone(ObjectGuid guid, uint32 zoneid)
{
    OutdoorPvpZone::iterator itr = m_OutdoorPvpZone.find(zoneid);
    if (itr == m_OutdoorPvpZone.end())
        return;

    itr->second->HandlePlayerLeaveZone(guid, zoneid);
}

void OutdoorPvpMgr::HandlePlayerEnterMap(ObjectGuid guid, uint32 zoneID)
{
    auto itr = m_OutdoorPvpZone.find(zoneID);
    if (itr == m_OutdoorPvpZone.end())
        return;
    
    itr->second->HandlePlayerEnterMap(guid, zoneID);
}

void OutdoorPvpMgr::HandlePlayerLeaveMap(ObjectGuid guid, uint32 zoneID)
{
    auto itr = m_OutdoorPvpMap.find(zoneID);
    if (itr == m_OutdoorPvpMap.end())
        return;

    for (auto v : itr->second)
        v->HandlePlayerLeaveMap(guid, zoneID);
}

void OutdoorPvpMgr::HandlePlayerEnterArea(ObjectGuid guid, uint32 areaID)
{
    auto itr = m_OutdoorPvpZone.find(areaID);
    if (itr == m_OutdoorPvpZone.end())
        return;

    itr->second->HandlePlayerEnterArea(guid, areaID);
}

void OutdoorPvpMgr::HandlePlayerLeaveArea(ObjectGuid guid, uint32 areaID)
{
    auto itr = m_OutdoorPvpZone.find(areaID);
    if (itr == m_OutdoorPvpZone.end())
        return;

    itr->second->HandlePlayerLeaveArea(guid, areaID);
}

OutdoorPvp* OutdoorPvpMgr::GetOutdoorPvpToZoneId(uint32 zoneid)
{
    return Trinity::Containers::MapGetValuePtr(m_OutdoorPvpZone, zoneid);
}

void OutdoorPvpMgr::Update(uint32 diff)
{
    m_UpdateTimer += diff;
    if (m_UpdateTimer > OUTDOORPVP_OBJECTIVE_UPDATE_INTERVAL)
    {
        for (OutdoorPvpSet::iterator itr = m_OutdoorPvpSet.begin(); itr != m_OutdoorPvpSet.end(); ++itr)
            (*itr)->Update(m_UpdateTimer);
        m_UpdateTimer = 0;
    }
}

bool OutdoorPvpMgr::HandleCustomSpell(Player* player, uint32 spellId, GameObject* go)
{
    for (OutdoorPvpSet::iterator itr = m_OutdoorPvpSet.begin(); itr != m_OutdoorPvpSet.end(); ++itr)
    {
        if ((*itr)->HandleCustomSpell(player, spellId, go))
            return true;
    }
    return false;
}

ZoneScript* OutdoorPvpMgr::GetZoneScript(uint32 zoneId)
{
    return Trinity::Containers::MapGetValuePtr(m_OutdoorPvpZone, zoneId);
}

bool OutdoorPvpMgr::HandleOpenGo(Player* player, ObjectGuid guid)
{
    for (OutdoorPvpSet::iterator itr = m_OutdoorPvpSet.begin(); itr != m_OutdoorPvpSet.end(); ++itr)
    {
        if ((*itr)->HandleOpenGo(player, guid))
            return true;
    }
    return false;
}

void OutdoorPvpMgr::HandleGossipOption(Player* player, ObjectGuid guid, uint32 gossipid)
{
    for (OutdoorPvpSet::iterator itr = m_OutdoorPvpSet.begin(); itr != m_OutdoorPvpSet.end(); ++itr)
    {
        if ((*itr)->HandleGossipOption(player, guid, gossipid))
            return;
    }
}

bool OutdoorPvpMgr::CanTalkTo(Player* player, Creature* creature, GossipMenuItems const& gso)
{
    for (OutdoorPvpSet::iterator itr = m_OutdoorPvpSet.begin(); itr != m_OutdoorPvpSet.end(); ++itr)
    {
        if ((*itr)->CanTalkTo(player, creature, gso))
            return true;
    }
    return false;
}

void OutdoorPvpMgr::HandleDropFlag(Player* player, uint32 spellId)
{
    for (OutdoorPvpSet::iterator itr = m_OutdoorPvpSet.begin(); itr != m_OutdoorPvpSet.end(); ++itr)
    {
        if ((*itr)->HandleDropFlag(player, spellId))
            return;
    }
}

void OutdoorPvpMgr::HandleGameEventStart(uint32 event)
{
    for (OutdoorPvpSet::iterator itr = m_OutdoorPvpSet.begin(); itr != m_OutdoorPvpSet.end(); ++itr)
    {
        (*itr)->HandleGameEventStart(event);
    }
}

void OutdoorPvpMgr::HandlePlayerResurrects(Player* player, uint32 zoneid)
{
    OutdoorPvpZone::iterator itr = m_OutdoorPvpZone.find(zoneid);
    if (itr == m_OutdoorPvpZone.end())
        return;

    if (itr->second->HasPlayer(player))
        itr->second->HandlePlayerResurrects(player, zoneid);
}
