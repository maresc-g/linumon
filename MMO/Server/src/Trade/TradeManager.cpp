//
// TradeManager.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Wed Feb 12 20:20:01 2014 laurent ansel
// Last update Fri Mar 14 20:42:14 2014 laurent ansel
//

#include			<functional>
#include			"Trade/TradeManager.hh"
#include			"Server/Server.hh"

TradeManager::TradeManager():
  _list(new std::list<std::pair<bool, Trade *> >),
  _mutex(new Mutex)
{
  _mutex->init();

  std::function<bool (Trame *)> func;


  func = std::bind1st(std::mem_fun(&TradeManager::putMob), this);
  Server::getInstance()->addFuncProtocol("PUTMOB", func);

  func = std::bind1st(std::mem_fun(&TradeManager::getMob), this);
  Server::getInstance()->addFuncProtocol("GETMOB", func);

  func = std::bind1st(std::mem_fun(&TradeManager::putItem), this);
  Server::getInstance()->addFuncProtocol("PUTITEM", func);

  func = std::bind1st(std::mem_fun(&TradeManager::getItem), this);
  Server::getInstance()->addFuncProtocol("GETITEM", func);

  func = std::bind1st(std::mem_fun(&TradeManager::putMoney), this);
  Server::getInstance()->addFuncProtocol("PUTMONEY", func);

  func = std::bind1st(std::mem_fun(&TradeManager::getMoney), this);
  Server::getInstance()->addFuncProtocol("GETMONEY", func);

  func = std::bind1st(std::mem_fun(&TradeManager::refuse), this);
  Server::getInstance()->addFuncProtocol("REFUSE", func);

  func = std::bind1st(std::mem_fun(&TradeManager::accept), this);
  Server::getInstance()->addFuncProtocol("ACCEPT", func);

  _mutex->lock();
  for (auto i = 0 ; i < DEFAULT_TRADE ; ++i)
    _list->push_back(std::make_pair(false, new Trade));
  _mutex->unlock();
}

TradeManager::~TradeManager()
{
  _mutex->lock();
  for (auto it = _list->begin() ; it != _list->end() ; ++it)
    delete it->second;
  delete _list;
  _mutex->unlock();
  _mutex->destroy();
  delete _mutex;
}

void				TradeManager::newTrade(Player *player1, Player *player2)
{
  std::cout << "LOCK" << std::endl;
  this->_mutex->lock();
  auto				it = _list->begin();

  std::cout << "TRADEMANAGER" << std::endl;
  for (; it != _list->end() && it->first ; ++it);
  if (!it->first && it->second)
    {
      std::cout << "NEW TRADE" << std::endl;
      it->second->launchTrade(player1, player2);
      it->first = true;
    }
  if (it == _list->end())
    {
      this->_list->push_back(std::make_pair(false, new Trade));
      it->second->launchTrade(player1, player2);
      it->first = true;
    }
  this->_mutex->unlock();
  std::cout << "UNLOCK" << std::endl;
}

bool				TradeManager::getMob(Trame *trame)
{
  bool				ret = false;
  unsigned int			idTrade;
  unsigned int			idPlayer;
  //  AMob				*mob;
  unsigned int			idMob;

  std::cout << "TRADEMANAGER => GETMOB" << std::endl;  this->_mutex->lock();
  this->_mutex->lock();
  idTrade = (*trame)[CONTENT]["GETMOB"]["IDTRADE"].asUInt();
  idMob = (*trame)[CONTENT]["GETMOB"]["IDMOB"].asUInt();
  // mob = AMob::deserialization((*trame)((*trame)[CONTENT]));
  // if (mob)
  //   {
  for (auto it = _list->begin() ; it != _list->end() ; ++it)
    if (it->first && it->second && it->second->getId() == idTrade)
      {
	idPlayer = it->second->getIdPlayer((*trame)[HEADER]["IDCLIENT"].asUInt());
	ret = it->second->getMob(idPlayer, idMob);//mob->getId());
      }
  //   }
  // else
  //   ret = false;
  this->_mutex->unlock();
  return (ret);
}

bool				TradeManager::putMob(Trame *trame)
{
  bool				ret = false;
  unsigned int			idTrade;
  unsigned int			idPlayer;
  // AMob				*mob;
  unsigned int			idMob;

  std::cout << "TRADEMANAGER => PUTMOB" << std::endl;  this->_mutex->lock();
  this->_mutex->lock();
  idTrade = (*trame)[CONTENT]["PUTMOB"]["IDTRADE"].asUInt();
  idMob = (*trame)[CONTENT]["PUTMOB"]["IDMOB"].asUInt();
  // mob = Mob::deserialization((*trame)((*trame)[CONTENT]));
  // if (mob)
  // {
  for (auto it = _list->begin() ; it != _list->end() ; ++it)
    if (it->first && it->second && it->second->getId() == idTrade)
      {
	idPlayer = it->second->getIdPlayer((*trame)[HEADER]["IDCLIENT"].asUInt());
	ret = it->second->putMob(idPlayer, idMob);//mob->getId());
      }
  //   }
  // else
  //   ret = false;
  this->_mutex->unlock();
  return (ret);
}

bool				TradeManager::getItem(Trame *trame)
{
  bool				ret = false;
  unsigned int			idTrade;
  unsigned int			idPlayer;
  // AItem				*item;
  unsigned int			idItem;


  std::cout << "TRADEMANAGER => GETITEM" << std::endl;  this->_mutex->lock();
  idTrade = (*trame)[CONTENT]["GETITEM"]["IDTRADE"].asUInt();
  // item = AItem::deserialization((*trame)((*trame)[CONTENT]));
  // if (item)
  //   {
  idItem = (*trame)[CONTENT]["GETITEM"]["IDSTACK"].asUInt();
  for (auto it = _list->begin() ; it != _list->end() ; ++it)
    if (it->first && it->second && it->second->getId() == idTrade)
      {
	idPlayer = it->second->getIdPlayer((*trame)[HEADER]["IDCLIENT"].asUInt());
	ret = it->second->getItem(idPlayer, idItem);//item->getId());
      }
  //   }
  // else
  //   ret = false;
  this->_mutex->unlock();
  return (ret);
}

bool				TradeManager::putItem(Trame *trame)
{
  bool				ret = false;
  unsigned int			idTrade;
  unsigned int			idPlayer;
  // AItem				*item;
  unsigned int			idItem;

  std::cout << "TRADEMANAGER => PUTITEM" << std::endl;
  this->_mutex->lock();
  idTrade = (*trame)[CONTENT]["PUTITEM"]["IDTRADE"].asUInt();
  // item = AItem::deserialization((*trame)((*trame)[CONTENT]));
  // if (item)
  //   {
  idItem = (*trame)[CONTENT]["PUTITEM"]["IDSTACK"].asUInt();
  for (auto it = _list->begin() ; it != _list->end() ; ++it)
    if (it->first && it->second && it->second->getId() == idTrade)
      {
	idPlayer = it->second->getIdPlayer((*trame)[HEADER]["IDCLIENT"].asUInt());
	ret = it->second->putItem(idPlayer, idItem);//item->getId());
      }
  //   }
  // else
  //   ret = false;
  this->_mutex->unlock();
  return (ret);
}

bool				TradeManager::getMoney(Trame *trame)
{
  bool				ret = false;
  unsigned int			idTrade;
  unsigned int			money;
  unsigned int			idPlayer;

  std::cout << "TRADEMANAGER => GETMONEY" << std::endl;
  this->_mutex->lock();
  idTrade = (*trame)[CONTENT]["GETMONEY"]["IDTRADE"].asUInt();
  money = (*trame)[CONTENT]["GETMONEY"]["MONEY"].asUInt();
  for (auto it = _list->begin() ; it != _list->end() ; ++it)
    if (it->first && it->second && it->second->getId() == idTrade)
      {
	idPlayer = it->second->getIdPlayer((*trame)[HEADER]["IDCLIENT"].asUInt());
	ret = it->second->getMoney(idPlayer, money);
      }
  this->_mutex->unlock();
  return (ret);
}

bool				TradeManager::putMoney(Trame *trame)
{
  bool				ret = false;
  unsigned int			idTrade;
  unsigned int			money;
  unsigned int			idPlayer;

  std::cout << "TRADEMANAGER => PUTMONEY" << std::endl;
  this->_mutex->lock();
  idTrade = (*trame)[CONTENT]["PUTMONEY"]["IDTRADE"].asUInt();
  money = (*trame)[CONTENT]["PUTMONEY"]["MONEY"].asUInt();
  for (auto it = _list->begin() ; it != _list->end() ; ++it)
    if (it->first && it->second && it->second->getId() == idTrade)
      {
	idPlayer = it->second->getIdPlayer((*trame)[HEADER]["IDCLIENT"].asUInt());
	ret = it->second->putMoney(idPlayer, money);
      }
  this->_mutex->unlock();
  return (ret);
}

bool				TradeManager::accept(Trame *trame)
{
  bool				ret = false;
  unsigned int			idTrade;
  unsigned int			idPlayer;

  std::cout << "TRADEMANAGER => ACCEPT" << std::endl;
  this->_mutex->lock();
  idTrade = (*trame)[CONTENT]["ACCEPT"].asUInt();
  for (auto it = _list->begin() ; it != _list->end() ; ++it)
    if (it->first && it->second && it->second->getId() == idTrade)
      {
	idPlayer = it->second->getIdPlayer((*trame)[HEADER]["IDCLIENT"].asUInt());
	ret = it->second->accept(idPlayer);
      }
  this->_mutex->unlock();
  return (ret);
}

bool				TradeManager::refuse(Trame *trame)
{
  bool				ret = false;
  unsigned int			idTrade;

  std::cout << "TRADEMANAGER => REFUSE" << std::endl;
  this->_mutex->lock();
  idTrade = (*trame)[CONTENT]["REFUSE"].asUInt();
  for (auto it = _list->begin() ; it != _list->end() ; ++it)
    if (it->first && it->second && it->second->getId() == idTrade)
      ret = it->second->refuse();
  this->_mutex->unlock();
  return (ret);
}

bool				TradeManager::disconnectPlayer(unsigned int const idPlayer)
{
  bool				ret = false;

  std::cout << "TRADEMANAGER => DISCONNECT" << std::endl;
  this->_mutex->lock();
  for (auto it = _list->begin() ; it != _list->end() && !ret; ++it)
    if (it->first && it->second)
      {
	ret = it->second->stopTrade(idPlayer);
	if (ret)
	  it->first = false;
      }
  this->_mutex->unlock();
  return (ret);
}
