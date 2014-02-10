######################################################################
# Automatically generated by qmake (2.01a) Thu Sep 26 15:12:21 2013
######################################################################

TEMPLATE = app
TARGET = ../pfa-client
DEPENDPATH += . include src
INCLUDEPATH += . include ../Common/include
FORMS = ../Res/loginview.ui ../Res/characterview.ui ../Res/chardescription.ui ../Res/createchar.ui ../Res/spellbar.ui ../Res/itemview.ui ../Res/inventoryview.ui ../Res/stuffview.ui ../Res/chatview.ui
LIBS += -lX11 -lsfml-system -lsfml-window -lsfml-graphics -lcryptopp -ljsoncpp
QMAKE_CXXFLAGS += -std=c++0x
OBJECTS_DIR = ./obj

# Input
HEADERS +=      include/Qt/QSFMLWidget.hpp \
                include/Qt/Views/LoginView.hh \
                include/Qt/Views/CharacterView.hh \
                include/Qt/Views/CreateCharView.hh \
                include/Qt/Views/SpellBarView.hh \
                include/Qt/Views/InventoryView.hh \
                include/Qt/Views/ItemView.hh \
                include/Qt/Views/StuffView.hh \
                include/Qt/Views/ChatView.hh \
                include/Qt/WindowManager.hh \
                include/Qt/CharDescription/CharDescription.hh \
                include/SFML/SFMLView.hpp \
                include/SFML/Sprite/Sprite.hh \
                include/SFML/Sprite/Animation.hh \
                include/Client.hh \
                include/Common/eState.hh \
                include/Common/eDirection.hh \
                include/Core/Core.hh \
                include/Core/ErrorHandler.hh \
                include/Chat/Chat.hh \

SOURCES +=      src/main.cpp \
                src/Qt/QSFMLWidget.cpp \
                src/Qt/Views/LoginView.cpp \
                src/Qt/Views/CharacterView.cpp \
                src/Qt/Views/CreateCharView.cpp \
                src/Qt/Views/SpellBarView.cpp \
                src/Qt/Views/InventoryView.cpp \
                src/Qt/Views/ItemView.cpp \
                src/Qt/Views/StuffView.cpp \
                src/Qt/Views/ChatView.cpp \
                src/Qt/WindowManager.cpp \
                src/Qt/CharDescription.cpp \
                src/SFML/SFMLView.cpp \
                src/SFML/Sprite/Sprite.cpp \
                src/SFML/Sprite/Animation.cpp \
                src/SFML/Sprite/SpriteManager.cpp \
                src/Client.cpp \
                src/Chat/Chat.cpp \
                src/Core/Core.cpp \
                src/Core/ErrorHandler.cpp \
                ../Common/src/Map/Map.cpp \
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
                ../Common/src/Entities/Stuff.cpp \ 
                ../Common/src/Entities/Inventory.cpp \ 
                ../Common/src/Entities/Faction.cpp \ 
                ../Common/src/Utility/Nameable.cpp \ 
                ../Common/src/Utility/Id.cpp
