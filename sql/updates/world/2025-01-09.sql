-- Fix Ancient Mana Shard game object drop rates
UPDATE `gameobject_loot_template` SET `ChanceOrQuestChance` = 100 where `item` = -1155 and `mincountOrRef` = 10;