-- Fix spawn times to be reasonable for groups, it is silly to have to wait 10 minutes in a group of 2 or 3 just to finish a single quest


-- ------------------------------------------------------------------------------------------
-- Fix spawn times for quest items that are single container, these will be 2 second respawns
-- 4483 = Burning Key (2689)
-- 4484 = Cresting Key (2691)
-- 4485 = Thundering Key (2690)
-- 4530 = Trelane's Phylactery (2717)
-- 4531 = Trelane's Orb (2716)
-- 4532 = Trelane's Ember Agate (2718)
-- 30628 = Fel Reaver Power Core (184859)
-- 30631 = Fel Reaver Armor Plate (184860)
-- 48921 = Sarcen Stone (195513)
-- 49012 = Abjurer's Manual (195584)
UPDATE `gameobject` SET `spawntimesecs` = 2 where `id` IN (2689, 2690, 2691, 2716, 2717, 2718) AND `zoneId` = 45;
UPDATE `gameobject` SET `spawntimesecs` = 2 where `id` IN (184859, 184860, 195513, 195584);

-- The following also have position fixes
-- 49642 = Heart of Arkkoroc
UPDATE `gameobject` SET `spawntimesecs` = 2, `position_x` = 3543.24, `position_y` = -5138.04, `position_z` = 88.5, `orientation` = 1.87 WHERE `id` = 200298;


-- ------------------------------------------------------------------------------------------
-- Fix spawn times for quest items in multiple containers, these will be 15 second respawns
-- 49639 = Highborne Tablet (199329, 199330, 199331, 199332)
UPDATE `gameobject` SET `spawntimesecs` = 15 where `id` IN (199329, 199330, 199331, 199332);


-- ------------------------------------------------------------------------------------------
-- Fix spawn times for quest items in multiple containers, these will be 20 second respawns
-- 30596 = Baa'ri Tablet Fragment (184869, 184870)
-- 30716 = Ever-Burning Ash (184948)
-- 49162 = Kawphi Bean (195686)
UPDATE `gameobject` SET `spawntimesecs` = 20 where `id` IN (184869, 184870, 184948, 195686);


-- ------------------------------------------------------------------------------------------
-- Fix spawn times for quest items in multiple containers, these will be 30 second respawns
-- 48128 = Mountainfoot Iron (195447, 195448)
-- 49082 = Living Ire Thyme (195587)
-- 49365 = Briaroot Brew (196834)
UPDATE `gameobject` SET `spawntimesecs` = 30 where `id` IN (195447, 195448, 195587, 196834);


-- ------------------------------------------------------------------------------------------
-- Fix spawn times for quest items in multiple containers, these will be 120 second respawns
-- 24468 = Burstcap Mushroom (182095)
-- 34709 = Warsong Munitions (23083, 187661, 187660, 187659)
UPDATE `gameobject` SET `spawntimesecs` = 120 where `id` IN (23083, 182095, 187661, 187660, 187659);


-- ------------------------------------------------------------------------------------------
-- Fix spawn times for quest items in multiple containers, these will be 180 second respawns
-- 35492 = Frostberry (188113)
UPDATE `gameobject` SET `spawntimesecs` = 180 where `id` IN (188113);


-- ------------------------------------------------------------------------------------------
-- Fix respawn time for chest restocking
-- (TEST LATER) UPDATE `gameobject_template` SET `Data2` = 3 WHERE `questItem1` IN (3920);