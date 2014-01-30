CREATE DATABASE `Linumon`;

GRANT ALL PRIVILEGES ON Linumon.* to 'odbLinumonUser'@'localhost' IDENTIFIED BY 'odbLinumonPassword';
FLUSH PRIVILEGES;

use Linumon;
source schema.sql;

INSERT INTO `User`(`pseudo`, `password`) VALUES('Thinenus', 'yolo');
