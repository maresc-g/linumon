##
## Makefile for  in /home/ansel_l/Documents/Rtype/rtype
## 
## Made by laurent ansel
## Login   <ansel_l@epitech.net>
## 
## Started on  Mon Oct 28 16:06:15 2013 laurent ansel
## Last update Fri Jan 31 11:20:14 2014 guillaume marescaux
##

NAMESERVER=	pfa-server
NAMECLIENT=	pfa-client

SERVER=		Server
SERVER_SRC=	$(SERVER)/src

COMMON=		Common
COMMON_SRC=	$(COMMON)/src

CLIENT=		Client

SCHEMA=		schema.sql

include		$(COMMON)/Makefile
include		$(SERVER)/Makefile

OBJSERVER=	$(SRCSERVER:.cpp=.o)
OBJCLIENT=	$(SRCCLIENT:.cpp=.o)
OBJCOMMON=	$(SRCCOMMON:.cpp=.o) $(ODB_OBJ)
CPPFLAGS=	-W -Wall -Wextra $(SERVER_INCLUDES) $(CLIENT_INCLUDES) $(COMMON_INCLUDES) -std=c++0x -g

all:		$(ODB_SRC) $(OBJCOMMON) $(NAMESERVER) client

client:
		cd $(CLIENT) && make

$(NAMESERVER):	$(OBJCOMMON) $(OBJSERVER)
		g++ -o $(NAMESERVER) $(OBJCOMMON) $(OBJSERVER) $(LDFLAGS)

$(NAMECLIENT):	$(OBJCOMMON) $(OBJCLIENT)
		g++ -o $(NAMECLIENT) $(OBJCOMMON) $(OBJCLIENT) $(LDFLAGS)

$(SCHEMA):	$(ODB_CLASSES)
		$(ODB) -d mysql --generate-schema-only --at-once --std c++11 \
		$(ODB_OPTIONS) \
		--input-name $(SCHEMA) $(COMMON_INCLUDES) $(ODB_CLASSES)

clean:
		rm -rf $(OBJSERVER) $(OBJCLIENT) $(OBJCOMMON) $(ODB_SRC) $(ODB_OBJ)
		cd $(CLIENT) && make clean

fclean:		clean
		rm -rf $(NAMESERVER)
		rm -rf $(NAMECLIENT)
		rm -rf $(SCHEMA)

re:		fclean all
