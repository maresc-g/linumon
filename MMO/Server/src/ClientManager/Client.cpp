//
// Client.cpp for  in /home/ansel_l/Documents/Pfa/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Tue Dec  3 16:04:56 2013 laurent ansel
// Last update Thu Mar 13 13:31:23 2014 laurent ansel
//

#include			"ClientManager/Client.hh"
#include			"Server/Server.hh"
#include			"Map/Map.hh"
#include			"ClientWriter/ClientWriter.hh"
#include			"RessourceManager/RessourceManager.hh"
#include			"Battle/BattleManager.hh"
#include			"Database/Repositories/PlayerRepository.hpp"
#include			"Database/Repositories/FactionRepository.hpp"

Client::Client():
  _use(false),
  _id(0),
  _sockets(new std::map<std::string, ISocketClient *>),
  _user(NULL),
  _player(NULL),
  _state(NONE)
{
  (*_sockets)["UDP"] = NULL;
  (*_sockets)["TCP"] = NULL;
}

Client::~Client()
{
  delete (*_sockets)["UDP"];
  delete (*_sockets)["TCP"];
  delete _sockets;
}

void				Client::clear()
{
  if (_state == TRADE && _player)
    TradeManager::getInstance()->disconnectPlayer(_player->getId());
  if (_state == BATTLE && _player)
    BattleManager::getInstance()->disconnect(_player->getId());
  _state = NONE;
  if (_player)
    {
      Map::getInstance()->delPlayer(_player->getZone(), _player);
      Server::getInstance()->callProtocol<int, Zone *>("REMOVEENTITY", _id, _id, Map::getInstance()->getZone(_player->getZone()));
    }
  delete (*_sockets)["UDP"];
  delete (*_sockets)["TCP"];
  (*_sockets)["UDP"] = NULL;
  (*_sockets)["TCP"] = NULL;
  _id = 0;
  _use = false;
  if (_user)
    _user->setId(0);
  _user = NULL;

  if (_player)
    {
      Repository<Player>	*rp = &Database::getRepository<Player>();

      rp->smartUpdate(*_player);
    }
  delete _player;
  _player = NULL;
}

void				Client::disconnectUser()
{
  if (_state == TRADE && _player)
    TradeManager::getInstance()->disconnectPlayer(_player->getId());
  if (_state == BATTLE && _player)
    BattleManager::getInstance()->disconnect(_player->getId());
  _state = GAME;
  if (_player)
    {
      Map::getInstance()->delPlayer(_player->getZone(), _player);
      Server::getInstance()->callProtocol<int, Zone *>("REMOVEENTITY", _id, _id, Map::getInstance()->getZone(_player->getZone()));
    }
  if (_user)
    _user->setId(0);
  _user = NULL;

  if (_player)
    {
      Repository<Player>	*rp = &Database::getRepository<Player>();

      rp->smartUpdate(*_player);
    }
  delete _player;

  _player = NULL;
}

void				Client::disconnectPlayer()
{
  if (_state == TRADE && _player)
    TradeManager::getInstance()->disconnectPlayer(_player->getId());
  if (_state == BATTLE && _player)
    BattleManager::getInstance()->disconnect(_player->getId());
  _state = GAME;
  if (_player)
    {
      Map::getInstance()->delPlayer(_player->getZone(), _player);
      Server::getInstance()->callProtocol<int, Zone *>("REMOVEENTITY", _id, _id, Map::getInstance()->getZone(_player->getZone()));
    }

  if (_player)
    {
      Repository<Player>	*rp = &Database::getRepository<Player>();

      rp->smartUpdate(*_player);
    }
  delete _player;

  _player = NULL;

  this->sendListPlayers();
}

bool				Client::isUse() const
{
  return (this->_use);
}

FD				Client::getId() const
{
  return (this->_id);
}

void				Client::use(FD const id)
{
  _state = GAME;
  this->_id = id;
  this->_use = true;
}

void				Client::sendAllInformationModel() const
{
  Server::getInstance()->callProtocol("AUTHORIZEDSTATKEYSLIST", _id);
  Server::getInstance()->callProtocol("STUFFS", _id);
  Server::getInstance()->callProtocol("CONSUMABLES", _id);
  Server::getInstance()->callProtocol("RESSOURCES", _id);
  Server::getInstance()->callProtocol("HEALS", _id);
  Server::getInstance()->callProtocol("SPELLSLIST", _id);
  Server::getInstance()->callProtocol("TALENTMODELS", _id);
  Server::getInstance()->callProtocol("JOBMODELS", _id);
  Server::getInstance()->callProtocol("MOBMODELS", _id);
}

void				Client::state(eState const state)
{
  _state = state;
}

void				Client::setSocket(ISocketClient const *socket, std::string const &proto)
{
  if ((*_sockets)[proto])
    delete (*_sockets)[proto];
  (*_sockets)[proto] = new SocketClient(socket);
}

bool				Client::writeTrame(Trame *trame, std::string const &proto)
{
  size_t			ret;
  std::string			str;
  std::string			tmp;

  if (trame && trame->toString(str))
    {
      std::cout << trame->toStyledString() << std::endl;
      // //      Crypto::getInstance()->encryption(str, tmp);
      // //      ret = (*this->_sockets)[proto]->writeSocket(const_cast<char *>(tmp.c_str()), tmp.size());
      ret = (*this->_sockets)[proto]->writeSocket(const_cast<char *>(str.c_str()), str.size());
      // //      if (ret < tmp.size())
      if (ret < str.size())
	{
	  trame->setSize(ret);
	  return (false);
	}
      ClientWriter::getInstance()->addNewTrame(_id, -1);
      return (true);
    }
  return (false);
}

bool				Client::readTrame(std::string &str, std::string const &proto)
{
  char                          tmp[SIZE_BUFFER] = "";
  std::string			decrypt;
  int				ret = (*this->_sockets)[proto]->readSocket(tmp, SIZE_BUFFER);

  if (ret > 0)
    {
      str.append(tmp, ret);
      // // decrypt.append(tmp, ret);
      // // if (Crypto::getInstance()->decryption(decrypt, str))
      return (true);
    }
  return (false);
}

void				Client::addUser(User *user)
{
  this->_user = user;
  this->_user->setId(this->_id);
}

bool				Client::addPlayer(std::string const &name, Faction *faction)
{
  if (this->_state == GAME && this->_user)
    {
      Repository<Player>	*rp = &Database::getRepository<Player>();
      Repository<Faction>	*rf = &Database::getRepository<Faction>();
      Player			*player = new Player(name);

      player->setFaction(*rf->getByName(faction->getName()));
      delete faction;
      this->_user->addPlayer(*player);
      rp->persist(*player);
      return (true);
    }
  return (false);
}

void				Client::sendListPlayers()
{
  if (_state == GAME && _user)
    Server::getInstance()->callProtocol<User *>("PLAYERLIST", _id, _user);
}

void				Client::choosePlayer(unsigned int const id, bool const send)
{
  if (_state == GAME)
    {
      Repository<Player>	*rp = &Database::getRepository<Player>();

      this->_player = rp->getById(id);
      if (this->_player && send)
	{
	  Map::getInstance()->addPlayer(_player->getZone(), _player);
	  Server::getInstance()->callProtocol<Player *>("PLAYER", _id, _player);
	  Server::getInstance()->callProtocol<Zone *>("MAP", _id, Map::getInstance()->getZone(_player->getZone()));
	  Server::getInstance()->callProtocol<Player *>("NEWPLAYER", _id, _player, Map::getInstance()->getZone(_player->getZone()));
	}
    }
}

void				Client::move(Player::PlayerCoordinate *coord)
{
  Trame				*trame = NULL;
  Header			*header;
  bool				ret;
  std::string			oldZone;

  if (_state == GAME)
    {
      if (this->_player && coord)
	{
	  this->_player->setCoord(*coord);
	  ObjectPoolManager::getInstance()->setObject(trame, "trame");
	  ObjectPoolManager::getInstance()->setObject(header, "header");
	  if (trame)
	    {
	      header->setIdClient(_id);
	      header->setProtocole("UDP");
	      header->serialization(*trame);
	      trame->setEnd(true);
	      (*trame)[CONTENT]["ENTITY"]["ID"] = static_cast<unsigned int>(this->_player->getId());
	      oldZone = _player->getZone();
	      ret = Map::getInstance()->move(_player);
	      if (ret)
		{
		  std::cout << "ENVOIE DU NEW ZONE" << std::endl;
		  Server::getInstance()->callProtocol<Player * , Zone *, Zone *>("NEWZONE", _id, _player, Map::getInstance()->getZone(oldZone), Map::getInstance()->getZone(_player->getZone()));
		  delete trame;
		  delete header;
		}
	      else
		{
		  _player->getCoord().serialization((*trame)((*trame)[CONTENT]["ENTITY"]));
		  Server::getInstance()->callProtocol<Trame *, Zone *, bool>("SENDTOALLCLIENT", _id, trame, Map::getInstance()->getZone(_player->getZone()), true);
		  delete header;
		  // if (!Map::getInstance()->getZone(_player->getZone())->getCase(_player->getX(), _player->getY())->getSafe())
		  //   if (BattleManager::getInstance()->inBattle(_player))
		  //     _state = BATTLE;
		}
	    }
	  if (!Map::getInstance()->getZone(_player->getZone())->getCase(_player->getX(), _player->getY())->getSafe())
	    {
	      std::cout << "Le getSafe RENVOIE TRUE, JE VAIS RENTRER DANS INBATTLE" << std::endl;
	      if (BattleManager::getInstance()->inBattle(_player))
	  	_state = BATTLE;
	    }
	}
    }
}

void				Client::updateTalents(std::string const &talent, unsigned int const pts) const
{
  if (_state == GAME && _player)
    {
      _player->modifyTalent(pts, talent);
      Server::getInstance()->callProtocol<Player *>("PLAYER", _id, _player);
    }
}

void				Client::useObject(unsigned int const target, unsigned int const item)
{
  if (_state == GAME && _player)
    {
      _player->useObject(target, item);
      Server::getInstance()->callProtocol<unsigned int, Stats const *>("OBJECTEFFECT", _id, target, &(_player->getMob(target).getRawCurrentStats()));
    }
}

void				Client::deleteObject(unsigned int const item, int const nb)
{
  if (_state == GAME && _player)
    {
      for (auto i = 0 ; i < nb ; ++i)
	_player->deleteItem(item);
    }
}

void				Client::startBattle(Player *&player)
{
  _state = BATTLE;
  player = _player;
}

void				Client::endBattle()
{
  _state = GAME;
}

void				Client::startTrade(Player *&player)
{
  _state = TRADE;
  player = _player;
}

void				Client::endTrade()
{
  _state = GAME;
}

bool				Client::craft(std::string const &craft, std::string const &job) const
{
  bool				ret = false;
  Stack				*result;
  std::list<Stack *>		*object;

  if (_state == GAME && _player && _user)
    {
      result = new Stack(0);
      object = new std::list<Stack *>;
      ret = _player->doCraft(job, craft, result, object);
      if (ret)
	{
	  Server::getInstance()->callProtocol<Stack *>("ADDTOINVENTORY", _id, result);
	  Server::getInstance()->callProtocol<std::list<Stack *> *>("DELETEFROMINVENTORY", _id, object);
	  //	  Server::getInstance()->callProtocol<std::list<std::pair<unsigned int, unsigned int> > *>("DELETEFROMINVENTORY", _id, &object);
	  Server::getInstance()->callProtocol<Job const *>("JOB", _id, _player->getJob(job));
	}
    }
  return (ret);
}

bool				Client::gather(std::string const &ressource, std::string const &job, Ressource::RessourceCoordinate const &) const
{
  bool				ret = false;
  Stack				*result;
  unsigned int			idRessource;
  AEntity			*entity;

  if (_state == GAME && _player && _user)
    {
      result = new Stack(0);
      ret = _player->doGather(job, ressource, result, idRessource);
      if (ret)
	{
	  //	  Server::getInstance()->callProtocol<std::list<AItem *> *>("ADDTOINVENTORY", _id, &result);
	  Server::getInstance()->callProtocol<Stack *>("ADDTOINVENTORY", _id, result);
	  Server::getInstance()->callProtocol<Job const *>("JOB", _id, _player->getJob(job));
	  entity = Map::getInstance()->getEntityById(_player->getZone(), idRessource);
	  if (entity)
	    {
	      static_cast<Ressource *>(entity)->setVisible(false);
	      RessourceManager::getInstance()->needRessource(ressource, _player->getZone(), static_cast<Ressource *>(entity));
	      Server::getInstance()->callProtocol<unsigned int, bool, Zone *>("VISIBLE", _id, idRessource, false, Map::getInstance()->getZone(_player->getZone()));
	    }
	}
    }
  return (ret);
}

bool				Client::stuff(bool const get, unsigned int const idItem, unsigned int const target)
{
  bool				ret = false;

  if (_state == GAME && _player)
    {
      if (get)
	{
	  if (target == _player->getId())
	    ret = _player->getPlayerEquipment(idItem);
	  else
	    ret = _player->getMobEquipment(target, idItem);
	}
      else
	{
	  if (target == _player->getId())
	    ret = _player->putPlayerEquipment(idItem);
	  else
	    ret = _player->putMobEquipment(target, idItem);
	}
      if (ret)
	{
	  if (target == _player->getId())
	    Server::getInstance()->callProtocol<ACharacter const *>("UPDATECHARACTER", _id, _player);
	  else
	    Server::getInstance()->callProtocol<ACharacter const *>("UPDATECHARACTER", _id, &_player->getMob(target));
	}
    }
  return (ret);
}

void				Client::merge(unsigned int const idStack, unsigned int const idStack2)
{
  if (_state == GAME && _player)
    _player->mergeStack(idStack, idStack2);
}

void				Client::newStack(unsigned int const idStack, unsigned int const nb)
{
  if (_state == GAME && _player)
    _player->newStack(idStack, nb);
}
