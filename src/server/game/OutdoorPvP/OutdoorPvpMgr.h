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

#ifndef OUTDOOR_PVP_MGR_H_
#define OUTDOOR_PVP_MGR_H_

#define OUTDOORPVP_OBJECTIVE_UPDATE_INTERVAL 1000

#include "OutdoorPvp.h"

class Player;
class GameObject;
class Creature;
class ZoneScript;
struct GossipMenuItems;

struct OutdoorPvpData
{
    OutdoorPvpTypes TypeId;
    uint32 ScriptId;
};

// class to handle player enter / leave / areatrigger / GO use events
class OutdoorPvpMgr
{
        OutdoorPvpMgr();
        ~OutdoorPvpMgr() {}

    public:
        static OutdoorPvpMgr* instance();

        // create outdoor PvP events
        void InitOutdoorPvp();

        // cleanup
        void Die();

        // called when a player enters an outdoor PvP area
        void HandlePlayerEnterZone(ObjectGuid guid, uint32 areaflag);

        // called when player leaves an outdoor PvP area
        void HandlePlayerLeaveZone(ObjectGuid guid, uint32 areaflag);

        // called when a player enters an outdoor PvP map
        void HandlePlayerEnterMap(ObjectGuid guid, uint32 zoneID);

        // called when a player leaves an outdoor PvP map
        void HandlePlayerLeaveMap(ObjectGuid guid, uint32 zoneID);

        // called when a player enters an outdoor PvP area
        void HandlePlayerEnterArea(ObjectGuid guid, uint32 aeaID);

        // called when a player leaves an outdoor PvP area
        void HandlePlayerLeaveArea(ObjectGuid guid, uint32 aeaID);

        // called when player resurrects
        void HandlePlayerResurrects(Player* player, uint32 areaflag);

        // return assigned outdoor PvP
        OutdoorPvp* GetOutdoorPvpToZoneId(uint32 zoneid);

        // handle custom (non-exist in dbc) spell if registered
        bool HandleCustomSpell(Player* player, uint32 spellId, GameObject* go);

        // handle custom go if registered
        bool HandleOpenGo(Player* player, ObjectGuid guid);

        ZoneScript* GetZoneScript(uint32 zoneId);

        void AddZone(uint32 zoneid, OutdoorPvp* handle);

        std::set<OutdoorPvp*>* GetOutdoorPvpMap(uint32 MapID);

        void Update(uint32 diff);

        void HandleGossipOption(Player* player, ObjectGuid guid, uint32 gossipid);

        bool CanTalkTo(Player* player, Creature* creature, GossipMenuItems const& gso);

        void HandleDropFlag(Player* player, uint32 spellId);

        void HandleGameEventStart(uint32 event);

        OutdoorPvpData* GetOutdoorPvpData(OutdoorPvpTypes type) { return m_OutdoorPvpDatas[type]; }
        void AddOutdoorPvp(OutdoorPvp* pvp) { m_OutdoorPvpSet.push_back(pvp); }
    private:
        typedef std::vector<OutdoorPvp*> OutdoorPvpSet;
        typedef std::map<uint32 /* zoneid */, OutdoorPvp*> OutdoorPvpZone;
        typedef std::map<uint32 /* mapId */, std::set<OutdoorPvp*>> OutdoorPvpMap;
        typedef std::map<OutdoorPvpTypes, OutdoorPvpData*> OutdoorPvpDataMap;

        // contains all initiated outdoor PvP events
        // used when initing / cleaning up
        OutdoorPvpSet  m_OutdoorPvpSet;

        // maps the zone ids to an outdoor PvP event
        // used in player event handling
        OutdoorPvpZone m_OutdoorPvpZone;
        OutdoorPvpMap m_OutdoorPvpMap;

        // Holds the outdoor PvP templates
        OutdoorPvpDataMap m_OutdoorPvpDatas;

        // update interval
        uint32 m_UpdateTimer;
};

#define sOutdoorPvpMgr OutdoorPvpMgr::instance()

#endif /*OUTDOOR_PVP_MGR_H_*/
