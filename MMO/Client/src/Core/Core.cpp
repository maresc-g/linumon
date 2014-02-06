//
// Core.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Jan 24 13:58:09 2014 guillaume marescaux
// Last update Thu Feb  6 15:17:41 2014 laurent ansel
//

#include			<unistd.h>
#include			<string.h>
#include			<functional>
#include			"Core/Core.hh"
#include			"Crypto/Crypto.hh"
#include			"Map/Map.hh"
#include			"Entities/User.hh"

static void			*runThread(void *data)
{
  if (data)
    {
      Core			*core = reinterpret_cast<Core *>(data);

      core->run();
    }
  return (NULL);
}

//-----------------------------------BEGIN CTOR / DTOR-----------------------------------------

Core::Core(MutexVar<CLIENT::eState> *state, MutexVar<Player *> *player,
	   MutexVar<std::list<PlayerView *> *> *players,
	   MutexVar<Chat *> *chat):
  Thread(),
  _sockets(new std::map<eSocket, Socket *>),
  _socketsClient(new std::map<eSocket, ISocketClient *>),
  _infos(new ConnectionInfos),
  _poll(new Poll),
  _proto(new Protocol(false)),
  _id(0),
  _initialized(new MutexVar<bool>(false)),
  _running(new MutexVar<bool>(true)),
  _state(state),
  _player(player),
  _players(players),
  _chat(chat),
  _handler(new ErrorHandler)
{
  std::function<bool (Trame *)> func;
  func = std::bind1st(std::mem_fun(&Core::welcome), this);
  _proto->addFunc("WELCOME", func);
  func = std::bind1st(std::mem_fun(&Core::check), this);
  _proto->addFunc("CHECK", func);
  func = std::bind1st(std::mem_fun(&Core::handleError), this);
  _proto->addFunc("ERROR", func);
  func = std::bind1st(std::mem_fun(&Core::playerlist), this);
  _proto->addFunc("PLAYERLIST", func);
  func = std::bind1st(std::mem_fun(&Core::player), this);
  _proto->addFunc("PLAYER", func);
  func = std::bind1st(std::mem_fun(&Core::map), this);
  _proto->addFunc("MAP", func);
  func = std::bind1st(std::mem_fun(&Core::getChat), this);
  _proto->addFunc("CHAT", func);

  (*_sockets)[TCP] = new Socket;
  (*_sockets)[UDP] = new Socket;
  (*_socketsClient)[TCP] = NULL;
  (*_socketsClient)[UDP] = NULL;
  this->create(&runThread, this);
  this->start();
}

Core::~Core()
{
  this->join();
  delete _infos;
  (*_sockets)[TCP]->destroy();
  (*_sockets)[UDP]->destroy();
  delete (*_sockets)[TCP];
  delete (*_sockets)[UDP];
  delete _sockets;
  delete _socketsClient;
  delete _poll;
  delete _proto;
  delete _handler;
  ObjectPoolManager::deleteInstance();
}

//------------------------------------END CTOR / DTOR------------------------------------------

//---------------------------------BEGIN PRIVATE METHODS---------------------------------------

void				Core::readFromSocket(eSocket sock)
{
  static char			buff[SIZE_BUFFER];
  static std::string		tmp;
  CircularBufferManager		*manager = CircularBufferManager::getInstance();
  //  Trame				*tmpTrame;
  int				size;
  // Crypto			*crypto = Crypto::getInstance();
  std::string			decrypted;

  if (_poll->isSet((*_socketsClient)[sock]->getSocket(), IPoll::READ))
    {
      memset(buff, 0, SIZE_BUFFER);
      tmp = "";
      // decrypted = "";
      // while (decrypted.rfind(TRAMEEND) == std::string::npos)
      while (tmp.rfind(TRAMEEND) == std::string::npos)
      	{
	  size = (*_socketsClient)[sock]->readSocket(buff, SIZE_BUFFER);
	  if (size > 0)
	    {
	      tmp.append(buff, size);
	      // crypto->decryption(tmp, decrypted);
	    }
      	  else
      	    {
      	      return;
      	    }
      	}
      // Trame::toTrame(*tmpTrame, decrypted);
      std::list<Trame *> *list = Trame::toTrame(tmp);
      // tmpTrame = new Trame;
      // Trame::toTrame(*tmpTrame, tmp);
      for (auto it = list->begin() ; it != list->end() ; ++it)
	if (*it)
	  manager->pushTrame(*it, CircularBufferManager::READ_BUFFER);
      delete list;
    }
}

void                            Core::writeToSocket(Trame const &trame, eSocket sock)
{
  static std::string            trameBuff;
  static char                   buff[SIZE_BUFFER];

  trameBuff = trame.toString();
  memset(buff, 0, SIZE_BUFFER);
  trameBuff.copy(buff, trameBuff.size());
  (*_socketsClient)[sock]->writeSocket(buff, trameBuff.size());
}
                                
bool				Core::welcome(Trame *trame)
{
  Header			*header;

  header = Header::deserialization(*trame);
  _id = header->getIdClient();
  _proto->operator()<unsigned int const>("INITIALIZE", _id);
  return (true);
}

bool				Core::check(Trame *)
{
  *_initialized = true;
  return (true);
}

bool				Core::handleError(Trame *trame)
{
  Error				*error;

  error = Error::deserialization(*trame);
  _handler->handleError(*error, _state);
  delete error;
  return (true);
}

bool				Core::playerlist(Trame *trame)
{
  *_players = User::deserialization(*trame);
  *_state = CLIENT::CHOOSE_PLAYER;
  return (true);
}

bool				Core::player(Trame *trame)
{
  *_player = Player::deserialization((*trame)((*trame)[CONTENT]));
  *_state = CLIENT::PLAYING;
  return (true);
}

bool				Core::getChat(Trame *trame)
{
  (**_chat)->addMsg((*trame)[CONTENT]["MESSAGE"].asString());
  return (true);
}

bool				Core::map(Trame *)
{
  Map::getInstance();
  // Zone::deserialization(trame);
  return (true);
}

bool				Core::launchBattle(Trame *)
{
  *_state = CLIENT::BATTLE;
  return (true);
}

bool				Core::spell(Trame *)
{
  return (true);
}

bool				Core::spellEffect(Trame *)
{
  return (true);
}

bool				Core::captureEffect(Trame *)
{
  return (true);
}

bool				Core::switchMob(Trame *)
{
  return (true);
}

bool				Core::deadMob(Trame *)
{
  return (true);
}

bool				Core::endBattle(Trame *)
{
  *_state = CLIENT::PLAYING;
  return (true);
}

bool				Core::upStats(Trame *)
{
  return (true);
}

bool				Core::upTalents(Trame *)
{
  return (true);
}

bool				Core::inventory(Trame *)
{
  return (true);
}

bool				Core::job(Trame *)
{
  return (true);
}

bool				Core::caseMap(Trame *)
{
  return (true);
}

bool				Core::objectEffect(Trame *)
{
  return (true);
}

bool				Core::launchTrade(Trame *)
{
  *_state = CLIENT::TRADE;
  return (true);
}

bool				Core::putItem(Trame *)
{
  return (true);
}

bool				Core::getItem(Trame *)
{
  return (true);
}

bool				Core::putMoney(Trame *)
{
  return (true);
}

bool				Core::getMoney(Trame *)
{
  return (true);
}

bool				Core::accept(Trame *)
{
  return (true);
}

bool				Core::refuse(Trame *)
{
  return (true);
}

bool				Core::quitServer(Trame *)
{
  return (true);
}

bool				Core::removeEntity(Trame *)
{
  return (true);
}

bool				Core::entity(Trame *)
{
  return (true);
}


//----------------------------------END PRIVATE METHODS----------------------------------------

//-------------------------------------BEGIN METHODS-------------------------------------------

void				Core::quit()
{
  *_running = false;
}

void                            Core::write()
{
  CircularBufferManager         *manager = CircularBufferManager::getInstance();
  Trame                         *tmp;

  _poll->pushFd((*_socketsClient)[TCP]->getSocket(), Poll::WRITE);
  _poll->pushFd((*_socketsClient)[UDP]->getSocket(), Poll::WRITE);
  tmp = manager->popTrame(_id, "TCP", CircularBufferManager::WRITE_BUFFER);
  if (!tmp)
    tmp = manager->popTrame(_id, "UDP", CircularBufferManager::WRITE_BUFFER);
  while (tmp)
    {
      _poll->runPoll(false);
      if ((*tmp)[HEADER]["PROTOCOLE"].asString() == "TCP")
        {
          if (_poll->isSet((*_socketsClient)[TCP]->getSocket(), Poll::WRITE))
            writeToSocket(*tmp, Core::TCP);
        }
      else if ((*tmp)[HEADER]["PROTOCOLE"].asString() == "UDP")
        {
          if (_poll->isSet((*_socketsClient)[UDP]->getSocket(), Poll::WRITE))
            writeToSocket(*tmp, Core::UDP);
        }
      delete tmp;
      tmp = manager->popTrame(_id, "TCP", CircularBufferManager::WRITE_BUFFER);
      if (!tmp)
        tmp = manager->popTrame(_id, "UDP", CircularBufferManager::WRITE_BUFFER);
    }
}

void				Core::read(int const timeout, bool const setTimeout)
{
  _poll->pushFd((*_socketsClient)[TCP]->getSocket(), IPoll::READ);
  _poll->pushFd((*_socketsClient)[UDP]->getSocket(), IPoll::READ);
  _poll->setTimeout(timeout);
  _poll->runPoll(setTimeout);
  this->readFromSocket(Core::TCP);
  this->readFromSocket(Core::UDP);  
}

void				Core::move(CLIENT::eDirection dir)
{
  Map				*map = Map::getInstance();
  Player::PlayerCoordinate::type	newX;
  Player::PlayerCoordinate::type	newY;
  Zone				*zone;

  newX = (**_player)->getX() + (dir == CLIENT::LEFT ? -1 : (dir == CLIENT::RIGHT ? 1 : 0));
  newY = (**_player)->getY() + (dir == CLIENT::UP ? -1 : (dir == CLIENT::DOWN ? 1 : 0));
  map->lock();
  zone = map->getZone((**_player)->getZone());
  if (zone && zone->getCase(newX, newY)->getEntities()->size() == 0)
    {
      (**_player)->setCoord(newX, newY);
      (*_proto).operator()<unsigned int const, int, Player::PlayerCoordinate>("ENTITY", _id, (**_player)->getId(),
  									      (**_player)->getCoord());
    }
  map->unlock();
}

void				Core::connection(std::string const &pseudo, std::string const &pass)
{
  (*_proto).operator()<unsigned int const, std::string, std::string>("CONNECTION", _id, pseudo, pass);
}

void				Core::choosePlayer(PlayerView const &player)
{
  (*_proto).operator()<unsigned int const, int>("CHOOSEPLAYER", _id, player.persistentId);
}

void				Core::createPlayer(std::string const &name, std::string const &faction)
{
  Faction			*tmp = new Faction(faction);

  (*_proto).operator()<unsigned int const, std::string, Faction>("CREATE", _id, name, *tmp);
}

void				Core::sendChat(std::string const &msg)
{
  (*_proto).operator()<unsigned int const, int, std::string>("CHAT", _id, static_cast<int>((**_player)->getZone()),
							     (**_player)->getName() + ": " + msg);
}

void				Core::init(void)
{
  Trame				*trame = new Trame();
  CircularBufferManager		*manager = CircularBufferManager::getInstance();

  Trame::readFile(*trame, CONNECT_FILE);
  _infos->ip = (*trame)["ip"].asString();
  _infos->port = (*trame)["port"].asInt();
  delete trame;

  (*_sockets)[TCP]->initialize("TCP");
  (*_sockets)[UDP]->initialize("UDP");
  (*_socketsClient)[TCP] = (*_sockets)[TCP]->connectToAddr(_infos->ip, _infos->port);
  (*_socketsClient)[UDP] = (*_sockets)[UDP]->connectToAddr(_infos->ip, _infos->port);
  _poll->pushFd((*_socketsClient)[TCP]->getSocket(), IPoll::RDWRDC);
  _poll->pushFd((*_socketsClient)[UDP]->getSocket(), IPoll::RDWR);
  while (!(trame = manager->popTrame(CircularBufferManager::READ_BUFFER)))
    this->read(0, false);
  _proto->decodeTrame(trame);
  this->write();
  while (!(trame = manager->popTrame(CircularBufferManager::READ_BUFFER)))
    this->read(0, false);
  _proto->decodeTrame(trame);
}

void				Core::run()
{
  while (**_running)
    {
      while (!**_initialized)
	usleep(100000);
      if (**_running)
	this->loop();
      usleep(1000);
    }
}

void				Core::loop()
{
  Trame				*trame = new Trame();
  CircularBufferManager		*manager = CircularBufferManager::getInstance();

  this->read(0, true);
  trame = manager->popTrame(CircularBufferManager::READ_BUFFER);
  if (trame)
    {
      _proto->decodeTrame(trame);
    }
  this->write();
}

//--------------------------------------END METHODS--------------------------------------------
