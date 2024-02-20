-- The Way to His Heart
UPDATE `creature_template` SET `ainame`='SmartAI' WHERE `entry` IN (24786,24797);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (24786,24797) AND `source_type`=0;
INSERT INTO `smart_scripts` VALUES
('24786','0','0','0','8','0','100','0','44454','0','0','0','29','0','0','24797','0','0','0','7','0','0','0','0','0','0','0','On Spell Hit - Follow Invoker'),
('24786','0','1','2','65','0','100','0','0','0','0','0','11','52148','0','0','0','0','0','1','0','0','0','0','0','0','0','On Follow Complete - Cast 52148'),
('24786','0','2','3','61','0','100','0','0','0','0','0','29','0','0','0','0','0','0','19','24797','10','0','0','0','0','0','Link With Event 1 - Follow Reef Cow'),
('24786','0','3','0','61','0','100','0','0','0','0','0','45','0','1','0','0','0','0','19','24797','10','0','0','0','0','0','Link With Event 2 - Set Data 0 1'),
('24797','0','0','1','38','0','100','0','0','1','0','0','11','52148','0','0','0','0','0','1','0','0','0','0','0','0','0','On Data Set 0 1 - Cast 52148'),
('24797','0','1','2','61','0','100','0','0','0','0','0','66','0','0','0','0','0','0','19','24786','0','0','0','0','0','0','Link With Event 0 - Set orientation'),
('24797','0','2','3','61','0','100','0','0','0','0','0','15','11472','0','0','0','0','0','18','20','0','0','0','0','0','0','Link With Event 1 - Give Quest Credit'),
('24797','0','3','0','61','0','100','0','0','0','0','0','41','4200','0','0','0','0','0','1','0','0','0','0','0','0','0','Link With Event 2 - Despawn');

DELETE FROM `spell_scripts` WHERE `id`=21014;
INSERT INTO `spell_scripts` VALUES
('21014','0','0','17','34127','1','0','0','0','0','0');