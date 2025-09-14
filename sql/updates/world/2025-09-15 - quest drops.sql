-- Fix loot chance for the following quest items (from creatures):
--
-- Set the following to 100%
-- 4458 = Sigil of Arathor
-- 34961 = Burglegoggle's Key
-- 34962 = Gurgleboggle's Key
-- 35353 = High Priest Naferset's Scroll
-- 35354 = High Priest Talet-Kha's Scroll
-- 35355 = High Priest Andorath's Scroll
-- 35483 = Glacial Splinter
-- 35484 = Magic-Bound Splinter
-- 35486 = Mechazod's Head
-- 35490 = Arcane Splinter
-- 35648 = Scintillating Fragment
-- 35669 = Energy Core
-- 35774 = Trident of Naz'jan
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -100 WHERE `item` IN (4458, 34961, 34962, 35353, 35354, 35355, 35483, 35484, 35486, 35490, 35648, 35669, 35774);
--
-- Set the following to 70%
-- 35288 = 
-- 35629 = Shimmering Rune
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -70 WHERE `item` IN (35288, 35629);


-- Cleanup bad entries
DELETE FROM `creature_loot_template` WHERE `item` = 34961 AND NOT `entry` = 25726;
DELETE FROM `creature_loot_template` WHERE `item` = 34962 AND NOT `entry` = 25725;
DELETE FROM `creature_loot_template` WHERE `item` = 35288 AND NOT `entry` IN (25680, 25750);
DELETE FROM `creature_loot_template` WHERE `item` = 35355 AND NOT `entry` = 25392;
DELETE FROM `creature_loot_template` WHERE `item` = 35483 AND NOT `entry` = 25709;
DELETE FROM `creature_loot_template` WHERE `item` = 35484 AND NOT `entry` = 25707;
DELETE FROM `creature_loot_template` WHERE `item` = 35586 AND NOT `entry` = 25728;
DELETE FROM `creature_loot_template` WHERE `item` = 35628 AND NOT `entry` = 25720;
DELETE FROM `creature_loot_template` WHERE `item` = 35629 AND NOT `entry` = 25719;
DELETE FROM `creature_loot_template` WHERE `item` = 35648 AND NOT `entry` = 25719;
DELETE FROM `creature_loot_template` WHERE `item` = 35669 AND NOT `entry` = 25712;
DELETE FROM `creature_loot_template` WHERE `item` = 35774 AND NOT `entry` = 26451;


-- Fix loot chance for following, should be 100% POSITIVE chance:
-- 46318 = Hellscream's Missive
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = 100 WHERE `item` IN (46318);

-- Fix loot chance for the following quest items (in game objects):
--
-- Set the following to 100%
-- 22094 = Bloodkelp (this seems to not drop when set to -100? appears to be missing quest objective to get 20 of these)
-- 28283 = Soul Mirror
-- 34709 = Warsong Munitions
-- 56804 = Sheathed Trol'kalar
UPDATE `gameobject_loot_template` SET `ChanceOrQuestChance` = -100 WHERE `item` IN (22094, 28283, 34709, 56804);
DELETE FROM `gameobject_loot_template` WHERE `item` = 56804 AND NOT `entry` = 203450;


-- Fix game objects being interactable when they should not be
-- 181053 = Basket of Bloodkelp
UPDATE `gameobject_template` SET `flags` = 4 WHERE `entry` = 181053;

-- Fix broken game objects not tied to quest like they should be (type, gameobject, item, quest):
-- 181053 = Basket of Bloodkelp (item 22094)
-- 188113 = Frostberry Bush (item 35492)
DELETE FROM `conditions` WHERE `SourceEntry` IN (22094, 35492);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(4, 181053, 22094, 0, 0, 9, 0, 8970, 0, 0, 0, 0, '', ''),
(4, 188113, 35492, 0, 0, 9, 0, 11912, 0, 0, 0, 0, '', '');