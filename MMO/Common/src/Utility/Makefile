##
## Makefile<3> for Makefile in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
## 
## Made by alexis mestag
## Login   <mestag_a@epitech.net>
## 
## Started on  Tue Dec  3 10:53:24 2013 alexis mestag
## Last update Thu Dec  5 15:32:22 2013 alexis mestag
##

UTILITY_SRC=		Id.cpp		\
			Nameable.cpp

UTILITY_SRC:=		$(addprefix $(UTILITY)/,$(UTILITY_SRC))

SRCCOMMON+=		$(UTILITY_SRC)

ODB_UTILITY+=		Nameable.hh

UTILITY_H_DIR=		$(subst src,include,$(UTILITY))

ODB_UTILITY:=		$(addprefix $(UTILITY_H_DIR)/,$(ODB_UTILITY))

ODB_CLASSES+=		$(ODB_UTILITY)
