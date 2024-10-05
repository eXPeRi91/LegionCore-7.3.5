-- Fix existing teleport locations
DELETE FROM `game_tele` WHERE `name` IN ('CampNarache', 'Valormok', 'Sorrowmurk');
INSERT INTO `game_tele` (`id`, `position_x`, `position_y`, `position_z`, `orientation`, `map`, `name`) VALUES
(188, -2895.67, -247.76, 59.809, 4.0043, 1, 'CampNarache'),
(1280, 3006.65, -4151.15, 101.810, 2.5073, 1, 'Valormok'),
(899, -10204.53, -4182.26, 22.356, 4.3773, 0, 'Sorrowmurk');

-- Insert missing teleport locations (do not include id column)
DELETE FROM `game_tele` WHERE `name` IN ('Bogpaddle');
INSERT INTO `game_tele` (`position_x`, `position_y`, `position_z`, `orientation`, `map`, `name`) VALUES
(-9761.64, -3918.13, 21.644, 1.5467, 0, 'Bogpaddle');