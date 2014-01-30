//
// ClientManager.cpp for  in /home/ansel_l/Documents/Pfa/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Wed Dec  4 11:22:44 2013 laurent ansel
// Last update Thu Jan 30 14:42:21 2014 laurent ansel
//

#include			"Database/Database.hpp"
#include			"Entities/User-odb.hxx"
#include			"ClientManager/ClientManager.hh"
#include			"Error/Error.hpp"
#include			"Server/Server.hh"

ClientManager::ClientManager():
  _updaters(new std::vector<std::pair<ClientUpdater *, bool> >),
  _serverWriteFunc(NULL),
  _quit(false),
  _mutex(new Mutex)
{
  _mutex->init();
  _mutex->lock();
  std::function<bool (Trame *)> func;

  func = std::bind1st(std::mem_fun(&ClientManager::connectionUser), this);
  Server::getInstance()->addFuncProtocol("CONNECTION", func);

  func = std::bind1st(std::mem_fun(&ClientManager::createPlayer), this);
  Server::getInstance()->addFuncProtocol("CREATE", func);

  func = std::bind1st(std::mem_fun(&ClientManager::choosePlayer), this);
  Server::getInstance()->addFuncProtocol("CHOOSEPLAYER", func);

  for (int i = 0 ; i < CLIENT_THREAD_MIN ; ++i)
    _updaters->push_back(std::make_pair(new ClientUpdater(NB_CLIENTS_PER_THREAD), false));
  _mutex->unlock();
  this->create(&runClientManager, this);
  this->start();
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

void				ClientManager::setWriteFunction(function *writeFunc)
{
  _serverWriteFunc = writeFunc;
}

void				ClientManager::setQuit(bool const quit)
{
  _mutex->lock();
  _quit = quit;
  _mutex->unlock();
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

void				ClientManager::setInfoClient(FD const fd, std::string const &name, std::string const &faction, bool &ok) const
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

void				ClientManager::findWrite() const
{
  std::list<FD>			list;

  this->_mutex->lock();
  for (auto it = this->_updaters->begin() ; it != this->_updaters->end() ; ++it)
    if ((*it).first && (*it).second)
      {
	(*it).first->getClients(list);
	this->_mutex->unlock();
	for (auto itClient = list.begin() ; itClient != list.end() ; ++itClient)
	  {
	    this->_mutex->lock();
	    if ((*it).first->getNbTrame((*itClient)) > 0)
	      {
		// this->_mutex->unlock();
		if (this->_serverWriteFunc)
		  {
		    (*this->_serverWriteFunc)(*itClient);
		  }
		// this->_mutex->lock();
	      }
	    this->_mutex->unlock();
	  }
	this->_mutex->lock();
      }
  this->_mutex->unlock();
}

void				ClientManager::newTrameToWrite(FD const fd, unsigned int const nbTrame) const
{
  bool				set = false;

  this->_mutex->lock();
  for (auto it = this->_updaters->begin() ; it != this->_updaters->end() && !set ; ++it)
    if ((*it).first && (*it).second && (*it).first->search(fd))
      {
	(*it).first->setInfo(fd, nbTrame);
	set = true;
      }
  this->_mutex->unlock();
}

void				ClientManager::run()
{
  int				size;

  this->_mutex->lock();
  while (!_quit)
    {
      this->_mutex->unlock();
      this->findWrite();
      this->_mutex->lock();
      if (!(size = this->_updaters->size()))
	size = 1;
      this->_mutex->unlock();
      usleep(1000000 / size);
      this->_mutex->lock();
    }
  this->_mutex->unlock();
}

bool				ClientManager::connectionUser(Trame *trame)
{
  bool				ret = false;
  Error				*error = NULL;

  this->_mutex->lock();
  if ((*trame)[CONTENT].isMember("CONNECTION"))
    {
      User			*user = NULL;
      Database			*db = Database::getInstance();
      odb::transaction		t(db->getDb()->begin());
      odb::query<User>		q(odb::query<User>::pseudo == (*trame)[CONTENT]["CONNECTION"]["PSEUDO"].asString());
      odb::result<User>		r(db->getDb()->query<User>(q));

      for (auto it = r.begin() ; it != r.end() ; ++it) {
	user = it.load();
      }

      std::cout << "Pseudo = |" << user->getPseudo() << "|"<< std::endl;
      std::cout << "Password = |" << user->getPassword() << "|"<< std::endl;

      if (user && user->getPassword() == (*trame)[CONTENT]["CONNECTION"]["PASS"].asString())
	{
	  this->_mutex->unlock();
	  //	  Server::getInstance()->callProtocol("PLAYERLIST", (*trame)[HEADER]["IDCLIENT"].asUInt(), user->getPlayers());
	  this->setInfoClient((*trame)[HEADER]["IDCLIENT"].asUInt(), user);
	  this->_mutex->lock();
	  ret = true;
	}
      else
	{

	  if (ObjectPoolManager::getInstance()->setObject(error, "error"))
	    {
	      error->setType(Error::USER);
	      this->_mutex->unlock();
	      Server::getInstance()->callProtocol("ERROR", (*trame)[HEADER]["IDCLIENT"].asUInt(), error);
	      this->_mutex->lock();
	      delete error;
	    }
	}
      t.commit();
    }
  this->_mutex->unlock();
  return (ret);
}

bool				ClientManager::createPlayer(Trame *trame)
{
  bool				ret;
  Error				*error = NULL;

  if ((*trame)[CONTENT].isMember("CREATE"))
    {
      this->setInfoClient((*trame)[HEADER]["IDCLIENT"].asInt(), (*trame)[CONTENT]["CREATE"]["NAME"].asString(), (*trame)[CONTENT]["CREATE"]["FACTION"].asString(), ret);
      if (ret)
	{
	  /*
	  ** send player list
	  */
	}
      else
	{
	  if (ObjectPoolManager::getInstance()->setObject(error, "error"))
	    {
	      error->setType(Error::CREATEPLAYER);
	      if (Server::getInstance()->callProtocol("ERROR", (*trame)[HEADER]["IDCLIENT"].asUInt(), error))
		ClientManager::getInstance()->newTrameToWrite((*trame)[HEADER]["IDCLIENT"].asUInt(), 1);
	      delete error;
	    }
	}
      return (true);
    }
  return (false);
}

bool				ClientManager::choosePlayer(Trame *trame)
{
  if ((*trame)[CONTENT].isMember("CHOOSEPLAYER"))
    this->setInfoClient((*trame)[HEADER]["IDCLIENT"].asInt(), (*trame)[CONTENT]["CHOOSEPLAYER"].asUInt());
  return (false);
}

void				*runClientManager(void *data)
{
  if (data)
    {
      ClientManager		*manager = reinterpret_cast<ClientManager *>(data);

      manager->run();
    }
  return (NULL);
}
