##
## Makefile for Makefile in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
## 
## Made by alexis mestag
## Login   <mestag_a@epitech.net>
## 
## Started on  Tue Dec  3 13:09:41 2013 alexis mestag
## Last update Wed Mar 12 15:24:10 2014 alexis mestag
##

STATS_SRC=		AuthorizedStatKeys.cpp	\
			ExperienceCurve.cpp	\
			Stat.cpp		\
			Stats.cpp		\
			StatKey.cpp		\
			Talent.cpp		\
			Talents.cpp		\
			TalentModel.cpp		\
			TalentTree.cpp

STATS_SRC:=		$(addprefix $(STATS)/,$(STATS_SRC))

SRCCOMMON+=		$(STATS_SRC)

STATS_H_DIR=		$(subst src,include,$(STATS))

ODB_STATS_OPTIONS=	
ODB_STATS_OPTIONS:=	$(addprefix $(STATS_H_DIR)/,$(ODB_STATS_OPTIONS))
ODB_OPTIONS+=		$(ODB_STATS_OPTIONS)

ODB_STATS=		AuthorizedStatKeys.hh	\
			ExperienceCurve.hh	\
			Stat.hh			\
			StatKey.hh		\
			Talent.hh		\
			TalentModel.hh		\
			TalentTree.hh

ODB_STATS:=		$(addprefix $(STATS_H_DIR)/,$(ODB_STATS))
ODB_CLASSES+=		$(ODB_STATS)
