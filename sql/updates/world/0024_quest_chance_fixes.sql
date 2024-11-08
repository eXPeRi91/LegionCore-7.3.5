--------------------------------------------------------------------------------------------
-- Fix loot chance for the following quest items
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
-- 31664 = Zuluhed's Key

DELETE FROM `creature_loot_template` WHERE NOT `entry` = 21499 AND `item` IN (30756, 30579);
DELETE FROM `creature_loot_template` WHERE NOT `entry` IN (21179, 21180) AND `item` = 30679;
DELETE FROM `creature_loot_template` WHERE NOT `entry` = 21500 AND `item` = 30785;
DELETE FROM `creature_loot_template` WHERE NOT `entry` IN (21503, 21505) AND `item` = 30811;
DELETE FROM `creature_loot_template` WHERE NOT `entry` = 21408 AND `item` = 30819;

-- Quest only drops
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -100 WHERE `item` IN (30645, 30785, 30786, 30807, 30867, 31664);
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -80 WHERE `item` IN (30679, 30819);
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -35 WHERE `item` = 30811;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = -20 WHERE `item` = 30596;

-- Can always drop
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = 100 WHERE `item` IN (30756, 30579);

--------------------------------------------------------------------------------------------
-- Fix loot chance for the following game objects
-- 30596 = Baa'ri Tablet Fragment
-- 30628 = Fel Reaver Power Core
-- 30631 = Fel Reaver Armor Plate
-- 30716 = Ever-Burning Ash

UPDATE `gameobject_loot_template` SET `ChanceOrQuestChance` = -100 WHERE `item` IN (30596, 30628, 30631, 30716);