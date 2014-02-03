/* Inserting Users */
DELETE FROM `User`;

INSERT INTO `User`(`id`, `pseudo`, `password`) VALUES(1, 'Laurent', 'yolo');
INSERT INTO `User`(`id`, `pseudo`, `password`) VALUES(2, 'Cyril', 'swag');

/* Inserting Factions */
DELETE FROM `Faction`;

INSERT INTO `Faction`(`id`, `name`) VALUES(1, 'Brakmar');
INSERT INTO `Faction`(`id`, `name`) VALUES(2, 'Bonta');

/* Inserting EffectLibs */
DELETE FROM `EffectLib`;

INSERT INTO `EffectLib`(`id`, `name`, `path`) VALUES(1, 'Rugissement', 'EffectLibs/Rugissement.so');
INSERT INTO `EffectLib`(`id`, `name`, `path`) VALUES(2, 'Mimi-Queue', 'EffectLibs/Mimi-Queue.so');

/* Inserting TalentModels */
DELETE FROM `TalentModel`;

INSERT INTO `TalentModel`(`id`, `name`, `maxPoints`, `effectLib`) VALUES(1, 'MinAtkTalentModel', 10, 1);
INSERT INTO `TalentModel`(`id`, `name`, `maxPoints`, `effectLib`) VALUES(2, 'MinDefTalentModel', 10, 2);

/* Inserting Talents */
DELETE FROM `Talent`;

INSERT INTO `Talent`(`id`, `model`, `currentPoints`) VALUES(1, 1, 0);
INSERT INTO `Talent`(`id`, `model`, `currentPoints`) VALUES(2, 2, 0);

/* Inserting TalentTrees */
DELETE FROM `TalentTree`;

INSERT INTO `TalentTree`(`id`, `name`, `talent`) VALUES(1, 'BaseTree1', 1);
INSERT INTO `TalentTree`(`id`, `name`, `talent`) VALUES(2, 'BaseTree2', 2);

/* Inserting Players */
DELETE FROM Player;

INSERT INTO `Player`(`id`, `name`, `currentExp`, `level_lvl`, `level_exp`, `faction`, `zone`, `talentTree`, `user`, `x`, `y`) VALUES(1, 'Thinenus', 0, 1, 10, 1, 'PLAIN', 1, 1, 10, 30);
INSERT INTO `Player`(`id`, `name`, `currentExp`, `level_lvl`, `level_exp`, `faction`, `zone`, `talentTree`, `user`, `x`, `y`) VALUES(2, 'Sezu-Kho', 0, 1, 10, 2, 'ROCK', 2, 2, 20, 20);

/* Assigning Players to Users */
DELETE FROM `User_players_players`;

INSERT INTO `User_players_players`(`object_id`, `index`, `value`) VALUES(1, 0, 1);
INSERT INTO `User_players_players`(`object_id`, `index`, `value`) VALUES(2, 0, 2);

/* Assigning Talents to Players */
DELETE FROM `Player_talents`;

INSERT INTO `Player_talents`(`object_id`, `index`, `value`) VALUES(1, 0, 1);
INSERT INTO `Player_talents`(`object_id`, `index`, `value`) VALUES(2, 0, 2);
