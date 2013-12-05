##
## Makefile for  in /home/ansel_l/Documents/Rtype/rtype
## 
## Made by laurent ansel
## Login   <ansel_l@epitech.net>
## 
## Started on  Mon Oct 28 16:06:15 2013 laurent ansel
## Last update Thu Dec  5 15:15:36 2013 alexis mestag
##

NAMESERVER=	server

SERVER=		Server
SERVER_SRC=	$(SERVER)/src

COMMON=		Common
COMMON_SRC=	$(COMMON)/src

SCHEMA=		schema.sql

include		$(COMMON)/Makefile
include		$(SERVER)/Makefile

OBJSERVER=	$(SRCSERVER:.cpp=.o)
OBJCOMMON=	$(SRCCOMMON:.cpp=.o) $(ODB_OBJ)
CPPFLAGS=	-W -Wall -Wextra $(SERVER_INCLUDES) $(COMMON_INCLUDES) -std=c++0x

all:		$(ODB_SRC) $(OBJCOMMON) $(NAMESERVER)

$(NAMESERVER):	$(OBJCOMMON) $(OBJSERVER)
		g++ -o $(NAMESERVER) $(OBJCOMMON) $(OBJSERVER) $(LDFLAGS)

$(SCHEMA):	$(ODB_CLASSES)
		$(ODB) -d mysql --generate-schema-only --at-once --std c++11 \
		$(ODB_OPTIONS) \
		--input-name $(SCHEMA) $(COMMON_INCLUDES) $(ODB_CLASSES)

clean:
		rm -rf $(OBJSERVER) $(OBJCOMMON) $(ODB_SRC) $(ODB_OBJ)

fclean:		clean
		rm -rf $(NAMESERVER)
		rm -rf $(SCHEMA)

re:		fclean all
