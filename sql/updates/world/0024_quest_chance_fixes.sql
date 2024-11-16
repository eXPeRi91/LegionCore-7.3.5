-- ------------------------------------------------------------------------------------------
-- Fix loot chance for the following quest items
-- 28292 = Archmage Vargoth's Staff
-- 28376 = B'naar Personnel Roster
-- 28475 = Heliotrope Oculus
-- 28479 = Stone of Glacius
-- 28550 = Flaming Torch
-- 28563 = Doomclaw's Hand
-- 28635 = Sunfury Arcanist Robes
-- 28636 = Sunfury Researcher Gloves
-- 28637 = Sunfury Guardsman Medallion
-- 28769 = The Keystone
-- 28786 = Apex's Crystal Focus
-- 28829 = Arklon Crystal Artifact
-- 29026 = Ata'mal Crystal
-- 29163 = Raw Farahlite
-- 29164 = Farahlite Core
-- 29209 = Zaxxis Insignia
-- 29331 = Annals of Kirin'Var
-- 29338 = Loathsome Remnant
-- 29365 = Smithing Hammer
-- 29366 = B'naar Access Crystal
-- 29396 = Coruu Access Crystal
-- 29397 = Duro Access Crystal
-- 29411 = Ara Access Crystal
-- 29591 = Prepared Ethereum Wrapping
-- 29624 = First Half of Socrethar's Stone
-- 29625 = Second Half of Socrethar's Stone
-- 29742 = The Warden's Key
-- 29768 = Hulking Hydra Heart
-- 29797 = Orders From Kael'thas
-- 29801 = Ripfang Lynx Pelt
-- 29822 = Fragment of Dimensius
-- 30596 = Baa'ri Tablet Fragment
-- 30679 = Sunfury Glaive
-- 30645 = Third Fragment of the Cipher of Damnation
-- 30756 (A) / 30579 (H) = Illidari-Bane Shard
-- 30785 = Morgroron's Glaive
-- 30786 = Makazradon's Glaive
-- 30807 = Uvuros' Fiery Mane
-- 30811 = Scroll of Demonic Unbanishing
-- 30819 = Felfire Spleen
-- 30867 = Overdeveloped Felfire Gizzard
-- 31085 = Top Shard of the Alcatraz Key
-- 31086 = Bottom Shard of the Alcatraz Key
-- 31653 = Condensed Nether Gas
-- 31664 = Zuluhed's Key
-- 31956 = Salvaged Ethereum Prison Key

DELETE FROM `creature_loot_template` WHERE NOT `entry` = 19493 AND `item` = 28292;
DELETE FROM `creature_loot_template` WHERE NOT `entry` = 19635 AND `item` = 28376;
DELETE FROM `creature_loot_template` WHERE NOT `entry` = 19926 AND `item` = 28475;
DELETE FROM `creature_loot_template` WHERE NOT `entry` = 19657 AND `item` = 28479;
DELETE FROM `creature_loot_template` WHERE NOT `entry` = 20221 AND `item` = 28550;
DELETE FROM `creature_loot_template` WHERE NOT `entry` = 20134 AND `item` = 28635;
DELETE FROM `creature_loot_template` WHERE NOT `entry` = 19940 AND `item` = 28786;
DELETE FROM `creature_loot_template` WHERE NOT `entry` = 20215 AND `item` = 28829;
DELETE FROM `creature_loot_template` WHERE NOT `entry` = 20138 AND `item` = 29026;
DELETE FROM `creature_loot_template` WHERE NOT `entry` = 20202 AND `item` = 29164;
DELETE FROM `creature_loot_template` WHERE NOT `entry` IN (18875, 19641, 19642) AND `item` = 29209;
DELETE FROM `creature_loot_template` WHERE NOT `entry` = 19543 AND `item` = 29331;
DELETE FROM `creature_loot_template` WHERE NOT `entry` = 20409 AND `item` = 29365;
DELETE FROM `creature_loot_template` WHERE NOT `entry` = 20416 AND `item` = 29366;
DELETE FROM `creature_loot_template` WHERE NOT `entry` = 20397 AND `item` = 29396;
DELETE FROM `creature_loot_template` WHERE NOT `entry` = 20685 AND `item` = 29411;
DELETE FROM `creature_loot_template` WHERE NOT `entry` = 20770 AND `item` = 29742;
DELETE FROM `creature_loot_template` WHERE NOT `entry` IN (18860, 20285, 20326) AND `item` = 29797;
DELETE FROM `creature_loot_template` WHERE NOT `entry` = 20671 AND `item` = 29801;
DELETE FROM `creature_loot_template` WHERE NOT `entry` = 21499 AND `item` IN (30756, 30579);
DELETE FROM `creature_loot_template` WHERE NOT `entry` IN (21179, 21180) AND `item` = 30679;
DELETE FROM `creature_loot_template` WHERE NOT `entry` = 21500 AND `item` = 30785;
DELETE FROM `creature_loot_template` WHERE NOT `entry` IN (21503, 21505) AND `item` = 30811;
DELETE FROM `creature_loot_template` WHERE NOT `entry` = 21408 AND `item` = 30819;
DELETE FROM `creature_loot_template` WHERE NOT `entry` = 16949 AND `item` = 31653;
DELETE FROM `creature_loot_template` WHERE NOT `entry` IN (20452, 20453, 20454, 20456, 20458, 20459, 20474, 20727, 20770, 20854, 23008) AND `item` = 31956;

-- Quest only drops
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -100 WHERE `item` IN (28292, 28376, 28475, 28479, 28550, 28563, 28635, 28636, 28637, 28769, 28786, 28829, 29026, 29164, 29331, 29366, 29396, 29397, 29411, 29591, 29742, 29768, 30645, 30785, 30786, 30807, 30867, 31085, 31086, 31664);
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -80 WHERE `item` IN (29163, 29338, 29365, 29797, 29801, 29822, 30679, 30819, 31653);
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -35 WHERE `item` = 30811;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -20 WHERE `item` = 30596;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -10 WHERE `item` = 31956;

-- 31957 = Ethereum Prisoner I.D. Tag
DELETE FROM `creature_loot_template` WHERE `item` = 31957;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`) VALUES
(20783, 31957, 100, 0, 0, 1, 1, 0),
(20784, 31957, 100, 0, 0, 1, 1, 0),
(20785, 31957, 100, 0, 0, 1, 1, 0),
(20786, 31957, 100, 0, 0, 1, 1, 0),
(20788, 31957, 100, 0, 0, 1, 1, 0),
(20789, 31957, 100, 0, 0, 1, 1, 0),
(20790, 31957, 100, 0, 0, 1, 1, 0);

-- Can always drop
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = 100 WHERE `item` IN (30756, 30579);
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = 65 WHERE `item` = 29209;

-- 29460 = Ethereum Prison Key
DELETE FROM `creature_loot_template` WHERE `entry` = 23385 AND `item` = 29460;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = 100 WHERE `entry` = 23008 AND `item` = 29460;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = 3 WHERE NOT `entry` = 23008 AND `item` = 29460;

-- Needs to be marked as quest only after loot system is fixed!
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = 100 WHERE `item` IN (29624, 29625);

-- ------------------------------------------------------------------------------------------
-- Fix loot chance for the following game objects
-- 30596 = Baa'ri Tablet Fragment
-- 30628 = Fel Reaver Power Core
-- 30631 = Fel Reaver Armor Plate
-- 30716 = Ever-Burning Ash

UPDATE `gameobject_loot_template` SET `ChanceOrQuestChance` = -100 WHERE `item` IN (30596, 30628, 30631, 30716);