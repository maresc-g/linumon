//
// ClientManager.cpp for  in /home/ansel_l/Documents/Pfa/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Wed Dec  4 11:22:44 2013 laurent ansel
// Last update Sat Feb  8 16:38:50 2014 laurent ansel
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
    this->setInfoClient((*trame)[HEADER]["IDCLIENT"].asInt(), (*trame)[CONTENT]["CHOOSEPLAYER"].asUInt());
  return (false);
}
