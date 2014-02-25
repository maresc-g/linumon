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

/* Inserting Guilds */
DELETE FROM `Guild`;

INSERT INTO `Guild`(`id`, `name`) VALUES
       (1, 'Folichon Babbage'),
       (2, 'Les Rageux');

/* Inserting Players */
DELETE FROM Player;

INSERT INTO `Player`(`id`, `name`, `stats_authKeys`, `currentExp`, `level_lvl`, `level_exp`, `faction`, `talentTree`, `user`, `guild`, `dbZone`, `x`, `y`, `inventoryPath`, `money`, `limit`) VALUES
       (1, 'Thinenus', 1, 13, 4, 10, 1, 1, 1, 1, 1, 10, 30, 'Res/Inventories/Thinenus.json', 10000, 30),
       (2, 'Sezu-Kho', 1, 20, 6, 10, 1, 2, 2, 1, 1, 20, 20, 'Res/Inventories/Sezu-Kho.json', 10000, 30),
       (3, 'WeshWeshCabillaud', 1, 15, 5, 10, 2, 1, 1, 2, 2, 10, 30, 'Res/Inventories/WeshWeshCabillaud.json', 20000, 20),
       (4, 'EnThéorieCaDevraitMarcher', 1, 584, 10, 10, 2, 2, 2, 2, 2, 20, 20, 'Res/Inventories/EnThéorieCaDevraitMarcher.json', 20000, 20);

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
       (24, 8, 100),

       (25, 1, 551),
       (26, 2, 54),
       (27, 3, 84),
       (28, 4, 98),
       (29, 5, 684),
       (30, 6, 68),
       (31, 7, 68),
       (32, 8, 963),
       (33, 1, 7),
       (34, 2, 5684),
       (35, 3, 54),
       (36, 4, 57),
       (37, 5, 5864),
       (38, 6, 574),
       (39, 7, 47),
       (40, 8, 1),
       (41, 1, 681),
       (42, 2, 5684),
       (43, 3, 684),
       (44, 4, 568),
       (45, 5, 6871),
       (46, 6, 51),
       (47, 7, 867),
       (48, 8, 68),
       (49, 1, 68),
       (50, 2, 41),
       (51, 3, 856741),
       (52, 4, 8),
       (53, 5, 8671),
       (54, 6, 58),
       (55, 7, 6),
       (56, 8, 7861),
       (57, 1, 8671),
       (58, 2, 85671),
       (59, 3, 271),
       (60, 4, 58),
       (61, 5, 92),
       (62, 6, 587),
       (63, 7, 56),
       (64, 8, 56),
       (65, 1, 57),
       (66, 2, 3084),
       (67, 3, 5),
       (68, 4, 684),
       (69, 5, 5784),
       (70, 6, 5),
       (71, 7, 57),
       (72, 8, 78);

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

/* Assigning Stats to Mobs */
DELETE FROM `Mob_stats_stats`;

INSERT INTO `Mob_stats_stats`(`object_id`, `index`, `value`) VALUES
       (1, 0, 25),
       (1, 1, 26),
       (1, 2, 27),
       (1, 3, 28),
       (1, 4, 29),
       (1, 5, 30),
       (1, 6, 31),
       (1, 7, 32),
       (2, 0, 33),
       (2, 1, 34),
       (2, 2, 35),
       (2, 3, 36),
       (2, 4, 37),
       (2, 5, 38),
       (2, 6, 39),
       (2, 7, 40),
       (3, 0, 41),
       (3, 1, 42),
       (3, 2, 43),
       (3, 3, 44),
       (3, 4, 45),
       (3, 5, 46),
       (3, 6, 47),
       (3, 7, 48),
       (4, 0, 49),
       (4, 1, 50),
       (4, 2, 51),
       (4, 3, 52),
       (4, 4, 53),
       (4, 5, 54),
       (4, 6, 55),
       (4, 7, 56),
       (5, 0, 57),
       (5, 1, 58),
       (5, 2, 59),
       (5, 3, 60),
       (5, 4, 61),
       (5, 5, 62),
       (5, 6, 63),
       (5, 7, 64),
       (6, 0, 65),
       (6, 1, 66),
       (6, 2, 67),
       (6, 3, 68),
       (6, 4, 69),
       (6, 5, 70),
       (6, 6, 71),
       (6, 7, 72);

/* Assigning Mobs to Players */
DELETE FROM `Player_digitaliser_mobs`;

INSERT INTO `Player_digitaliser_mobs`(`object_id`, `index`, `value`) VALUES
       (1, 0, 1),
       (1, 1, 2),
       (1, 2, 3),
       (2, 0, 4),
       (2, 1, 5),
       (2, 2, 6);

/* Inserting Stuff */
DELETE FROM `Stuff`;

INSERT INTO `Stuff`(`id`, `name`, `stuffType`) VALUES
       (1, 'Coiffe Bouftou', 'HELMET'),
       (2, 'Cape Bouftou', 'CLOAK'),
       (3, 'Bottes Bouftou', 'BOOTS'),
       (4, 'Amulette Bouftou', 'NECKLACE'),
       (5, 'Epaulettes Bouftou', 'SHOULDERS'),
       (6, 'Plastron Bouftou', 'BREASTPLATE'),
       (7, 'Anneau Bouftou', 'RING'),
       (8, 'Ceinture Bouftou', 'BELT'),
       (9, 'Marteau Bouftou', 'WEAPON');

/* Assigning Stuff to Players */
DELETE FROM `Player_equipment_stuffs`;

INSERT INTO `Player_equipment_stuffs`(`object_id`, `key`, `value`) VALUES
       (1, 'HELMET', 1),
       (1, 'BREASTPLATE', 6),
       (1, 'SHOULDERS', 5),
       (1, 'CLOAK', 2),
       (2, 'WEAPON', 9),
       (2, 'BELT', 8),
       (2, 'RING', 7),
       (2, 'BOOTS', 3);

/* Inserting Ressources */
DELETE FROM `Ressource`;

INSERT INTO `Ressource`(`id`, `name`, `level_lvl`, `level_exp`) VALUES
       (1, 'Orchidée', 10, 100),
       (2, 'Peau de bouftou', 1, 10);

/* Adding some fancy views because it's quite swag */
DROP VIEW IF EXISTS `StatView`;
CREATE VIEW StatView AS SELECT Stat.id, StatKey.name, Stat.value FROM Stat, StatKey WHERE Stat.key = StatKey.id;

DROP VIEW IF EXISTS `MobModelView`;
CREATE VIEW MobModelView AS 
       SELECT MobModel.id, MobModel.name AS model, Type.name AS type, StatView.name AS stat, StatView.value
       	      FROM StatView, Type, MobModel_stats_stats, MobModel
       	      WHERE MobModel_stats_stats.value = StatView.id
       	      	    AND MobModel_stats_stats.object_id = MobModel.id
	     	    AND MobModel.type = Type.id;

DROP VIEW IF EXISTS `MobView`;
CREATE VIEW `MobView` AS
       SELECT Mob.id, Mob.name, Mob.level_lvl, MobModelView.model, MobModelView.type, MobModelView.stat, MobModelView.value AS modelValue
       	      FROM Mob, MobModelView
       	      WHERE Mob.model_id = MobModelView.id;

DROP VIEW IF EXISTS `PlayerView`;
CREATE VIEW `PlayerView` AS
       SELECT Player.id, Player.name, User.pseudo AS user, Faction.name AS faction, Player.level_lvl, Player.currentExp, DBZone.name AS zone, Player.x, Player.y,
       	      AuthorizedStatKeys.name AS statKeys, TalentTree.name AS talentTree
       	      FROM Player, Faction, User, DBZone, AuthorizedStatKeys, TalentTree
       	      WHERE Player.faction = Faction.id
       	      	    AND Player.user = User.id
	     	    AND Player.dbZone = DBZone.id
		    AND Player.stats_authKeys = AuthorizedStatKeys.id
		    AND Player.talentTree = TalentTree.id;

DROP VIEW IF EXISTS `TypeView`;
CREATE VIEW `TypeView` AS
       SELECT Type.id, Type.name, OType.name AS other, Type_relations_relations.value_coeff AS coeff
       	      FROM Type, Type AS OType, Type_relations_relations
	      WHERE Type_relations_relations.object_id = Type.id
	      	    AND Type_relations_relations.value_oType_id = OType.id
	      ORDER BY Type.id, OType.id;

COMMIT;
