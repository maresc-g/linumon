//
// ClientUpdater.cpp for  in /home/ansel_l/Documents/Pfa/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Wed Dec  4 13:04:27 2013 laurent ansel
// Last update Wed Mar 26 10:39:07 2014 guillaume marescaux
//

#include			"ClientManager/ClientUpdater.hh"
#include			"Server/Server.hh"
#include			"ClientWriter/ClientWriter.hh"

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
	  ClientWriter::getInstance()->newClient(header.getIdClient());
	  this->_mutex->unlock();
	  return (true);
	}
    }
  this->_mutex->unlock();
  return (false);
}

bool				ClientUpdater::setInfo(FD const fd, ISocketClient const *client, std::string const &proto) const
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
	  ClientWriter::getInstance()->deleteClient(fd);
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

bool				ClientUpdater::setInfo(FD const fd, std::string const &name, Faction *faction, bool &ok) const
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

bool				ClientUpdater::setInfo(FD const fd, User *user) const
{
  this->_mutex->lock();
  for (auto it = this->_action->begin() ; it != this->_action->end() ; ++it)
    {
      if (fd == (*it).first->getId() && (*it).first->isUse())
	{
	  (*it).first->addUser(user);
	  this->_mutex->unlock();
	  return (true);
	}
    }
  this->_mutex->unlock();
  return (false);
}

bool				ClientUpdater::setInfo(FD const fd, Player::PlayerCoordinate *coord) const
{
  this->_mutex->lock();
  for (auto it = this->_action->begin() ; it != this->_action->end() ; ++it)
    {
      if (fd == (*it).first->getId() && (*it).first->isUse())
	{
	  (*it).first->move(coord);
	  this->_mutex->unlock();
	  return (true);
	}
    }
  this->_mutex->unlock();
  return (false);
}

void				ClientUpdater::sendAllInformationModel(FD const fd) const
{
  bool				set = false;

  this->_mutex->lock();
  for (auto it = this->_action->begin() ; it != this->_action->end() && !set ; ++it)
    {
      if (fd == (*it).first->getId() && (*it).first->isUse())
	{
	  (*it).first->sendAllInformationModel();
	  set = true;
	}
    }
  this->_mutex->unlock();
}

bool				ClientUpdater::sendListPlayers(FD const fd) const
{
  this->_mutex->lock();
  for (auto it = this->_action->begin() ; it != this->_action->end() ; ++it)
    {
      if (fd == (*it).first->getId() && (*it).first->isUse())
	{
	  (*it).first->sendListPlayers();
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
  //  Trame				*trame;

  this->_mutex->lock();
  if (client->isUse())
    {
      if (client->readTrame(str, protocole))
	{
	  //	  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
	  //	  Trame::toTrame(*trame, str);

	  std::list<Trame *>	*list = Trame::toTrame(str);
	  for (auto it = list->begin() ; it != list->end() ; ++it)
	    {
	      if (*it)
		CircularBufferManager::getInstance()->pushTrame(*it, CircularBufferManager::READ_BUFFER);
	    }
	  delete list;
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

bool				ClientUpdater::setTalents(FD const fd, std::string const &talent, unsigned int const pts) const
{
  this->_mutex->lock();
  std::cout << "I AM IN SET TALENTS" << std::endl;
  for (auto it = this->_action->begin() ; it != this->_action->end() ; ++it)
    {
      if (fd == (*it).first->getId() && (*it).first->isUse())
	{
	  std::cout << "I AM UPDATING TALENTS" << std::endl;
	  (*it).first->updateTalents(talent, pts);
	  this->_mutex->unlock();
	  return (true);
	}
    }
  this->_mutex->unlock();
  return (false);
}

bool				ClientUpdater::modifyDigitaliser(FD const fd, unsigned int const idMob1, unsigned int const idMob2, bool const toBattleMob) const
{
  this->_mutex->lock();
  for (auto it = this->_action->begin() ; it != this->_action->end() ; ++it)
    {
      if (fd == (*it).first->getId() && (*it).first->isUse())
	{
	  (*it).first->modifyDigitaliser(idMob1, idMob2, toBattleMob);
	  this->_mutex->unlock();
	  return (true);
	}
    }
  this->_mutex->unlock();
  return (false);
}


bool				ClientUpdater::playerObject(FD const fd, unsigned int const target, unsigned int const item) const
{
  this->_mutex->lock();
  for (auto it = this->_action->begin() ; it != this->_action->end() ; ++it)
    {
      if (fd == (*it).first->getId() && (*it).first->isUse())
	{
	  (*it).first->useObject(target, item);
	  this->_mutex->unlock();
	  return (true);
	}
    }
  this->_mutex->unlock();
  return (false);
}

bool				ClientUpdater::playerObject(FD const fd, unsigned int const item, int const nb) const
{
  this->_mutex->lock();
  for (auto it = this->_action->begin() ; it != this->_action->end() ; ++it)
    {
      if (fd == (*it).first->getId() && (*it).first->isUse())
	{
	  (*it).first->deleteObject(item, nb);
	  this->_mutex->unlock();
	  return (true);
	}
    }
  this->_mutex->unlock();
  return (false);
}

bool				ClientUpdater::newGuild(FD const fd, Guild *guild) const
{
  bool				ret = false;

  this->_mutex->lock();
  for (auto it = this->_action->begin() ; it != this->_action->end() ; ++it)
    {
      if (fd == (*it).first->getId() && (*it).first->isUse())
	ret = (*it).first->newGuild(guild);
    }
  this->_mutex->unlock();
  return (ret);
}

bool				ClientUpdater::newGuild(std::string const &playerName, Guild *guild) const
{
  bool				ret = false;

  this->_mutex->lock();
  for (auto it = this->_action->begin() ; it != this->_action->end() ; ++it)
    {
      if (playerName == (*it).first->getName() && (*it).first->isUse())
	ret = (*it).first->newGuild(guild);
    }
  this->_mutex->unlock();
  return (ret);
}

bool				ClientUpdater::inviteInGuild(std::string const &name, std::string const &nameGuild) const
{
  bool				ret = false;

  this->_mutex->lock();
  for (auto it = this->_action->begin() ; it != this->_action->end() ; ++it)
    {
      if (name == (*it).first->getName() && (*it).first->isUse())
	{
	  ret = (*it).first->inviteInGuild(nameGuild);
	  this->_mutex->unlock();
	  return (ret);
	}
    }
  this->_mutex->unlock();
  return (ret);
}

bool				ClientUpdater::inGuild(FD const fd, bool &guild) const
{
  bool				ret = false;

  this->_mutex->lock();
  for (auto it = this->_action->begin() ; it != this->_action->end() ; ++it)
    {
      if (fd == (*it).first->getId() && (*it).first->isUse())
	{
	  guild = (*it).first->inGuild();
	  ret = true;
	}
    }
  this->_mutex->unlock();
  return (ret);
}

bool				ClientUpdater::merge(FD const fd, unsigned int const idStack, unsigned int const idStack2) const
{
  this->_mutex->lock();
  for (auto it = this->_action->begin() ; it != this->_action->end() ; ++it)
    {
      if (fd == (*it).first->getId() && (*it).first->isUse())
	{
	  (*it).first->merge(idStack, idStack2);
	  this->_mutex->unlock();
	  return (true);
	}
    }
  this->_mutex->unlock();
  return (false);
}

bool				ClientUpdater::newStack(FD const fd, unsigned int const idStack, unsigned int const nb) const
{
  this->_mutex->lock();
  for (auto it = this->_action->begin() ; it != this->_action->end() ; ++it)
    {
      if (fd == (*it).first->getId() && (*it).first->isUse())
	{
	  (*it).first->newStack(idStack, nb);
	  this->_mutex->unlock();
	  return (true);
	}
    }
  this->_mutex->unlock();
  return (false);
}

bool				ClientUpdater::stateBattle(FD const fd, bool const start, bool const end, Player *&player) const
{
  this->_mutex->lock();
  for (auto it = this->_action->begin() ; it != this->_action->end() ; ++it)
    {
      if (fd == (*it).first->getId() && (*it).first->isUse())
	{
	  if (start)
	    (*it).first->startBattle(player);
	  if (end)
	    (*it).first->endBattle();
	  this->_mutex->unlock();
	  return (true);
	}
    }
  this->_mutex->unlock();
  return (false);
}

bool				ClientUpdater::stateTrade(FD const fd, bool const start, bool const end, Player *&player) const
{
  this->_mutex->lock();
  for (auto it = this->_action->begin() ; it != this->_action->end() ; ++it)
    {
      if (fd == (*it).first->getId() && (*it).first->isUse())
	{
	  if (start)
	    (*it).first->startTrade(player);
	  if (end)
	    (*it).first->endTrade();
	  this->_mutex->unlock();
	  return (true);
	}
    }
  this->_mutex->unlock();
  return (false);
}

void				ClientUpdater::newState(FD const fd, Client::eState const st) const
{
  this->_mutex->lock();
  for (auto it = this->_action->begin() ; it != this->_action->end() ; ++it)
    {
      if (fd == (*it).first->getId() && (*it).first->isUse())
	{
	  it->first->state(st);
	  this->_mutex->unlock();
	  return;
	}
    }
  this->_mutex->unlock();
}

void				ClientUpdater::heal(FD const fd) const
{
  this->_mutex->lock();
  for (auto it = this->_action->begin() ; it != this->_action->end() ; ++it)
    {
      if (fd == (*it).first->getId() && (*it).first->isUse())
	{
	  it->first->heal();
	  this->_mutex->unlock();
	  return;
	}
    }
  this->_mutex->unlock();
}

bool				ClientUpdater::stuff(FD const fd, bool const get, unsigned int const idItem, unsigned int const target) const
{
  bool				ret;

  this->_mutex->lock();
  for (auto it = this->_action->begin() ; it != this->_action->end() ; ++it)
    {
      if (fd == (*it).first->getId() && (*it).first->isUse())
	{
	  ret = it->first->stuff(get, idItem, target);
	  this->_mutex->unlock();
	  return (ret);
	}
    }
  this->_mutex->unlock();
  return (false);
}

bool				ClientUpdater::disconnectUser(FD const fd) const
{
  this->_mutex->lock();
  for (auto it = this->_action->begin() ; it != this->_action->end() ; ++it)
    {
      if (fd == (*it).first->getId() && (*it).first->isUse())
	{
	  it->first->disconnectUser();
	  this->_mutex->unlock();
	  return (true);
	}
    }
  this->_mutex->unlock();
  return (false);
}

bool				ClientUpdater::disconnectPlayer(FD const fd) const
{
  this->_mutex->lock();
  for (auto it = this->_action->begin() ; it != this->_action->end() ; ++it)
    {
      if (fd == (*it).first->getId() && (*it).first->isUse())
	{
	  it->first->disconnectPlayer();
	  this->_mutex->unlock();
	  return (true);
	}
    }
  this->_mutex->unlock();
  return (false);
}

bool				ClientUpdater::craftSomething(FD const fd, std::string const &craft, std::string const &job) const
{
  bool				ret = false;

  this->_mutex->lock();
  for (auto it = this->_action->begin() ; it != this->_action->end() ; ++it)
    {
      if (fd == (*it).first->getId() && (*it).first->isUse())
	{
	  ret = it->first->craft(craft, job);
	  this->_mutex->unlock();
	  return (ret);
	}
    }
  this->_mutex->unlock();
  return (ret);
}

bool				ClientUpdater::gatherSomething(FD const fd, unsigned int const gather, std::string const &job, unsigned int const carcass) const
{
  bool				ret = false;

  this->_mutex->lock();
  for (auto it = this->_action->begin() ; it != this->_action->end() ; ++it)
    {
      if (fd == (*it).first->getId() && (*it).first->isUse())
	{
	  ret = it->first->gather(gather, job, carcass);
	  this->_mutex->unlock();
	  return (ret);
	}
    }
  this->_mutex->unlock();
  return (ret);
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
