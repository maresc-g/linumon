##
## Makefile<2> for Makefile in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
## 
## Made by alexis mestag
## Login   <mestag_a@epitech.net>
## 
## Started on  Mon Dec  2 16:28:46 2013 alexis mestag
## Last update Thu Mar  6 13:26:30 2014 laurent ansel
##

DATABASE_SRC=		Persistent.cpp

DATABASE_SRC:=		$(addprefix $(DATABASE)/, $(DATABASE_SRC))

SRCCOMMON+=		$(DATABASE_SRC)

DATABASE_H_DIR=		$(subst src,include,$(DATABASE))

ODB_DATABASE=		Persistent.hh
ODB_DATABASE:=		$(addprefix $(DATABASE_H_DIR)/,$(ODB_DATABASE))

ODB_CLASSES+=		$(ODB_DATABASE)
