##
## Makefile for  in /home/ansel_l/Documents/Rtype/rtype
## 
## Made by laurent ansel
## Login   <ansel_l@epitech.net>
## 
## Started on  Mon Oct 28 16:06:15 2013 laurent ansel
## Last update Thu Nov 28 16:44:46 2013 laurent ansel
##

NAMESERVER=	server

SERVER=		Server
SERVER_SRC=	$(SERVER)/src

COMMON=		Common
COMMON_SRC=	$(COMMON)/src

include		$(COMMON)/Makefile
include		$(SERVER)/Makefile

OBJSERVER=	$(SRCSERVER:.cpp=.o)
OBJCOMMON=	$(SRCCOMMON:.cpp=.o)
CPPFLAGS=	-W -Wall -Wextra $(SERVER_INCLUDES) $(COMMON_INCLUDES) -std=c++0x

all:		$(OBJCOMMON) $(NAMESERVER)

$(NAMESERVER):	$(OBJCOMMON) $(OBJSERVER)
		g++ -o $(NAMESERVER) $(OBJCOMMON) $(OBJSERVER) $(LDFLAGS)

clean:
		rm -rf $(OBJSERVER) $(OBJCOMMON)

fclean:		clean
		rm -rf $(NAMESERVER)

re:		fclean all
