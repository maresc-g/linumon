//
// TradeManager.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Wed Feb 12 20:20:01 2014 laurent ansel
// Last update Wed Mar 12 18:00:05 2014 laurent ansel
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
  this->_mutex->lock();
  auto				it = _list->begin();

  for (; it != _list->end() && it->first ; ++it);
  if (!it->first && it->second)
    {
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
}

bool				TradeManager::getMob(Trame *trame)
{
  bool				ret = false;
  unsigned int			idTrade;
  unsigned int			idPlayer;
  //  AMob				*mob;
  unsigned int			idMob;

  this->_mutex->lock();
  idTrade = (*trame)[CONTENT]["TRADE"]["IDTRADE"].asUInt();
  idMob = (*trame)[CONTENT]["TRADE"]["IDMOB"].asUInt();
  // mob = AMob::deserialization((*trame)((*trame)[CONTENT]["TRADE"]));
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

  this->_mutex->lock();
  idTrade = (*trame)[CONTENT]["TRADE"]["IDTRADE"].asUInt();
  idMob = (*trame)[CONTENT]["TRADE"]["IDMOB"].asUInt();
  // mob = Mob::deserialization((*trame)((*trame)[CONTENT]["TRADE"]));
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

  this->_mutex->lock();
  idTrade = (*trame)[CONTENT]["TRADE"]["IDTRADE"].asUInt();
  // item = AItem::deserialization((*trame)((*trame)[CONTENT]["TRADE"]));
  // if (item)
  //   {
  idItem = (*trame)[CONTENT]["TRADE"]["IDSTACK"].asUInt();
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

  this->_mutex->lock();
  idTrade = (*trame)[CONTENT]["TRADE"]["IDTRADE"].asUInt();
  // item = AItem::deserialization((*trame)((*trame)[CONTENT]["TRADE"]));
  // if (item)
  //   {
  idItem = (*trame)[CONTENT]["TRADE"]["IDSTACK"].asUInt();
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

  this->_mutex->lock();
  idTrade = (*trame)[CONTENT]["TRADE"]["IDTRADE"].asUInt();
  money = (*trame)[CONTENT]["TRADE"]["MONEY"].asUInt();
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

  this->_mutex->lock();
  idTrade = (*trame)[CONTENT]["TRADE"]["IDTRADE"].asUInt();
  money = (*trame)[CONTENT]["TRADE"]["MONEY"].asUInt();
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

  this->_mutex->lock();
  idTrade = (*trame)[CONTENT]["TRADE"]["IDTRADE"].asUInt();
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

  this->_mutex->lock();
  idTrade = (*trame)[CONTENT]["TRADE"]["IDTRADE"].asUInt();
  for (auto it = _list->begin() ; it != _list->end() ; ++it)
    if (it->first && it->second && it->second->getId() == idTrade)
      ret = it->second->refuse();
  this->_mutex->unlock();
  return (ret);
}

bool				TradeManager::disconnectPlayer(unsigned int const idPlayer)
{
  bool				ret = false;

  this->_mutex->lock();
  for (auto it = _list->begin() ; it != _list->end() && !ret; ++it)
    if (it->first && it->second)
      ret = it->second->stopTrade(idPlayer);
  this->_mutex->unlock();
  return (ret);
}
