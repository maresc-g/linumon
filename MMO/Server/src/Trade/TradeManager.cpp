//
// TradeManager.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Wed Feb 12 20:20:01 2014 laurent ansel
// Last update Wed Feb 12 20:34:56 2014 laurent ansel
//

#include			<functional>
#include			"Trade/TradeManager.hh"
#include			"Server/Server.hh"

TradeManager::TradeManager():
  _list(new std::list<Trade *>)
{
  std::function<bool (Trame *)> func;

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
}

TradeManager::~TradeManager()
{
  for (auto it = _list->begin() ; it != _list->end() ; ++it)
    delete *it;
  delete _list;
}

void				TradeManager::newTrade(unsigned int const, unsigned int const)
{

}

bool				TradeManager::getItem(Trame *)
{

  return (false);
}

bool				TradeManager::putItem(Trame *)
{

  return (false);
}

bool				TradeManager::getMoney(Trame *)
{

  return (false);
}

bool				TradeManager::putMoney(Trame *)
{

  return (false);
}

bool				TradeManager::accept(Trame *)
{

  return (false);
}

bool				TradeManager::refuse(Trame *)
{

  return (false);
}
