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
#include "OutdoorPvpRG.h"
#include "OutdoorPvpMgr.h"

Position summon_pos[3]
{
    {3187.85f, 7262.52f, 35.0026f, 3.03f},
    {3182.00f, 7265.00f, 36.0833f, 0.00f},
    {3181.76f, 7257.72f, 34.1580f, 4.67f}
};

OutdoorPvpRG::OutdoorPvpRG()
{
    m_TypeId = OUTDOOR_PVP_RG;
    m_summonTimer = 0;
    m_canSummon = true;
}

bool OutdoorPvpRG::SetupOutdoorPvp()
{
    RegisterZone(BLACK_ROOK_RUMBLE_AREA);

    return true;
}

uint32 ArenaNPCs[4] =
{
    111256, 111141, 110943, 111136
};

void OutdoorPvpRG::HandleKill(Player* killer, Unit* killed)
{
    if (!killer || !killed || !killer->IsPlayer())
        return;

    if (!killed->IsPlayer() && killed->GetEntry() != 111136 && killed->GetEntry() != 111256 &&
        killed->GetEntry() != 111141 && killed->GetEntry() != 110943)
        return;

    ObjectGuid killerGuid = killer->GetGUID();
    ObjectGuid killedGuid = killed->GetGUID();

    killer->KilledMonsterCredit(RG_KILL_CREDIT);
    killer->CastSpell(killer, 212270, true); // Rumbler's Momentum

    for (GuidSet::iterator itr = m_playersInArea.begin(); itr != m_playersInArea.end(); ++itr)
    {
        if (killerGuid == *itr || killerGuid == *itr)
            continue;

        if (Player* player = ObjectAccessor::GetObjectInMap((*itr), m_map, (Player*)nullptr))
            if (player->isAlive())
                player->KilledMonsterCredit(RG_KILL_CREDIT);
    }

    switch (killed->GetEntry())
    {
    case 111256:
    case 111141:
    case 110943:
    case 111136:
        m_canSummon = true;
        break;
    }
}

bool OutdoorPvpRG::Update(uint32 diff)
{
    if (!m_canSummon)
        return true;

    if (!m_playersInArea.empty() && m_playersInArea.size() < 6)
    {
        if (m_summonTimer >= 30000)
        {
            if (TempSummon* summon = m_map->SummonCreature(ArenaNPCs[urand(0,3)], summon_pos[urand(0, 2)], NULL, 20000))
            {
                summon->SetTempSummonType(TEMPSUMMON_CORPSE_DESPAWN);
                summon->SetReactState(REACT_AGGRESSIVE);
                m_canSummon = false;
            }
            m_summonTimer = 0;
        }
        else
            m_summonTimer += diff;
    }
    return true;
}

class OutdoorPvp_ravens_glory : public OutdoorPvpScript
{
    public:

        OutdoorPvp_ravens_glory()
            : OutdoorPvpScript("outdoorpvp_rg")
        {
        }

        OutdoorPvp* GetOutdoorPvp() const override
        {
            return new OutdoorPvpRG();
        }
};

void AddSC_outdoorpvp_rg()
{
    new OutdoorPvp_ravens_glory();
}
