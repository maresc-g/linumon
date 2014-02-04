######################################################################
# Automatically generated by qmake (2.01a) Thu Sep 26 15:12:21 2013
######################################################################

TEMPLATE = app
TARGET = ../pfa-client
DEPENDPATH += . include src
INCLUDEPATH += . include ../Common/include
FORMS = ../Res/loginview.ui ../Res/characterview.ui ../Res/chardescription.ui ../Res/createchar.ui
LIBS += -lX11 -lsfml-system -lsfml-window -lsfml-graphics -lcryptopp -ljsoncpp
QMAKE_CXXFLAGS += -std=c++0x
OBJECTS_DIR = ./obj

# Input
HEADERS +=      include/Qt/QSFMLWidget.hpp \
                include/Qt/LoginView/LoginView.hh \
                include/Qt/CharacterView/CharacterView.hh \
                include/Qt/WindowManager.hh \
                include/Qt/CharDescription/CharDescription.hh \
                include/Qt/CreateCharView/CreateCharView.hh \
                include/SFML/SFMLView.hpp \
                include/SFML/Sprite/Sprite.hh \
                include/SFML/Sprite/Animation.hh \
                include/Client.hh \
                include/eState.hh \
                include/Core/Core.hh \
                include/Core/ErrorHandler.hh \
                include/Map/Map.hh

SOURCES +=      src/main.cpp \
                src/Qt/QSFMLWidget.cpp \
                src/Qt/LoginView.cpp \
                src/Qt/CharacterView.cpp \
                src/Qt/WindowManager.cpp \
                src/Qt/CharDescription.cpp \
                src/Qt/CreateCharView.cpp \
                src/SFML/SFMLView.cpp \
                src/SFML/Sprite/Sprite.cpp \
                src/SFML/Sprite/Animation.cpp \
                src/SFML/Sprite/SpriteManager.cpp \
                src/Client.cpp \
                src/Core/Core.cpp \
                src/Core/ErrorHandler.cpp \
                src/Map/Map.cpp \
                ../Common/src/Crypto/Crypto.cpp \ 
                ../Common/src/Mutex/AMutex.cpp \ 
                ../Common/src/Mutex/UnixMutex.cpp \ 
                ../Common/src/Poll/UnixPoll.cpp \ 
                ../Common/src/InitializeConnection/InitializeConnection.cpp \ 
                ../Common/src/FileSystem/Entry.cpp \ 
                ../Common/src/FileSystem/Directory.cpp \ 
                ../Common/src/FileSystem/File.cpp \ 
                ../Common/src/JsonFile/JsonFile.cpp \ 
                ../Common/src/Zone/Zone.cpp \ 
                ../Common/src/Zone/Case.cpp \ 
                ../Common/src/Database/Persistent.cpp \ 
                ../Common/src/Socket/UnixSocket.cpp \ 
                ../Common/src/Socket/UnixSocketClient.cpp \ 
                ../Common/src/CircularBufferManager/CircularBufferManager.cpp \ 
                ../Common/src/CircularBufferManager/CircularBuffer.cpp \ 
                ../Common/src/Thread/PthreadCondition.cpp \ 
                ../Common/src/Thread/UnixThread.cpp \ 
                ../Common/src/Protocol/Protocol.cpp \ 
                ../Common/src/Stats/Stats.cpp \ 
                ../Common/src/Stats/Stat.cpp \ 
                ../Common/src/Trame/Trame.cpp \ 
                ../Common/src/Header/Header.cpp \ 
                ../Common/src/Entities/Spells.cpp \ 
                ../Common/src/Entities/ACharacter.cpp \ 
                ../Common/src/Entities/TypeRelations.cpp \ 
                ../Common/src/Entities/MobModel.cpp \ 
                ../Common/src/Entities/Players.cpp \ 
                ../Common/src/Entities/Type.cpp \ 
                ../Common/src/Entities/AItem.cpp \ 
                ../Common/src/Entities/Spell.cpp \ 
                ../Common/src/Entities/Level.cpp \ 
                ../Common/src/Entities/Digitaliser.cpp \ 
                ../Common/src/Entities/Mob.cpp \ 
                ../Common/src/Entities/AEntity.cpp \ 
                ../Common/src/Entities/User.cpp \ 
                ../Common/src/Entities/AStatEntity.cpp \ 
                ../Common/src/Entities/Player.cpp \ 
                ../Common/src/Entities/Faction.cpp \ 
                ../Common/src/Utility/Nameable.cpp \ 
                ../Common/src/Utility/Id.cpp
