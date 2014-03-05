//
// Core.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Jan 24 13:58:09 2014 guillaume marescaux
// Last update Wed Mar  5 13:50:40 2014 guillaume marescaux
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
	   MutexVar<Chat *> *chat, MutexVar<bool> *newPlayer,
	   MutexVar<Battle *> *battle):
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
  _newPlayer(newPlayer),
  _battle(battle),
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
  func = std::bind1st(std::mem_fun(&Core::entity), this);
  _proto->addFunc("ENTITY", func);
  func = std::bind1st(std::mem_fun(&Core::newPlayer), this);
  _proto->addFunc("NEWPLAYER", func);
  func = std::bind1st(std::mem_fun(&Core::newZone), this);
  _proto->addFunc("NEWZONE", func);
  func = std::bind1st(std::mem_fun(&Core::addToInventory), this);
  _proto->addFunc("ADDTOINVENTORY", func);
  func = std::bind1st(std::mem_fun(&Core::deleteFromInventory), this);
  _proto->addFunc("DELETEFROMINVENTORY", func);
  func = std::bind1st(std::mem_fun(&Core::job), this);
  _proto->addFunc("JOB", func);
  func = std::bind1st(std::mem_fun(&Core::launchBattle), this);
  _proto->addFunc("LAUNCHBATTLE", func);
  func = std::bind1st(std::mem_fun(&Core::turnTo), this);
  _proto->addFunc("TURNTO", func);

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
  delete _initialized;
  delete _running;
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
  std::cout << "PLAYERLIST" << std::endl;
  *_players = User::deserialization(*trame);
  *_state = CLIENT::CHOOSE_PLAYER;
  return (true);
}

bool				Core::player(Trame *trame)
{
  *_player = Player::deserialization((*trame)((*trame)[CONTENT]));
  return (true);
}

bool				Core::getChat(Trame *trame)
{
  (**_chat)->addMsg((*trame)[CONTENT]["CHAT"]["MESSAGE"].asString());
  (**_chat)->setNewMessage(true);
  return (true);
}

bool				Core::map(Trame *trame)
{
  Map::getInstance()->getZone((**_player)->getZone())->deserialization(*trame);
  *_state = CLIENT::PLAYING;
  std::cout << "PLAYERS IN MAP = " << Map::getInstance()->getPlayers((**_player)->getZone())->size() << std::endl;
  return (true);
}

bool				Core::launchBattle(Trame *trame)
{
  *_state = CLIENT::BATTLE;
  (**_battle)->setInfos(_player, (*trame)[CONTENT]["LAUNCHBATTLE"]["ID"].asUInt(),
			Player::deserialization((*trame)((*trame)[CONTENT]["LAUNCHBATTLE"]["ENEMY"])));
  return (true);
}

bool				Core::turnTo(Trame *trame)
{
  (**_battle)->setTurnTo((*trame)[CONTENT]["TURNTO"].asUInt());
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

bool				Core::addToInventory(Trame *trame)
{
  std::vector<std::string>	keys = (*trame)[CONTENT]["ADDTOINVENTORY"].getMemberNames();
  AItem				*item;

  for (auto it = keys.begin() ; it != keys.end() ; it++)
    {
      item = AItem::deserialization((*trame)((*trame)[CONTENT]["ADDTOINVENTORY"]["ITEM"]));
      for (int i = 0 ; i < (*trame)[CONTENT]["ADDTOINVENTORY"][*it]["NB"].asInt() ; i++)
	(**_player)->addItem(item);
    }
  return (true);
}

bool				Core::deleteFromInventory(Trame *trame)
{
  std::vector<std::string>	keys = (*trame)[CONTENT]["DELETEFROMINVENTORY"].getMemberNames();

  for (auto it = keys.begin() ; it != keys.end() ; it++)
    {
      for (int i = 0 ; i < (*trame)[CONTENT]["DELETEFROMINVENTORY"][*it]["NB"].asInt() ; i++)
	(**_player)->deleteItem((*trame)[CONTENT]["DELETEFROMINVENTORY"][*it]["ID"].asUInt());
    }
  return (true);
}

bool				Core::job(Trame *trame)
{
  Job				*job = Job::deserialization((*trame)((*trame)[CONTENT]["JOB"]));

  (**_player)->setJob(job->getJobModel().getName(), job);
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

bool				Core::removeEntity(Trame *trame)
{
  Map				*map = Map::getInstance();
  AEntity			*entity = map->getEntityById((**_player)->getZone(),
							     (*trame)[CONTENT]["REMOVEENTITY"]["ID"].asUInt());

  if (entity->getEntityType() == AEntity::STATENTITY)
    map->delPlayer((**_player)->getZone(), entity);
  else
    map->delEntity((**_player)->getZone(), entity);
  return (true);
}

bool				Core::entity(Trame *trame)
{
  Map				*map = Map::getInstance();
  AEntity			*entity = map->getEntityById((**_player)->getZone(),
							     (*trame)[CONTENT]["ENTITY"]["ID"].asUInt());

  if (entity)
    {
      static_cast<Player *>(entity)->setX((*trame)[CONTENT]["ENTITY"]["COORDINATE"]["X"].asInt());
      static_cast<Player *>(entity)->setY((*trame)[CONTENT]["ENTITY"]["COORDINATE"]["Y"].asInt());
      map->move(entity);
    }
  return (true);
}

bool				Core::newPlayer(Trame *trame)
{
  Player			*player = Player::deserialization((*trame)((*trame)[CONTENT]["NEWPLAYER"]));

  *_newPlayer = true;
  Map::getInstance()->addPlayer((**_player)->getZone(), player);
  return (true);
}

bool				Core::newZone(Trame *trame)
{
  *_state = CLIENT::LOADING;
  (**_player)->setCoord((*trame)[CONTENT]["NEWZONE"]["COORDINATE"]["X"].asUInt(),
			(*trame)[CONTENT]["NEWZONE"]["COORDINATE"]["Y"].asUInt());
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

bool				Core::move(CLIENT::eDirection dir)
{
  Map				*map = Map::getInstance();
  Player::PlayerCoordinate::type	newX;
  Player::PlayerCoordinate::type	newY;
  Zone				*zone;
  bool				ret = false;

  newX = (**_player)->getX() + (dir == CLIENT::LEFT ? -1 : (dir == CLIENT::RIGHT ? 1 : 0));
  newY = (**_player)->getY() + (dir == CLIENT::UP ? -1 : (dir == CLIENT::DOWN ? 1 : 0));
  map->lock();
  zone = map->getZone((**_player)->getZone());
  if ((zone->getCase(newX, newY) && zone->getCase(newX, newY)->getEntities()->size() == 0) || !zone->getCase(newX, newY))
    {
      (**_player)->setCoord(newX, newY);
      Player::Coordinate	*coord = new Player::Coordinate(newX, newY);
      (*_proto).operator()<unsigned int const, int, Player::PlayerCoordinate const *>("ENTITY", _id, (**_player)->getId(),
  									      coord);
      delete coord;
      ret = true;
    }
  map->unlock();
  return (ret);
}

void				Core::connection(std::string const &pseudo, std::string const &pass)
{
  (*_proto).operator()<unsigned int const, std::string, std::string>("CONNECTION", _id, pseudo, pass);
}

void				Core::choosePlayer(PlayerView const &player)
{
  *_state = CLIENT::LOADING;
  (*_proto).operator()<unsigned int const, int>("CHOOSEPLAYER", _id, player.persistentId);
}

void				Core::createPlayer(std::string const &name, std::string const &faction)
{
  Faction			*tmp = new Faction(faction);

  *_state = CLIENT::CREATE;
  (*_proto).operator()<unsigned int const, std::string, Faction const *>("CREATE", _id, name, tmp);
  delete tmp;
}

void				Core::sendChat(std::string const &msg)
{
  (*_proto).operator()<unsigned int const, std::string, std::string>("CHAT", _id, (**_player)->getZone(),
							     (**_player)->getName() + ": " + msg);
}

void				Core::spell(unsigned int idBattle, Spell const &spell, unsigned int target)
{
  (*_proto).operator()<unsigned int const, unsigned int, Spell const *, unsigned int>("SPELL", _id, idBattle, &spell, target);
}

void				Core::capture(unsigned int idBattle, unsigned int target)
{
  (*_proto).operator()<unsigned int const, unsigned int, unsigned int>("CAPTURE", _id, idBattle, target);
}

void				Core::sendSwitch(unsigned int idBattle, unsigned int target, unsigned int newMob)
{
  (*_proto).operator()<unsigned int const, unsigned int, unsigned int, unsigned int>("SWITCH", _id, idBattle, target, newMob);
}

void				Core::stuff(int action, unsigned int idItem, unsigned int target)
{
  (*_proto).operator()<unsigned int const, int, unsigned int, unsigned int>("STUFF", _id, action, idItem, target);
}

// void				talents();

void				Core::craft(std::string const &craftName, std::string const &jobName)
{
  (*_proto).operator()<unsigned int const, std::string, std::string>("CRAFT", _id, craftName, jobName);
}


// void				gather();

void				Core::useObject(unsigned int target, AItem const &item)
{
  (*_proto).operator()<unsigned int const, unsigned int, unsigned int>("USEOBJECT", _id, target, item.getId());  
}

// void				unsigned interaction();

void				Core::putItem(AItem const &item)
{
  (*_proto).operator()<unsigned int const, AItem const *>("PUTITEM", _id, &item);  
}

void				Core::getItem(AItem const &item)
{
  (*_proto).operator()<unsigned int const, AItem const *>("GETITEM", _id, &item);  
}

void				Core::sendMoney(unsigned int money)
{
  (*_proto).operator()<unsigned int const, unsigned int>("MONEY", _id, money);  
}

void				Core::accept(void)
{
  (*_proto).operator()<unsigned int const>("ACCEPT", _id);  
}

void				Core::refuse(void)
{
  (*_proto).operator()<unsigned int const>("REFUSE", _id);  
}

void				Core::heal(void)
{
  (*_proto).operator()<unsigned int const>("HEAL", _id);  
}

void				Core::disconnect(void)
{
  *_state = CLIENT::LOGIN;
  (*_proto).operator()<unsigned int const>("DISCONNECT", _id);  
}

void				Core::switchPlayer(void)
{
  *_state = CLIENT::CHOOSE_PLAYER;
  (*_proto).operator()<unsigned int const>("SWITCHPLAYER", _id);  
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
  Trame				*trame;
  CircularBufferManager		*manager = CircularBufferManager::getInstance();

  this->read(0, true);
  trame = manager->popTrame(CircularBufferManager::READ_BUFFER);
  if (trame)
    {
      _proto->decodeTrame(trame);
      delete trame;
    }
  this->write();
}

//--------------------------------------END METHODS--------------------------------------------
