DELETE FROM `Type`;
DELETE FROM `Type_relations`;

INSERT INTO `Type`(`name`) VALUES
       ('Feu'),
       ('Plante');

INSERT INTO `Type_relations`(`type_id`, `link_oType_id`, `link_coeff`) VALUE
       (1, 1, 1),
       (1, 2, 2),
       (2, 1, 0.5),
       (2, 2, 1);
