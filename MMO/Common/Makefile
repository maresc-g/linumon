##
## Makefile for  in /home/ansel_l/Documents/Pfa/work
## 
## Made by laurent ansel
## Login   <ansel_l@epitech.net>
## 
## Started on  Thu Nov 28 16:47:21 2013 laurent ansel
## Last update Fri Nov 29 15:36:07 2013 laurent ansel
##

THREAD=		$(COMMON_SRC)/Thread
MUTEX=		$(COMMON_SRC)/Mutex
SOCKET=		$(COMMON_SRC)/Socket
CIRCULAR_BUFFER_MANAGER=	$(COMMON_SRC)/CircularBufferManager
FILESYSTEM=	$(COMMON_SRC)/FileSystem
TRAME=		$(COMMON_SRC)/Trame
POLL=		$(COMMON_SRC)/Poll
HEADER=		$(COMMON_SRC)/Header

include		$(THREAD)/Makefile
include		$(MUTEX)/Makefile
include		$(SOCKET)/Makefile
include		$(CIRCULAR_BUFFER_MANAGER)/Makefile
include		$(FILESYSTEM)/Makefile
include		$(TRAME)/Makefile
include		$(POLL)/Makefile
include		$(HEADER)/Makefile

ifndef _WIN32
LDFLAGS +=	-lpthread -D_REENTRANT -ljsoncpp
endif

COMMON_INCLUDES=	-I $(COMMON)/include
