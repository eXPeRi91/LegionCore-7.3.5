-- Fix loot chance for the following quest items (from creatures):
--
-- Set the following to 100%:
-- 4103 = Shackle Key (this was positive before)
-- 4458 = Sigil of Arathor
-- 5851 = Cozzle's Key
-- 8707 = Gahz'rilla's Electrified Scale
-- 9234 = Tiara of the Deep
-- 19023 = Katoom's Best Lure
-- 23735 = Grand Warlock's Amulet
-- 24472 = Boss Grog'ak's Head
-- 25767 = Raliq's Debt
-- 25768 = Coosh'coosh's Debt
-- 25769 = Floon's Debt
-- 25852 = Tail Feather of Torgos
-- 27943 = Chieftain Mummaki's Totem
-- 28677 = The Book of the Dead
-- 30356 = Shadowmoon Tuber
-- 30442 = Crystalline Key
-- 30453 = Second Fragment of the Cipher of Damnation
-- 30617 = Stormrage Missive
-- 30618 = Trachela's Carcass (this was positive before)
-- 30649 = Orders from Akama
-- 30689 = Razuun's Orders (this was positive before)
-- 30691 = Haalum's Medallion Fragment
-- 30692 = Eykenen's Medallion Fragment
-- 30693 = Lakaan's Madallion Fragment
-- 30694 = Uylaru's Madallion Fragment
-- 30797 = Gorefiend's Armor
-- 30799 = Gorefiend's Cloak
-- 30800 = Gorefiend's Truncheon
-- 30828 = Vial of Underworld Loam
-- 30851 = Felspine's Hide
-- 31169 = Sketh'lon War Totem
-- 31307 = Heart of Fury (this was positive before)
-- 31716 = Unused Axe of the Executioner
-- 31826 = Enormous Bone Worm Organs
-- 32666 = Hardened Hide of Tyrantus
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
-- 52346 = Commander Arrington's Head
-- 52347 = Darkblade Cyn's Head
-- 52349 = Alexi Silenthowl's Head
-- 52559 = Fickle Heart
-- 56469 = Alliance Attack Plans
-- 58082 = Direglob Sample
-- 60772 = Cult Orders
-- 60867 = Smither's Logbook
-- 62053 = Obsidian Power Core
-- 62055 = Titan Power Core
-- 72574 = Irradiated Gear
-- 72597 = O'mrogg's Warcloth
-- 122746 = Head of Thane Wildsky
-- 124672 = Sargerite Keystone (this was positive before)
-- 127411 = Rotbeak's Head
-- 127863 = Prison Keys
-- 128508 = Gutspill's Head
-- 128509 = Rumblehoof's Head
-- 129911 = Scale of Drakol'nir
-- 132560 = Essence of the Whirlwind
-- 138022 = Spitefeather's Beak
-- 138023 = Stonefang's Jaw
-- 138150 = Broketooth's Ruby Amulet
-- 139276 = Sixtriggers' Key (this was positive before)
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -100 WHERE `item` IN (4103, 4458, 5851, 8707, 9234, 19023, 23735, 24472, 25767, 25768, 25769, 25852, 27943, 28677, 30356, 30442, 30453, 30617, 30618, 30649, 30689, 30691, 30692, 30693, 30694, 30797, 30799, 30800, 30828, 30851, 31169, 31307, 31716, 31826, 32666, 34961, 34962, 35353, 35354, 35355, 35483, 35484, 35486, 35490, 35648, 35669, 35774, 52346, 52347, 52349, 52559, 56469, 58082, 60772, 60867, 62053, 62055, 72574, 72597, 122746, 124672, 127411, 127863, 128508, 128509, 129911, 132560, 138022, 138023, 138150, 139276);
--
-- Set the following to 70%:
-- 35288 = Uncured Caribou Hide
-- 35629 = Shimmering Rune
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -70 WHERE `item` IN (35288, 35629);


-- Cleanup bad entries:
DELETE FROM `creature_loot_template` WHERE `item` = 24472 AND NOT `entry` = 18159;
DELETE FROM `creature_loot_template` WHERE `item` = 30689 AND NOT `entry` = 21287;
DELETE FROM `creature_loot_template` WHERE `item` = 30691 AND NOT `entry` = 21711;
DELETE FROM `creature_loot_template` WHERE `item` = 30692 AND NOT `entry` = 21709;
DELETE FROM `creature_loot_template` WHERE `item` = 30694 AND NOT `entry` = 21710;
DELETE FROM `creature_loot_template` WHERE `item` = 31169 AND NOT `entry` = 22025;
DELETE FROM `creature_loot_template` WHERE `item` = 31271 AND NOT `entry` = 22012;
DELETE FROM `creature_loot_template` WHERE `item` = 31345 AND NOT `entry` = 21979;
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


-- These should not drop at all:
DELETE FROM `creature_loot_template` WHERE `item` = 34972;


-- Fix loot chance for following, should be 100% POSITIVE chance:
-- 16305 = Sharptalon's Claw
-- 31345 = The Journal of Val'zareq
-- 46318 = Hellscream's Missive
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = 100 WHERE `item` IN (16305, 31345, 46318);

-- Fix loot chance for the following quest items (in game objects):
--
-- Set the following to 100%
-- 22094 = Bloodkelp (this seems to not drop when set to -100? appears to be missing quest objective to get 20 of these)
-- 28283 = Soul Mirror
-- 34709 = Warsong Munitions
-- 56804 = Sheathed Trol'kalar
UPDATE `gameobject_loot_template` SET `ChanceOrQuestChance` = -100 WHERE `item` IN (22094, 28283, 34709, 56804);
DELETE FROM `gameobject_loot_template` WHERE `item` = 56804 AND NOT `entry` = 203450;


-- Fix game objects being interactable when they should not be unless you have the quest:
-- 181053 = Basket of Bloodkelp
UPDATE `gameobject_template` SET `flags` = 4 WHERE `entry` = 181053;


-- Fix missing game objects from the world:
-- 188113 = Frostberry Bush
UPDATE `gameobject_template` SET `type` = 3 WHERE `entry` = 188113;


-- Fix broken game objects not tied to quest like they should be (type, gameobject, item, quest):
-- 181053 = Basket of Bloodkelp (item 22094)
-- 188113 = Frostberry Bush (item 35492)
DELETE FROM `conditions` WHERE `SourceEntry` IN (22094, 35492);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(4, 181053, 22094, 0, 0, 9, 0, 8970, 0, 0, 0, 0, '', ''),
(4, 188113, 35492, 0, 0, 9, 0, 11912, 0, 0, 0, 0, '', '');