/////////////////////////////////////////////////////////////////////////////
//         				   Developed by Zie                                //
//                     Copyright (C) 2015 Zie                              //
//                          Thesatria.Com                                  //
/////////////////////////////////////////////////////////////////////////////

#include "ScriptPCH.h"

class npc_ex_emblem : public CreatureScript
{
public:
    npc_ex_emblem() : CreatureScript("npc_ex_emblem") { }
	
    bool OnGossipHello(Player *player, Creature *_creature)
    {
        if (player->isInCombat())
        {
            player->CLOSE_GOSSIP_MENU();
            _creature->MonsterWhisper("You are in combat!", player->GetGUID());
            return true;
        }
        else
        {			
            player->ADD_GOSSIP_ITEM( 4, "|cffADD8E6|TInterface\\icons\\Achievement_Dungeon_Icecrown_Frostmourne:24|tExcahnge 25000 Honor to 250 Arena"      					, GOSSIP_SENDER_MAIN, 3); //Change the ID below
            player->ADD_GOSSIP_ITEM( 4, "|cffADD8E6|TInterface\\icons\\Achievement_Dungeon_Icecrown_Frostmourne:24|tExcahnge 250 Arena to 20000 Honor"       					, GOSSIP_SENDER_MAIN, 4); //Change the ID below
            player->ADD_GOSSIP_ITEM( 4, "|cffADD8E6|TInterface\\icons\\Achievement_Dungeon_Icecrown_Frostmourne:24|tExcahnge 500 Golden Coin to 40 Love Event Token" 			, GOSSIP_SENDER_MAIN, 5); //Change the stats below
            player->ADD_GOSSIP_ITEM( 4, "|cffADD8E6|TInterface\\icons\\Achievement_Dungeon_Icecrown_Frostmourne:24|tExcahnge 20 Love Event Token to 100 Firdaus PvP Credit"   	, GOSSIP_SENDER_MAIN, 6); //Change the stats below
			player->PlayerTalkClass->SendGossipMenu(907, _creature->GetGUID());
        }

        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _creature->GetGUID());         
        return true;
    }

    bool OnGossipSelect(Player *player, Creature *_creature, uint32 sender, uint32 uiAction)
    {
        if (sender == GOSSIP_SENDER_MAIN)
        {
            player->PlayerTalkClass->ClearMenus();
            switch(uiAction)
            {
			case 3: //Honor
			if (player->GetHonorPoints() >= 25000)
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->ModifyHonorPoints(-25000);
                    player->ModifyArenaPoints(+250);
                    _creature->MonsterWhisper("You exchanged succesfully!", player->GetGUID());
                }
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                     _creature->MonsterWhisper("I'm sorry, but you don't have enough honor points to make this exchange!.", player->GetGUID());
                    return false;
                }break;
				
			case 4:	//Arena
			if (player->GetArenaPoints() >= 250)
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->ModifyArenaPoints(-250);
                    player->ModifyHonorPoints(+20000);
                    _creature->MonsterWhisper("You exchanged succesfully!", player->GetGUID());
                }
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                     _creature->MonsterWhisper("I'm sorry, but you don't have enough arena points to make this exchange!.", player->GetGUID());
                    return false;
                }break;
				
            case 5: //Golden Coin 
                if (player->HasItemCount( 37829, 500, false )) //golden peral
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->DestroyItemCount(37829, 500, true, false);
                    player->AddItem(49927, 40 );
                    _creature->MonsterWhisper("You exchanged successfully!", player->GetGUID());
                }
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    _creature->MonsterWhisper("I'm sorry, but you don't have enough arena points to make this exchange!.", player->GetGUID());
                    return false;
                }
                break;
			case 6: //Love Event Token
                if (player->HasItemCount( 49927, 20, false ))
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->DestroyItemCount(49927, 20, true, false);
                    player->AddItem(38186, 100);
                    _creature->MonsterWhisper("You exchanged successfully!", player->GetGUID());
                }
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    _creature->MonsterWhisper("I'm sorry, but you don't have enough arena points to make this exchange!.", player->GetGUID());
                    return false;
                }
                break;
				
            } 
        } 
        return true;
    } 
};

void AddSC_npc_ex_emblem()
{
    new npc_ex_emblem();
}