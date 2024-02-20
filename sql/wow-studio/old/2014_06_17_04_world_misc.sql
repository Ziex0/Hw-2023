-- Curing the Sick
DELETE FROM `creature_queststarter` WHERE `quest` = 6124;
DELETE FROM `gameobject_queststarter` WHERE `quest` = 6124;
UPDATE `item_template` SET `StartQuest`=0 WHERE `StartQuest` = 6124;
INSERT INTO `creature_queststarter` (`id`, `quest`) VALUES (3702, 6124);
UPDATE `creature_template` SET `npcflag`=`npcflag`|2 WHERE `entry` = 3702;
DELETE FROM `creature_questender` WHERE `quest` = 6124;
DELETE FROM `gameobject_questender` WHERE `quest` = 6124;
INSERT INTO `creature_questender` (`id`, `quest`) VALUES (11802, 6124);
UPDATE `creature_template` SET `npcflag`=`npcflag`|2 WHERE `entry`=11802;
REPLACE INTO `quest_template` (`Id`, `Method`, `Level`, `MinLevel`, `MaxLevel`, `ZoneOrSort`, `Type`, `SuggestedPlayers`, `LimitTime`, `RequiredClasses`, `RequiredRaces`, `RequiredSkillId`, `RequiredSkillPoints`, `RequiredFactionId1`, `RequiredFactionId2`, `RequiredFactionValue1`, `RequiredFactionValue2`, `RequiredMinRepFaction`, `RequiredMaxRepFaction`, `RequiredMinRepValue`, `RequiredMaxRepValue`, `PrevQuestId`, `NextQuestId`, `ExclusiveGroup`, `NextQuestIdChain`, `RewardXPId`, `RewardOrRequiredMoney`, `RewardMoneyMaxLevel`, `RewardSpell`, `RewardSpellCast`, `RewardHonor`, `RewardHonorMultiplier`, `RewardMailTemplateId`, `RewardMailDelay`, `SourceItemId`, `SourceItemCount`, `SourceSpellId`, `Flags`, `SpecialFlags`, `RewardTitleId`, `RequiredPlayerKills`, `RewardTalents`, `RewardArenaPoints`, `RewardItemId1`, `RewardItemId2`, `RewardItemId3`, `RewardItemId4`, `RewardItemCount1`, `RewardItemCount2`, `RewardItemCount3`, `RewardItemCount4`, `RewardChoiceItemId1`, `RewardChoiceItemId2`, `RewardChoiceItemId3`, `RewardChoiceItemId4`, `RewardChoiceItemId5`, `RewardChoiceItemId6`, `RewardChoiceItemCount1`, `RewardChoiceItemCount2`, `RewardChoiceItemCount3`, `RewardChoiceItemCount4`, `RewardChoiceItemCount5`, `RewardChoiceItemCount6`, `RewardFactionId1`, `RewardFactionId2`, `RewardFactionId3`, `RewardFactionId4`, `RewardFactionId5`, `RewardFactionValueId1`, `RewardFactionValueId2`, `RewardFactionValueId3`, `RewardFactionValueId4`, `RewardFactionValueId5`, `RewardFactionValueIdOverride1`, `RewardFactionValueIdOverride2`, `RewardFactionValueIdOverride3`, `RewardFactionValueIdOverride4`, `RewardFactionValueIdOverride5`, `PointMapId`, `PointX`, `PointY`, `PointOption`, `Title`, `Objectives`, `Details`, `EndText`, `OfferRewardText`, `RequestItemsText`, `CompletedText`, `RequiredNpcOrGo1`, `RequiredNpcOrGo2`, `RequiredNpcOrGo3`, `RequiredNpcOrGo4`, `RequiredNpcOrGoCount1`, `RequiredNpcOrGoCount2`, `RequiredNpcOrGoCount3`, `RequiredNpcOrGoCount4`, `RequiredSourceItemId1`, `RequiredSourceItemId2`, `RequiredSourceItemId3`, `RequiredSourceItemId4`, `RequiredSourceItemCount1`, `RequiredSourceItemCount2`, `RequiredSourceItemCount3`, `RequiredSourceItemCount4`, `RequiredItemId1`, `RequiredItemId2`, `RequiredItemId3`, `RequiredItemId4`, `RequiredItemId5`, `RequiredItemId6`, `RequiredItemCount1`, `RequiredItemCount2`, `RequiredItemCount3`, `RequiredItemCount4`, `RequiredItemCount5`, `RequiredItemCount6`, `Unknown0`, `ObjectiveText1`, `ObjectiveText2`, `ObjectiveText3`, `ObjectiveText4`, `DetailsEmote1`, `DetailsEmote2`, `DetailsEmote3`, `DetailsEmote4`, `DetailsEmoteDelay1`, `DetailsEmoteDelay2`, `DetailsEmoteDelay3`, `DetailsEmoteDelay4`, `EmoteOnIncomplete`, `EmoteOnComplete`, `OfferRewardEmote1`, `OfferRewardEmote2`, `OfferRewardEmote3`, `OfferRewardEmote4`, `OfferRewardEmoteDelay1`, `OfferRewardEmoteDelay2`, `OfferRewardEmoteDelay3`, `OfferRewardEmoteDelay4`, `VerifiedBuild`) VALUES (6124, 2, -1, 14, 0, -263, 0, 0, 0, 1024, 1101, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6123, 0, 0, 6125, 4, 0, 99300, 0, 0, 0, 0, 0, 0, 15826, 1, 0, 0, 32, 0, 0, 0, 0, 15866, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 609, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Curing the Sick', 'Use the Curative Animal Salve on 10 Sickly Deer that are located throughout Darkshore; doing so should cure them.  Sickly Deer have been reported starting south of the Cliffspring River to the north of Auberdine and extending all the way into southern Darkshore where the edge of Ashenvale begins.', 'The amount of salve made out of the reagents you brought me is good enough for ten doses, $N.  While I work with the village to try and make some more salve, I\'d like for you to help us get a head start.  All around Darkshore are sickly deer; use the salve on them and cure their malaise.$B$BDendrite Starblaze in Moonglade will want to talk to you when you\'re done, I\'m sure.  Please extend Auberdine\'s thanks to the Cenarion Circle there... and let me say thanks to you directly for the help you\'ve given!', '', 'You have done well in tending to the sickly deer of Darkshore; they are unwitting victims of a greater taint and corruption that is spreading all throughout the land.  There are those in Darnassus who choose to recognize this threat... and there are those who ignore the growing signs.  I hope you will not be one to put blinders on about what facts stare you in the face, $N.$B$BRegardless, you\'ve proven your worth as a friend of nature and the Circle - take this as a symbol of such.', 'Have you completed what was asked of you by Alanndarian Nightsong of Auberdine? Your work is not complete unless it is.', 'Return to Dendrite Starblaze at Nighthaven in Moonglade.', 12298, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Sickly Deer cured', '', '', '', 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 12340);

UPDATE `locales_quest` SET `ObjectiveText1_loc3` = 'Krankes Wild geheilt' WHERE `Id` = 6124;


UPDATE `creature_template` SET `ainame`='SmartAI' WHERE `entry` IN (12298);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (12298) AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(12298,0,0,0,8,0,100,0,19512,0,0,0,33,12298,0,0,0,0,0,7,0,0,0,0,0,0,0,'Heilung der Kranken Quest Credit, On Spell Hit (Salbe auftragen) - Quest Credit');