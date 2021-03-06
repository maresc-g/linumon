//
// ClientManager.cpp for  in /home/ansel_l/Documents/Pfa/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Wed Dec  4 11:22:44 2013 laurent ansel
// Last update Wed Mar 26 10:40:49 2014 guillaume marescaux
//

#include			"Database/Database.hpp"
#include			"Entities/User-odb.hxx"
#include			"ClientManager/ClientManager.hh"
#include			"Error/Error.hpp"
#include			"Server/Server.hh"
#include			"Database/Repositories/UserRepository.hpp"

ClientManager::ClientManager():
  _updaters(new std::vector<std::pair<ClientUpdater *, bool> >),
  _mutex(new Mutex)
{
  _mutex->init();
  _mutex->lock();

  this->initializeProtocolFunction();

  for (int i = 0 ; i < CLIENT_THREAD_MIN ; ++i)
    {
      _updaters->push_back(std::make_pair(new ClientUpdater(NB_CLIENTS_PER_THREAD), false));
    }
  _mutex->unlock();
}

ClientManager::~ClientManager()
{
  std::cout << "ClientManager DELETE " << std::flush;
  _mutex->lock();
  for (auto it = this->_updaters->begin() ; it != this->_updaters->end() ; ++it)
    if ((*it).first)
      {
	(*it).first->setQuit(true);
	if ((*it).second)
	  (*it).first->join();
	delete (*it).first;
	std::cout << "." << std::flush;
      }
  delete this->_updaters;
  std::cout << "." << std::flush;
  _mutex->unlock();
  _mutex->destroy();
  delete _mutex;
  std::cout << "." << std::flush;
  std::cout << std::endl << "Done" << std::endl;
}

void				ClientManager::newClient(Header const &header, ISocketClient *tcp)
{
  bool				set = false;
  static int			i = 0;
  unsigned int			limit = 0;

  this->_mutex->lock();
  for (; limit < this->_updaters->size() && !set ; ++limit)
    {
      if ((*this->_updaters)[i].first && (*this->_updaters)[i].first->newClient(header, tcp))
	{
	  if (!(*this->_updaters)[i].second)
	    {
	      (*this->_updaters)[i].first->start();
	      (*this->_updaters)[i].second = true;
	    }
	  set = true;
	}
      i = (i + 1) % this->_updaters->size();
    }
  if (!set)
    {
      _updaters->push_back(std::make_pair(new ClientUpdater(NB_CLIENTS_PER_THREAD), true));
      _updaters->back().first->newClient(header, tcp);
    }
  this->_mutex->unlock();
}

void				ClientManager::setInfoClient(FD const fd, ISocketClient const *socket, std::string const &proto) const
{
  bool				set = false;

  this->_mutex->lock();
  for (auto it = this->_updaters->begin() ; it != this->_updaters->end() && !set ; ++it)
    if ((*it).first && (*it).second && (*it).first->search(fd))
      {
	(*it).first->setInfo(fd, socket, proto);
	set = true;
      }
  this->_mutex->unlock();
}

void				ClientManager::setInfoClient(FD const fd) const
{
  bool				set = false;

  this->_mutex->lock();
  for (auto it = this->_updaters->begin() ; it != this->_updaters->end() && !set ; ++it)
    if ((*it).first && (*it).second && (*it).first->search(fd))
      {
	(*it).first->setInfo(fd, true);
	set = true;
      }
  this->_mutex->unlock();
}

void				ClientManager::setInfoClient(FD const fd, std::string const &protocole, bool const read) const
{
  bool				set = false;

  this->_mutex->lock();
  for (auto it = this->_updaters->begin() ; it != this->_updaters->end() && !set ; ++it)
    if ((*it).first && (*it).second && (*it).first->search(fd))
      {
	if (read)
	  (*it).first->readClient(fd, protocole);
	else
	  (*it).first->canWrite(fd, protocole);
	set = true;
      }
  this->_mutex->unlock();
}

void				ClientManager::setInfoClient(FD const fd, std::string const &name, Faction *faction, bool &ok) const
{
  bool				set = false;

  this->_mutex->lock();
  for (auto it = this->_updaters->begin() ; it != this->_updaters->end() && !set ; ++it)
    if ((*it).first && (*it).second && (*it).first->search(fd))
      {
	(*it).first->setInfo(fd, name, faction, ok);
	set = true;
      }
  this->_mutex->unlock();
}

void				ClientManager::setInfoClient(FD const fd, unsigned int const idPlayer) const
{
  bool				set = false;

  this->_mutex->lock();
  for (auto it = this->_updaters->begin() ; it != this->_updaters->end() && !set ; ++it)
    if ((*it).first && (*it).second && (*it).first->search(fd))
      {
	(*it).first->setInfo(fd, idPlayer, true);
	set = true;
      }
  this->_mutex->unlock();
}

void				ClientManager::setInfoClient(FD const fd, User *user) const
{
  bool				set = false;

  this->_mutex->lock();
  for (auto it = this->_updaters->begin() ; it != this->_updaters->end() && !set ; ++it)
    if ((*it).first && (*it).second && (*it).first->search(fd))
      {
	(*it).first->setInfo(fd, user);
	set = true;
      }
  this->_mutex->unlock();
}

void				ClientManager::setInfoClient(FD const fd, Player::PlayerCoordinate *coord) const
{
  bool				set = false;

  this->_mutex->lock();
  for (auto it = this->_updaters->begin() ; it != this->_updaters->end() && !set ; ++it)
    if ((*it).first && (*it).second && (*it).first->search(fd))
      {
	(*it).first->setInfo(fd, coord);
	set = true;
      }
  this->_mutex->unlock();
}

void				ClientManager::sendAllInformationModel(FD const fd) const
{
  bool				set = false;

  this->_mutex->lock();
  for (auto it = this->_updaters->begin() ; it != this->_updaters->end() && !set ; ++it)
    if ((*it).first && (*it).second && (*it).first->search(fd))
      {
	(*it).first->sendAllInformationModel(fd);
	set = true;
      }
  this->_mutex->unlock();
}

void				ClientManager::sendListPlayers(FD const fd) const
{
  bool				set = false;

  this->_mutex->lock();
  for (auto it = this->_updaters->begin() ; it != this->_updaters->end() && !set ; ++it)
    if ((*it).first && (*it).second && (*it).first->search(fd))
      {
	(*it).first->sendListPlayers(fd);
	set = true;
      }
  this->_mutex->unlock();
}

void				ClientManager::setPlayerTalent(FD const fd, std::string const &talent, unsigned int const pts) const
{
  bool				set = false;

  this->_mutex->lock();
  std::cout << "I AM IN SET PLAYERS TALENTS" << std::endl;
  for (auto it = this->_updaters->begin() ; it != this->_updaters->end() && !set ; ++it)
    if ((*it).first && (*it).second)
      set = (*it).first->setTalents(fd, talent, pts);
  this->_mutex->unlock();
}

void				ClientManager::modifyDigitaliser(FD const fd, unsigned int const idMob1, unsigned int const idMob2, bool const toBattleMob) const
{
  bool				set = false;

  this->_mutex->lock();
  for (auto it = this->_updaters->begin() ; it != this->_updaters->end() && !set ; ++it)
    if ((*it).first && (*it).second)
      set = (*it).first->modifyDigitaliser(fd, idMob1, idMob2, toBattleMob);
  this->_mutex->unlock();
}

void				ClientManager::playerObject(FD const fd, unsigned int const target, unsigned int const item) const
{
  bool				set = false;

  this->_mutex->lock();
  for (auto it = this->_updaters->begin() ; it != this->_updaters->end() && !set ; ++it)
    if ((*it).first && (*it).second)
      set = (*it).first->playerObject(fd, target, item);
  this->_mutex->unlock();
}

void				ClientManager::playerObject(FD const fd, unsigned int const item, int const nb) const
{
  bool				set = false;

  this->_mutex->lock();
  for (auto it = this->_updaters->begin() ; it != this->_updaters->end() && !set ; ++it)
    if ((*it).first && (*it).second)
      set = (*it).first->playerObject(fd, item, nb);
  this->_mutex->unlock();
}

void				ClientManager::merge(FD const fd, unsigned int const idStack, unsigned int const idStack2) const
{
  bool				set = false;

  this->_mutex->lock();
  for (auto it = this->_updaters->begin() ; it != this->_updaters->end() && !set ; ++it)
    if ((*it).first && (*it).second)
      set = (*it).first->merge(fd, idStack, idStack2);
  this->_mutex->unlock();
}

void				ClientManager::newStack(FD const fd, unsigned int const idStack, unsigned int const nb) const
{
  bool				set = false;

  this->_mutex->lock();
  for (auto it = this->_updaters->begin() ; it != this->_updaters->end() && !set ; ++it)
    if ((*it).first && (*it).second)
      set = (*it).first->newStack(fd, idStack, nb);
  this->_mutex->unlock();
}

void				ClientManager::startBattle(FD const fd, Player *&player) const
{
  bool				set = false;

  this->_mutex->lock();
  for (auto it = this->_updaters->begin() ; it != this->_updaters->end() && !set ; ++it)
    if ((*it).first && (*it).second)
      set = (*it).first->stateBattle(fd, true, false, player);
  this->_mutex->unlock();
}

void				ClientManager::endBattle(FD const fd) const
{
  bool				set = false;
  Player			*player;

  this->_mutex->lock();
  for (auto it = this->_updaters->begin() ; it != this->_updaters->end() && !set ; ++it)
    if ((*it).first && (*it).second)
      set = (*it).first->stateBattle(fd, false, true, player);
  this->_mutex->unlock();
}

void				ClientManager::startTrade(FD const fd, Player *&player) const
{
  bool				set = false;

  this->_mutex->lock();
  for (auto it = this->_updaters->begin() ; it != this->_updaters->end() && !set ; ++it)
    if ((*it).first && (*it).second)
      set = (*it).first->stateTrade(fd, true, false, player);
  this->_mutex->unlock();
}

void				ClientManager::endTrade(FD const fd) const
{
  bool				set = false;
  Player			*player;

  this->_mutex->lock();
  for (auto it = this->_updaters->begin() ; it != this->_updaters->end() && !set ; ++it)
    if ((*it).first && (*it).second)
      set = (*it).first->stateTrade(fd, false, true, player);
  this->_mutex->unlock();
}

void				ClientManager::newState(FD const fd, Client::eState const state) const
{
  bool				set = false;

  this->_mutex->lock();
  for (auto it = this->_updaters->begin() ; it != this->_updaters->end() && !set ; ++it)
    if ((*it).first && (*it).second)
      (*it).first->newState(fd, state);
  this->_mutex->unlock();
}


bool				ClientManager::stuff(FD const fd, bool const get, unsigned int const idItem, unsigned int const target) const
{
  bool				set = false;

  this->_mutex->lock();
  for (auto it = this->_updaters->begin() ; it != this->_updaters->end() && !set ; ++it)
    if ((*it).first && (*it).second)
      set = (*it).first->stuff(fd, get, idItem, target);
  this->_mutex->unlock();
  return (set);
}

bool				ClientManager::inviteInGuild(std::string const &name, std::string const &nameGuild) const
{
 bool				set = false;

  this->_mutex->lock();
  for (auto it = this->_updaters->begin() ; it != this->_updaters->end() && !set ; ++it)
    if ((*it).first && (*it).second)
      set = (*it).first->inviteInGuild(name, nameGuild);
  this->_mutex->unlock();
  return (set);
}

void				ClientManager::newGuild(FD const fd, Guild *guild) const
{
  bool				set = false;

  this->_mutex->lock();
  for (auto it = this->_updaters->begin() ; it != this->_updaters->end() && !set ; ++it)
    if ((*it).first && (*it).second)
      set = (*it).first->newGuild(fd, guild);
  this->_mutex->unlock();
}

void				ClientManager::newGuild(std::string const &playerName, Guild *guild) const
{
  bool				set = false;

  this->_mutex->lock();
  for (auto it = this->_updaters->begin() ; it != this->_updaters->end() && !set ; ++it)
    if ((*it).first && (*it).second)
      set = (*it).first->newGuild(playerName, guild);
  this->_mutex->unlock();
}

bool				ClientManager::inGuild(FD const fd) const
{
  bool				set = false;
  bool				ret = false;

  this->_mutex->lock();
  for (auto it = this->_updaters->begin() ; it != this->_updaters->end() && !set ; ++it)
    if ((*it).first && (*it).second)
      set = (*it).first->inGuild(fd, ret);
  this->_mutex->unlock();
  return (ret);
}

void				ClientManager::heal(FD const fd) const
{
  bool				set = false;

  this->_mutex->lock();
  for (auto it = this->_updaters->begin() ; it != this->_updaters->end() && !set ; ++it)
    if ((*it).first && (*it).second)
      (*it).first->heal(fd);
  this->_mutex->unlock();
}

bool				ClientManager::craftSomething(FD const fd, std::string const &craft, std::string const &job) const
{
  bool				set = false;

  this->_mutex->lock();
  for (auto it = this->_updaters->begin() ; it != this->_updaters->end() && !set ; ++it)
    if ((*it).first && (*it).second)
      set = (*it).first->craftSomething(fd, craft, job);
  this->_mutex->unlock();
  return (set);
}

bool				ClientManager::gatherSomething(FD const fd, std::string const &job, unsigned int const idRes, unsigned int const carcass) const
{
  bool				set = false;

  this->_mutex->lock();
  for (auto it = this->_updaters->begin() ; it != this->_updaters->end() && !set ; ++it)
    if ((*it).first && (*it).second)
      set = (*it).first->gatherSomething(fd, idRes, job, carcass);
  this->_mutex->unlock();
  return (set);
}

bool				ClientManager::userAlreadyConnected(FD const fd, User *user) const
{
  bool				ret = false;
  Error				*error = NULL;

  this->_mutex->lock();
  if (user && user->getId() != 0)
    {
      ret = true;
      if (ObjectPoolManager::getInstance()->setObject(error, "error"))
	{
	  error->setType(Error::USERCONNECTED);
	  this->_mutex->unlock();
	  Server::getInstance()->callProtocol<Error *>("ERROR", fd, error);
	  this->_mutex->lock();
	  delete error;
	}
    }
  else
    ret = false;
  this->_mutex->unlock();
  return (ret);
}

/*
** Protocol
*/

void				ClientManager::initializeProtocolFunction() const
{
  std::function<bool (Trame *)> func;

  func = std::bind1st(std::mem_fun(&ClientManager::connectionUser), this);
  Server::getInstance()->addFuncProtocol("CONNECTION", func);

  func = std::bind1st(std::mem_fun(&ClientManager::createPlayer), this);
  Server::getInstance()->addFuncProtocol("CREATE", func);

  func = std::bind1st(std::mem_fun(&ClientManager::choosePlayer), this);
  Server::getInstance()->addFuncProtocol("CHOOSEPLAYER", func);

  func = std::bind1st(std::mem_fun(&ClientManager::moveEntity), this);
  Server::getInstance()->addFuncProtocol("ENTITY", func);

  func = std::bind1st(std::mem_fun(&ClientManager::disconnectUser), this);
  Server::getInstance()->addFuncProtocol("DISCONNECT", func);

  func = std::bind1st(std::mem_fun(&ClientManager::disconnectPlayer), this);
  Server::getInstance()->addFuncProtocol("SWITCHPLAYER", func);
}

bool				ClientManager::moveEntity(Trame *trame)
{
  Player::PlayerCoordinate	*coord = NULL;

  if ((*trame)[CONTENT].isMember("ENTITY"))
    {
      coord = Player::PlayerCoordinate::deserialization((*trame)((*trame)[CONTENT]["ENTITY"]));
      this->setInfoClient((*trame)[HEADER]["IDCLIENT"].asInt(), coord);
      return (true);
    }
  return (false);
}

bool				ClientManager::connectionUser(Trame *trame)
{
  bool				ret = false;
  Error				*error = NULL;

  this->_mutex->lock();
  if ((*trame)[CONTENT].isMember("CONNECTION"))
    {
      User			*user = Database::getRepository<User>().getByPseudo((*trame)[CONTENT]["CONNECTION"]["PSEUDO"].asString());

      this->_mutex->unlock();
      if (user && this->userAlreadyConnected((*trame)[HEADER]["IDCLIENT"].asUInt(), user))
      	return (false);

      this->_mutex->lock();

      if (user && user->getPassword() == (*trame)[CONTENT]["CONNECTION"]["PASS"].asString())
	{
	  this->_mutex->unlock();
	  this->setInfoClient((*trame)[HEADER]["IDCLIENT"].asUInt(), user);
	  this->sendListPlayers((*trame)[HEADER]["IDCLIENT"].asUInt());
	  this->_mutex->lock();
	  ret = true;
	}
      else
	{
	  if (ObjectPoolManager::getInstance()->setObject(error, "error"))
	    {
	      error->setType(Error::USER);
	      this->_mutex->unlock();
	      Server::getInstance()->callProtocol<Error *>("ERROR", (*trame)[HEADER]["IDCLIENT"].asUInt(), error);
	      this->_mutex->lock();
	      delete error;
	    }
	}
    }
  this->_mutex->unlock();
  return (ret);
}

bool				ClientManager::createPlayer(Trame *trame)
{
  bool				ret;
  Error				*error = NULL;

  this->_mutex->lock();
  if ((*trame)[CONTENT].isMember("CREATE"))
    {

      Faction			*faction = Faction::deserialization((*trame)((*trame)[CONTENT]["CREATE"]));

      this->_mutex->unlock();
      this->setInfoClient((*trame)[HEADER]["IDCLIENT"].asInt(), (*trame)[CONTENT]["CREATE"]["NAME"].asString(), faction, ret);
      this->_mutex->lock();
      if (ret)
      	{
	  this->_mutex->unlock();
	  this->sendListPlayers((*trame)[HEADER]["IDCLIENT"].asInt());
	  this->_mutex->lock();
	}
      else
      	{
	  if (ObjectPoolManager::getInstance()->setObject(error, "error"))
	    {
	      error->setType(Error::CREATEPLAYER);
	      this->_mutex->unlock();
	      Server::getInstance()->callProtocol<Error *>("ERROR", (*trame)[HEADER]["IDCLIENT"].asUInt(), error);
	      this->_mutex->lock();
	      delete error;
	    }
	}
      this->_mutex->unlock();
      return (true);
    }
  this->_mutex->unlock();
  return (false);
}

bool				ClientManager::choosePlayer(Trame *trame)
{
  if ((*trame)[CONTENT].isMember("CHOOSEPLAYER"))
    {
      this->setInfoClient((*trame)[HEADER]["IDCLIENT"].asInt(), (*trame)[CONTENT]["CHOOSEPLAYER"].asUInt());
      return (true);
    }
  return (false);
}

bool				ClientManager::disconnectUser(Trame *trame)
{
  FD				fd;
  bool				set = false;

  this->_mutex->lock();
  if ((*trame)[CONTENT].isMember("DISCONNECT"))
    {
      fd = (*trame)[HEADER]["IDCLIENT"].asInt();
      for (auto it = this->_updaters->begin() ; it != this->_updaters->end() && !set ; ++it)
	if ((*it).first && (*it).second)
	  set = (*it).first->disconnectUser(fd);
    }
  this->_mutex->unlock();
  return (set);
}

bool				ClientManager::disconnectPlayer(Trame *trame)
{
  FD				fd;
  bool				set = false;

  this->_mutex->lock();
  if ((*trame)[CONTENT].isMember("SWITCHPLAYER"))
    {
      fd = (*trame)[HEADER]["IDCLIENT"].asInt();
      for (auto it = this->_updaters->begin() ; it != this->_updaters->end() && !set ; ++it)
	if ((*it).first && (*it).second)
	  set = (*it).first->disconnectPlayer(fd);
    }
  this->_mutex->unlock();
  return (set);
}
