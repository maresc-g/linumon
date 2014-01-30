##
## Makefile for  in /home/ansel_l/Documents/Pfa/work
## 
## Made by laurent ansel
## Login   <ansel_l@epitech.net>
## 
## Started on  Thu Nov 28 16:47:21 2013 laurent ansel
## Last update Thu Jan 30 11:25:59 2014 laurent ansel
##

COMMON_INCLUDES=	-I $(COMMON)/include

THREAD=		$(COMMON_SRC)/Thread
MUTEX=		$(COMMON_SRC)/Mutex
SOCKET=		$(COMMON_SRC)/Socket
CIRCULAR_BUFFER_MANAGER=	$(COMMON_SRC)/CircularBufferManager
FILESYSTEM=	$(COMMON_SRC)/FileSystem
TRAME=		$(COMMON_SRC)/Trame
POLL=		$(COMMON_SRC)/Poll
HEADER=		$(COMMON_SRC)/Header
ENTITIES=	$(COMMON_SRC)/Entities
DATABASE=	$(COMMON_SRC)/Database
UTILITY=	$(COMMON_SRC)/Utility
STATS=		$(COMMON_SRC)/Stats
INITIALIZECONNECTION=		$(COMMON_SRC)/InitializeConnection
CRYPTO=		$(COMMON_SRC)/Crypto
ZONE=		$(COMMON_SRC)/Zone
PROTOCOL=	$(COMMON_SRC)/Protocol
JSON=		$(COMMON_SRC)/JsonFile

# Needed for odb
ODB_CLASSES=
ODB_OPTIONS=

include		$(THREAD)/Makefile
include		$(MUTEX)/Makefile
include		$(SOCKET)/Makefile
include		$(CIRCULAR_BUFFER_MANAGER)/Makefile
include		$(FILESYSTEM)/Makefile
include		$(TRAME)/Makefile
include		$(POLL)/Makefile
include		$(HEADER)/Makefile
include		$(ENTITIES)/Makefile
include		$(DATABASE)/Makefile
include		$(UTILITY)/Makefile
include		$(STATS)/Makefile
include		$(INITIALIZECONNECTION)/Makefile
include		$(CRYPTO)/Makefile
include		$(ZONE)/Makefile
include		$(PROTOCOL)/Makefile
include		$(JSON)/Makefile

ODB_OPTIONS:=	$(addprefix --options-file ,$(ODB_OPTIONS))

ODB=		odb
ODB_DIR=	odb
ODB_CXX=        $(ODB_CLASSES:.hh=-odb.cxx)
ODB_HXX=        $(ODB_CLASSES:.hh=-odb.hxx)
ODB_IXX=        $(ODB_CLASSES:.hh=-odb.ixx)
# ODB_SQL=        $(ODB_CLASSES:.hh=.sql)
ODB_SRC=        $(ODB_CXX) $(ODB_HXX) $(ODB_IXX) #$(ODB_SQL)
ODB_OBJ=	$(ODB_CXX:.cxx=.o)

ODB_FLAGS=	-d mysql --generate-query --generate-session --std c++11 \
		$(COMMON_INCLUDES) $(ODB_OPTIONS)

%-odb.cxx %-odb.hxx %-odb.ixx:	%.hh
				$(ODB)  $(ODB_FLAGS) -o $(dir $<) $<

%.o:		%.cxx
		g++  $(CPPFLAGS)  -c -o $@ $<

ifndef _WIN32
LDFLAGS +=	-lpthread -D_REENTRANT -ljsoncpp
endif

LDFLAGS+=	-L/usr/lib/odb -lodb-mysql -lodb
