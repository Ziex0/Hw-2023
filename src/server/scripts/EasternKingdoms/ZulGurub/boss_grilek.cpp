/*
 * Copyright (C) 2023 UpdateCore <http://www.Heaven-Wow.Com>
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
 */

/* ScriptData
SDName: Boss_Grilek
SD%Complete: 100
SDComment:
SDCategory: Zul'Gurub
EndScriptData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "zulgurub.h"

enum Spells
{
    SPELL_AVATAR                    = 24646, // Enrage Spell
    SPELL_GROUND_TREMOR             = 6524
};

enum Events
{
    EVENT_AVATAR                    = 0,
    EVENT_GROUND_TREMOR             = 1
};

class boss_grilek : public CreatureScript // grilek
{
    public: boss_grilek() : CreatureScript("boss_grilek") {}

        struct boss_grilekAI : public BossAI
        {
            boss_grilekAI(Creature* creature) : BossAI(creature, DATA_EDGE_OF_MADNESS) {}

            void Reset()
            {
                _Reset();
            }

            void JustDied(Unit* /*killer*/)
            {
                _JustDied();
            }

            void EnterCombat(Unit* /*who*/)
            {
                _EnterCombat();
                events.ScheduleEvent(EVENT_AVATAR, urand(15000, 25000));
                events.ScheduleEvent(EVENT_GROUND_TREMOR, urand(15000, 25000));
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_AVATAR:
                            DoCast(me, SPELL_AVATAR);
                            if (Unit* victim = me->GetVictim())
                            {
                                if (DoGetThreat(victim))
                                    DoModifyThreatPercent(victim, -50);
                            }

                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1))
                                AttackStart(target);
                            events.ScheduleEvent(EVENT_AVATAR, urand(25000, 35000));
                            break;
                        case EVENT_GROUND_TREMOR:
                            DoCastVictim(SPELL_GROUND_TREMOR, true);
                            events.ScheduleEvent(EVENT_GROUND_TREMOR, urand(12000, 16000));
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_grilekAI(creature);
        }
};

void AddSC_boss_grilek()
{
    new boss_grilek();
}

