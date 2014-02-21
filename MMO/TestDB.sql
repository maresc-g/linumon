BEGIN;

/* Inserting Users */
DELETE FROM `User`;

INSERT INTO `User`(`id`, `pseudo`, `password`) VALUES
       (1, 'Laurent', 'yolo'),
       (2, 'Cyril', 'swag');

/* Inserting Factions */
DELETE FROM `Faction`;

INSERT INTO `Faction`(`id`, `name`) VALUES
       (1, 'Hesode'),
       (2, 'Celestia');

/* Inserting EffectLibs */
DELETE FROM `EffectLib`;

INSERT INTO `EffectLib`(`id`, `name`, `path`) VALUES
       (1, 'Rugissement', 'EffectLibs/Rugissement.so'),
       (2, 'Mimi-Queue', 'EffectLibs/Mimi-Queue.so');

/* Inserting TalentModels */
DELETE FROM `TalentModel`;

INSERT INTO `TalentModel`(`id`, `name`, `maxPoints`, `effectLib`) VALUES
       (1, 'MinAtkTalentModel', 10, 1),
       (2, 'MinDefTalentModel', 10, 2);

/* Inserting Talents */
DELETE FROM `Talent`;

INSERT INTO `Talent`(`id`, `model`, `currentPoints`) VALUES
       (1, 1, 0),
       (2, 2, 0);

/* Inserting TalentTrees */
DELETE FROM `TalentTree`;

INSERT INTO `TalentTree`(`id`, `name`, `talent`) VALUES
       (1, 'BaseTree1', 1),
       (2, 'BaseTree2', 2);

/* Inserting DBZones */
DELETE FROM `DBZone`;

INSERT INTO `DBZone`(`id`, `name`, `averageLevel`) VALUES
       (1, 'Plain', 10),
       (2, 'Rock', 40);

/* Inserting Inventories */
DELETE FROM Inventory;

INSERT INTO `Inventory`(`id`, `path`, `money`, `limit`) VALUES
       (1, 'Res/Inventories/Thinenus.json', 10000, 30),
       (2, 'Res/Inventories/Sezu-Kho.json', 10000, 30),
       (3, 'Res/Inventories/WeshWeshCabillaud.json', 20000, 20),
       (4, 'Res/Inventories/EnThéorieCaDevraitMarcher.json', 20000, 20);

/* Inserting Types */
DELETE FROM `Type`;

INSERT INTO `Type`(`id`, `name`) VALUES
       (1, 'Fire'),
       (2, 'Water'),
       (3, 'Grass');

/* Assigning Types to Types */
DELETE FROM `Type_relations_relations`;

INSERT INTO `Type_relations_relations`(`object_id`, `index`, `value_oType_id`, `value_coeff`) VALUES
       (1, 0, 1, 0.5),
       (1, 1, 2, 0.5),
       (1, 2, 3, 2),
       (2, 0, 1, 2),
       (2, 1, 2, 0.5),
       (2, 2, 3, 0.5),
       (3, 0, 1, 0.5),
       (3, 1, 2, 2),
       (3, 2, 3, 0.5);

/* Inserting StatKeys */
DELETE FROM `StatKey`;

INSERT INTO `StatKey`(`id`, `name`) VALUES
       (1, 'HP'),
       (2, 'Attack'),
       (3, 'Defense'),
       (4, 'Speed'),
       (5, 'Precision'),
       (6, 'Dodge'),
       (7, 'Parade'),
       (8, 'Critic'),
       (9, 'Capture'),
       (10, 'Limit mob');

/* Inserting AuthorizedStatKeys */
DELETE FROM `AuthorizedStatKeys`;

INSERT INTO `AuthorizedStatKeys`(`id`, `name`) VALUES
       (1, 'PlayerKeys'),
       (2, 'MobKeys');

/* Assigning StatKeys to AuthorizedStatKeys */
DELETE FROM `AuthorizedStatKeys_keys`;

INSERT INTO `AuthorizedStatKeys_keys`(`object_id`, `index`, `value`) VALUES
       (1, 0, 9),
       (1, 1, 10),
       (2, 0, 1),
       (2, 1, 2),
       (2, 2, 3),
       (2, 3, 4),
       (2, 4, 5),
       (2, 5, 6),
       (2, 6, 7),
       (2, 7, 8);

/* Inserting Players */
DELETE FROM Player;

<<<<<<< HEAD
INSERT INTO `Player`(`id`, `name`, `stats_authKeys`, `currentExp`, `level_lvl`, `level_exp`, `faction`, `talentTree`, `user`, `inventory`, `dbZone`, `x`, `y`) VALUES
       (1, 'Thinenus', 1, 13, 4, 10, 1, 1, 1, 1, 1, 10, 30),
       (2, 'Sezu-Kho', 1, 20, 6, 10, 1, 2, 2, 2, 1, 20, 20),
       (3, 'WeshWeshCabillaud', 1, 15, 5, 10, 2, 1, 1, 3, 2, 10, 30),
       (4, 'EnThéorieCaDevraitMarcher', 1, 584, 10, 10, 2, 2, 2, 4, 2, 20, 20);

/* Assigning Talents to Players */
DELETE FROM `Player_talents`;

INSERT INTO `Player_talents`(`object_id`, `index`, `value`) VALUES
       (1, 0, 1),
       (2, 0, 2);

/* Inserting MobModels */
DELETE FROM `MobModel`;

INSERT INTO `MobModel`(`id`, `name`, `stats_authKeys`, `type`) VALUES
       (1, 'Charizard', 2, 1),
       (2, 'Blastoise', 2, 2),
       (3, 'Venuzaur', 2, 3);

/* Inserting Stats */
DELETE FROM `Stat`;

INSERT INTO `Stat`(`id`, `key`, `value`) VALUES
       (1, 1, 78),
       (2, 2, 84),
       (3, 3, 78),
       (4, 4, 100),
       (5, 5, 109),
       (6, 6, 100),
       (7, 7, 85),
       (8, 8, 109),
       (9, 1, 79),
       (10, 2, 83),
       (11, 3, 100),
       (12, 4, 78),
       (13, 5, 85),
       (14, 6, 78),
       (15, 7, 105),
       (16, 8, 85),
       (17, 1, 80),
       (18, 2, 82),
       (19, 3, 83),
       (20, 4, 80),
       (21, 5, 100),
       (22, 6, 80),
       (23, 7, 100),
       (24, 8, 100);

/* Assigning Stats to MobModels */
DELETE FROM `MobModel_stats_stats`;

INSERT INTO `MobModel_stats_stats`(`object_id`, `index`, `value`) VALUES
       (1, 0, 1),
       (1, 1, 2),
       (1, 2, 3),
       (1, 3, 4),
       (1, 4, 5),
       (1, 5, 6),
       (1, 6, 7),
       (1, 7, 8),
       (2, 0, 9),
       (2, 1, 10),
       (2, 2, 11),
       (2, 3, 12),
       (2, 4, 13),
       (2, 5, 14),
       (2, 6, 15),
       (2, 7, 16),
       (3, 0, 17),
       (3, 1, 18),
       (3, 2, 19),
       (3, 3, 20),
       (3, 4, 21),
       (3, 5, 22),
       (3, 6, 23),
       (3, 7, 24);

/* Inserting Mobs */
DELETE FROM `Mob`;

INSERT INTO `Mob`(`id`, `name`, `stats_authKeys`, `currentExp`, `level_lvl`, `level_exp`, `model_id`) VALUES
       (1, 'TinyLezard', 2, 412, 6, 500, 1),
       (2, 'BigTurtle', 2, 789, 7, 1000, 2),
       (3, 'VastFlowerPot', 2, 350, 5, 400, 3),
       (4, 'MegaFist', 2, 15659, 12, 25000, 1),
       (5, 'SuperWet', 2, 11087, 11, 15000, 2),
       (6, 'UltraBushy', 2, 12, 1, 20, 3);

/* Assigning Mobs to Players */
DELETE FROM `Player_digitaliser_mobs`;

INSERT INTO `Player_digitaliser_mobs`(`object_id`, `index`, `value`) VALUES
       (1, 0, 1),
       (1, 1, 2),
       (1, 2, 3),
       (2, 0, 4),
       (2, 1, 5),
       (2, 2, 6);

/* Adding some fancy views because it's quite swag */
DROP VIEW IF EXISTS `StatView`;
CREATE VIEW StatView AS SELECT Stat.id, StatKey.name, Stat.value FROM Stat, StatKey WHERE Stat.key = StatKey.id;

COMMIT;
