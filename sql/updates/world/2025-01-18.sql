-- Fix bad creature flag making it so the player cannot attack them first until they agro
UPDATE `creature_template` SET `unit_flags` = 32768 WHERE `entry` = 98555;