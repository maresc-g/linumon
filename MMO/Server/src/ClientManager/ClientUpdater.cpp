//
// ClientUpdater.cpp for  in /home/ansel_l/Documents/Pfa/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Wed Dec  4 13:04:27 2013 laurent ansel
// Last update Wed Jan 29 16:12:48 2014 laurent ansel
//

#include			"ClientManager/ClientUpdater.hh"

ClientUpdater::ClientUpdater(unsigned int const nbClient):
  Thread(),
  _mutex(new Mutex),
  _quit(false),
  _action(new std::map<Client *, std::list<ReadWriteAction *> * >)
{
  _mutex->init();
  this->_mutex->lock();
  for (unsigned int i = 0 ; i < nbClient ; ++i)
    (*_action)[new Client] = new std::list<ReadWriteAction *>;
  this->_mutex->unlock();
  this->create(&runClientUpdater, this);
}

ClientUpdater::~ClientUpdater()
{
  this->_mutex->lock();
  for (auto it = this->_action->begin() ; it != this->_action->end() ; ++it)
    {
      delete (*it).first;
      for (auto itList =  (*it).second->begin() ; itList != (*it).second->end() ; ++itList)
	delete (*itList);
      delete (*it).second;
    }
  delete this->_action;
  this->_mutex->unlock();
  _mutex->destroy();
  delete this->_mutex;
}

void				ClientUpdater::check()
{
  this->_mutex->lock();
  for (auto it = this->_action->begin() ; it != this->_action->end() ; ++it)
    {
      if (!it->second->empty())
	{
	  for (auto itList =  (*it).second->begin() ; itList != (*it).second->end() ; ++itList)
	    if ((*itList)->isUse())
	      {
		if ((*itList)->getAction() == ReadWriteAction::READ)//ne pas oublier de verifier la lecture
		  {
		    this->_mutex->unlock();
		    this->readTrame((*it).first, (*itList)->getProtocole());
		    this->_mutex->lock();
		  }
		else
		  {
		    this->_mutex->unlock();
		    this->writeTrame((*it).first, (*itList)->getProtocole());
		    this->_mutex->lock();
		  }
		(*itList)->clear();
	      }
	}
    }
  this->_mutex->unlock();
}

void				ClientUpdater::run()
{
  this->_mutex->lock();
  while (!_quit)
    {
      this->_mutex->unlock();
      this->check();
      usleep(50000); //calculer le temps
      this->_mutex->lock();
    }
  this->_mutex->unlock();
}

void				ClientUpdater::setQuit(bool const quit)
{
  this->_mutex->lock();
  this->_quit = quit;
  this->_mutex->unlock();
}

bool				ClientUpdater::newClient(Header const &header, ISocketClient *client)
{
  this->_mutex->lock();
  for (auto it = this->_action->begin() ; it != this->_action->end() ; ++it)
    {
      if (!(*it).first->isUse())
	{
	  std::cout << "createUpdater" << std::endl;
	  (*it).first->use(header.getIdClient());
	  (*it).first->setSocket(client, header.getProtocole());
	  this->_mutex->unlock();
	  return (true);
	}
    }
  this->_mutex->unlock();
  return (false);
}

bool				ClientUpdater::setInfo(FD const fd, ISocketClient *client, std::string const &proto) const
{
  this->_mutex->lock();
  for (auto it = this->_action->begin() ; it != this->_action->end() ; ++it)
    {
      if (fd == (*it).first->getId() && (*it).first->isUse())
	{
	  (*it).first->setSocket(client, proto);
	  this->_mutex->unlock();
	  return (true);
	}
    }
  this->_mutex->unlock();
  return (false);
}

bool				ClientUpdater::setInfo(FD const fd, bool const disconnect) const
{
  this->_mutex->lock();
  for (auto it = this->_action->begin() ; it != this->_action->end() ; ++it)
    {
      if (fd == (*it).first->getId() && (*it).first->isUse() && disconnect)
	{
	  (*it).first->clear();
	  this->_mutex->unlock();
	  return (true);
	}
    }
  this->_mutex->unlock();
  return (false);
}

bool				ClientUpdater::setInfo(FD const fd, unsigned int const nbTrame) const
{
  this->_mutex->lock();
  for (auto it = this->_action->begin() ; it != this->_action->end() ; ++it)
    {
      if (fd == (*it).first->getId() && (*it).first->isUse())
	{
	  (*it).first->addTrame(nbTrame);
	  this->_mutex->unlock();
	  return (true);
	}
    }
  this->_mutex->unlock();
  return (false);
}

bool				ClientUpdater::setInfo(FD const fd, unsigned int const idPlayer, bool const send) const
{
  this->_mutex->lock();
  for (auto it = this->_action->begin() ; it != this->_action->end() ; ++it)
    {
      if (fd == (*it).first->getId() && (*it).first->isUse())
	{
	  (*it).first->choosePlayer(idPlayer, send);
	  this->_mutex->unlock();
	  return (true);
	}
    }
  this->_mutex->unlock();
  return (false);
}

bool				ClientUpdater::setInfo(FD const fd, std::string const &name, std::string const &faction, bool &ok) const
{
  this->_mutex->lock();
  for (auto it = this->_action->begin() ; it != this->_action->end() ; ++it)
    {
      if (fd == (*it).first->getId() && (*it).first->isUse())
	{
	  ok = (*it).first->addPlayer(name, faction);
	  this->_mutex->unlock();
	  return (true);
	}
    }
  this->_mutex->unlock();
  return (false);
}

void				ClientUpdater::readTrame(Client *client, std::string const &protocole) const
{
  std::string			str;
  Trame				*trame;

  this->_mutex->lock();
  if (client->isUse())
    {
      if (client->readTrame(str, protocole))
	{
	  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
	  std::cout << "RET = " << Trame::toTrame(*trame, str) << std::endl;
	  CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::READ_BUFFER);
	}
    }
  this->_mutex->unlock();
}

void				ClientUpdater::writeTrame(Client *client, std::string const &protocole) const
{
  Trame				*trame;

  this->_mutex->lock();
  if (client->isUse())
    {
      trame = CircularBufferManager::getInstance()->popTrame(client->getId(), protocole, CircularBufferManager::WRITE_BUFFER);
      if (trame)
	{
	  if (client->writeTrame(trame, protocole))
	    delete trame;
	  else
	    CircularBufferManager::getInstance()->pushFrontTrame(trame, CircularBufferManager::WRITE_BUFFER);
	}
    }
  this->_mutex->unlock();
}

void				ClientUpdater::readClient(FD const fd, std::string const &protocole)
{
  bool				set = false;

  this->_mutex->lock();
  for (auto it = this->_action->begin() ; it != this->_action->end() ; ++it)
    {
      if (fd == (*it).first->getId() && (*it).first->isUse())
	{
	  for (auto itA = (*it).second->begin() ; itA != (*it).second->end() ; ++itA)
	    if (!(*itA)->isUse())
	      {
		(*itA)->setProtocole(protocole);
		(*itA)->setAction(ReadWriteAction::READ);
		(*itA)->use();
		set = true;
	      }
	  if (!set)
	    (*it).second->push_back(new ReadWriteAction(protocole, ReadWriteAction::READ));
	}
    }
  this->_mutex->unlock();
}

void				ClientUpdater::canWrite(FD const fd, std::string const &protocole)
{
  bool				set = false;

  this->_mutex->lock();
  for (auto it = this->_action->begin() ; it != this->_action->end() ; ++it)
    {
      if (fd == (*it).first->getId() && (*it).first->isUse())
	{
	  for (auto itA = (*it).second->begin() ; itA != (*it).second->end() ; ++itA)
	    if (!(*itA)->isUse())
	      {
		(*itA)->setProtocole(protocole);
		(*itA)->setAction(ReadWriteAction::WRITE);
		(*itA)->use();
		set = true;
	      }
	  if (!set)
	    (*it).second->push_back(new ReadWriteAction(protocole, ReadWriteAction::WRITE));
	}
    }
  this->_mutex->unlock();

}

bool				ClientUpdater::search(FD const fd) const
{
  this->_mutex->lock();
  for (auto it = this->_action->begin() ; it != this->_action->end() ; ++it)
    {
      if (fd == (*it).first->getId() && (*it).first->isUse())
	{
	  this->_mutex->unlock();
	  return (true);
	}
    }
  this->_mutex->unlock();
  return (false);
}

void				ClientUpdater::getClients(std::list<FD> &list) const
{
  this->_mutex->lock();
  for (auto it = this->_action->begin() ; it != this->_action->end() ; ++it)
    {
      if ((*it).first->isUse())
	list.push_back((*it).first->getId());
    }
  this->_mutex->unlock();
}

unsigned int			ClientUpdater::getNbTrame(FD const fd) const
{
  unsigned int			nb = 0;

  this->_mutex->lock();
  for (auto it = this->_action->begin() ; it != this->_action->end() ; ++it)
    {
      if (fd == (*it).first->getId() && (*it).first->isUse())
	{
	  nb = (*it).first->getNbTrame();
	  this->_mutex->unlock();
	  return (nb);
	}
    }
  this->_mutex->unlock();
  return (nb);
}

void				*runClientUpdater(void *data)
{
  if (data)
    {
      ClientUpdater		*updater = reinterpret_cast<ClientUpdater *>(data);

      updater->run();
    }
  return (NULL);
}
