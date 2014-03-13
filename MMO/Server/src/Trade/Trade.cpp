//
// Trade.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Sat Feb  8 17:40:51 2014 laurent ansel
// Last update Wed Mar 12 22:47:40 2014 laurent ansel
//

#include			<functional>
#include			"Trade/Trade.hh"
#include			"Server/Server.hh"

Trade::Trade():
  _player1(NULL),
  _player2(NULL),
  _mobs1(new std::list<Mob *>),
  _mobs2(new std::list<Mob *>),
  _items1(new std::list<AItem *>),
  _items2(new std::list<AItem *>),
  _money1(0),
  _money2(0),
  _accept1(false),
  _accept2(false)
{
}

Trade::~Trade()
{
  delete _items1;
  delete _items2;
}

void				Trade::launchTrade(Player *player1, Player *player2)
{
  _player1 = player1;
  _player2 = player2;
  if (_player1 && _player2)
    {
      Server::getInstance()->callProtocol<unsigned int, std::string>("LAUNCHTRADE", player2->getUser().getId(), getId(), player1->getName());
      Server::getInstance()->callProtocol<unsigned int, std::string>("LAUNCHTRADE", player1->getUser().getId(), getId(), player2->getName());
    }
}

bool				Trade::stopTrade(unsigned int const idPlayer)
{
  if ((_player1 && _player1->getId() == idPlayer) || (_player2 && _player2->getId() == idPlayer))
    {
      for (auto it = _mobs1->begin() ; it != _mobs1->end() ; ++it)
	_player1->addMob(*it);
      _mobs1->clear();
      for (auto it = _mobs2->begin() ; it != _mobs2->end() ; ++it)
	_player2->addMob(*it);
      _mobs2->clear();
      for (auto it = _items1->begin() ; it != _items1->end() ; ++it)
	_player1->addItem(*it);
      _items1->clear();
      for (auto it = _items2->begin() ; it != _items2->end() ; ++it)
	_player2->addItem(*it);
      _items2->clear();
      _player1->addMoney(_money1);
      _player2->addMoney(_money2);
      _money1 = 0;
      _money2 = 0;
      _player1 = NULL;
      _player2 = NULL;
      _accept1 = false;
      _accept2 = false;
      if (_player2->getId() == idPlayer)
	{
	  Server::getInstance()->callProtocol<unsigned int>("REFUSE", _player1->getUser().getId(), getId());
	  Server::getInstance()->newClientStateInStandBy(_player1->getUser().getId(), Client::eState::GAME);
	  //	  ClientManager::getInstance()->endTrade(_player1->getUser().getId()); probleme mutex
	}
      if (_player1->getId() == idPlayer)
	{
	  Server::getInstance()->callProtocol<unsigned int>("REFUSE", _player2->getUser().getId(), getId());
	  Server::getInstance()->newClientStateInStandBy(_player2->getUser().getId(), Client::eState::GAME);
	  //	  ClientManager::getInstance()->endTrade(_player2->getUser().getId()); probleme mutex
	}
      return (true);
    }
  return (false);
}

unsigned int			Trade::getIdPlayer(unsigned int const idUser) const
{
  unsigned int			ret = 0;

  if (_player1 && _player1->getUser().getId() == idUser)
    ret = _player1->getId();
  else if (_player2 && _player2->getUser().getId() == idUser)
    ret = _player2->getId();
  return (ret);
}

bool				Trade::getMob(unsigned int const id, unsigned int const idMob)
{
  if (_player1->getId() == id)
    {
      auto it = _mobs1->begin();

      for (; it != _mobs1->end() && (*it)->getId() != idMob ; ++it);
      if (it != _mobs1->end() && (*it)->getId() != idMob)
	{
	  _player1->addMob(*it);
	  _mobs1->erase(it);
	  Server::getInstance()->callProtocol<unsigned int, Mob const *>("GETMOB", _player2->getUser().getId(), getId(), *it);
	}
    }
  else
    {
      auto it = _mobs2->begin();

      for (; it != _mobs2->end() && (*it)->getId() != idMob ; ++it);
      if (it != _mobs2->end() && (*it)->getId() != idMob)
	{
	  _player2->addMob(*it);
	  _mobs2->erase(it);
	  Server::getInstance()->callProtocol<unsigned int, Mob const *>("GETMOB", _player1->getUser().getId(), getId(), *it);
	}
    }
  return (true);
}

bool				Trade::putMob(unsigned int const id, unsigned int const idMob)
{
  Mob				*mob = NULL;

  if (_player1->getId() == id)
    {
      mob = _player1->getAndDeleteMob(idMob);
      if (mob)
	{
	  _mobs1->push_back(mob);
	  Server::getInstance()->callProtocol<unsigned int, Mob const *>("PUTMOB", _player2->getUser().getId(), getId(), mob);
	}
    }
  else
    {
      mob = _player2->getAndDeleteMob(idMob);
      if (mob)
	{
	  _mobs2->push_back(mob);
	  Server::getInstance()->callProtocol<unsigned int, Mob const *>("PUTMOB", _player1->getUser().getId(), getId(), mob);
	}
    }
  return (true);
}

bool				Trade::getItem(unsigned int const id, unsigned int const idItem)
{
  if (_player1->getId() == id)
    {
      auto it = _items1->begin();

      for (; it != _items1->end() && (*it)->getId() != idItem ; ++it);
      if (it != _items1->end() && (*it)->getId() != idItem)
	{
	  _player1->addItem(*it);
	  _items1->erase(it);
	  Server::getInstance()->callProtocol<unsigned int, AItem const *>("GETITEM", _player2->getUser().getId(), getId(), *it);
	}
    }
  else
    {
      auto it = _items2->begin();

      for (; it != _items2->end() && (*it)->getId() != idItem ; ++it);
      if (it != _items2->end() && (*it)->getId() != idItem)
	{
	  _player2->addItem(*it);
	  _items2->erase(it);
	  Server::getInstance()->callProtocol<unsigned int, AItem const *>("GETITEM", _player1->getUser().getId(), getId(), *it);
	}
    }
  return (true);
}

bool				Trade::putItem(unsigned int const id, unsigned int const idItem)
{
  AItem				*item = NULL;

  if (_player1->getId() == id)
    {
      item = _player1->getAndDeleteItem(idItem);
      if (item)
	{
	  _items1->push_back(item);
	  Server::getInstance()->callProtocol<unsigned int, AItem const *>("PUTITEM", _player2->getUser().getId(), getId(), item);
	}
    }
  else
    {
      item = _player2->getAndDeleteItem(idItem);
      if (item)
	{
	  _items2->push_back(item);
	  Server::getInstance()->callProtocol<unsigned int, AItem const *>("PUTITEM", _player1->getUser().getId(), getId(), item);
	}
    }
  return (true);
}

bool				Trade::getMoney(unsigned int const id, int const money)
{
  if (_player1->getId() == id)
    {
      _player1->addMoney(money);
      _money1 -= money;
      Server::getInstance()->callProtocol<unsigned int, unsigned int>("GETMONEY", _player2->getUser().getId(), getId(), money);
    }
  else
    {
      _player2->addMoney(money);
      _money2 -= money;
      Server::getInstance()->callProtocol<unsigned int, unsigned int>("GETMONEY", _player1->getUser().getId(), getId(), money);
    }
  return (true);
}

bool				Trade::putMoney(unsigned int const id, int const money)
{
  if (_player1->getId() == id)
    {
      _player1->addMoney(-money);
      _money1 += money;
      Server::getInstance()->callProtocol<unsigned int, unsigned int>("PUTMONEY", _player2->getUser().getId(), getId(), money);
    }
  else
    {
      _player2->addMoney(-money);
      _money2 += money;
      Server::getInstance()->callProtocol<unsigned int, unsigned int>("PUTMONEY", _player1->getUser().getId(), getId(), money);
    }
  return (true);
}

bool				Trade::accept(unsigned int const id)
{
  if (_player1->getId() == id)
    {
      _accept1 = true;
      Server::getInstance()->callProtocol<unsigned int>("ACCEPT", _player2->getUser().getId(), getId());
    }
  if (_player2->getId() == id)
    {
      _accept2 = true;
      Server::getInstance()->callProtocol<unsigned int>("ACCEPT", _player1->getUser().getId(), getId());
    }
  if (_accept1 && _accept2)
    {
      for (auto it = _items1->begin() ; it != _items1->end() ; ++it)
	_player2->addItem(*it);
      _items1->clear();
      for (auto it = _items2->begin() ; it != _items2->end() ; ++it)
	_player1->addItem(*it);
      _items2->clear();
      _player2->addMoney(_money1);
      _player1->addMoney(_money2);
      _money1 = 0;
      _money2 = 0;
      _accept1 = false;
      _accept2 = false;
    }
  return (true);
}

bool				Trade::refuse()
{
  for (auto it = _mobs1->begin() ; it != _mobs1->end() ; ++it)
    _player1->addMob(*it);
  _mobs1->clear();
  for (auto it = _mobs2->begin() ; it != _mobs2->end() ; ++it)
    _player2->addMob(*it);
  _mobs2->clear();
  for (auto it = _items1->begin() ; it != _items1->end() ; ++it)
    _player1->addItem(*it);
  _items1->clear();
  for (auto it = _items2->begin() ; it != _items2->end() ; ++it)
    _player2->addItem(*it);
  _items2->clear();
  _player1->addMoney(_money1);
  _player2->addMoney(_money2);
  _money1 = 0;
  _money2 = 0;
  _accept1 = false;
  _accept2 = false;
  Server::getInstance()->callProtocol<unsigned int>("REFUSE", _player1->getUser().getId(), getId());
  Server::getInstance()->callProtocol<unsigned int>("REFUSE", _player2->getUser().getId(), getId());
  ClientManager::getInstance()->endTrade(_player1->getUser().getId());
  ClientManager::getInstance()->endTrade(_player2->getUser().getId());
  return (true);
}
