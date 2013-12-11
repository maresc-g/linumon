##
## Makefile for Makefile in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
## 
## Made by alexis mestag
## Login   <mestag_a@epitech.net>
## 
## Started on  Tue Dec  3 13:09:41 2013 alexis mestag
## Last update Thu Dec  5 20:23:28 2013 alexis mestag
##

STATS_SRC=		Stat.cpp	\
			Stats.cpp

STATS_SRC:=		$(addprefix $(STATS)/,$(STATS_SRC))

SRCCOMMON+=		$(STATS_SRC)

STATS_H_DIR=		$(subst src,include,$(STATS))

ODB_STATS_OPTIONS=	Stats.options
ODB_STATS_OPTIONS:=	$(addprefix $(STATS_H_DIR)/,$(ODB_STATS_OPTIONS))
ODB_OPTIONS+=		$(ODB_STATS_OPTIONS)

ODB_STATS=		Stat.hh
ODB_STATS:=		$(addprefix $(STATS_H_DIR)/,$(ODB_STATS))
ODB_CLASSES+=		$(ODB_STATS)
