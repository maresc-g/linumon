//
// Trade.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Sat Feb  8 17:40:51 2014 laurent ansel
// Last update Mon Feb 10 16:32:14 2014 laurent ansel
//

#include			<functional>
#include			"GameProtocol/Trade.hh"
#include			"Server/Server.hh"

Trade::Trade()
{
  std::function<bool (Trame *)> func;

  func = std::bind1st(std::mem_fun(&Trade::putItem), this);
  Server::getInstance()->addFuncProtocol("PUTITEM", func);

  func = std::bind1st(std::mem_fun(&Trade::getItem), this);
  Server::getInstance()->addFuncProtocol("GETITEM", func);

  func = std::bind1st(std::mem_fun(&Trade::putMoney), this);
  Server::getInstance()->addFuncProtocol("PUTMONEY", func);

  func = std::bind1st(std::mem_fun(&Trade::getMoney), this);
  Server::getInstance()->addFuncProtocol("GETMONEY", func);

  func = std::bind1st(std::mem_fun(&Trade::refuse), this);
  Server::getInstance()->addFuncProtocol("REFUSE", func);

  func = std::bind1st(std::mem_fun(&Trade::accept), this);
  Server::getInstance()->addFuncProtocol("ACCEPT", func);
}

Trade::~Trade()
{

}

bool				Trade::getItem(Trame *)
{

  return (false);
}

bool				Trade::putItem(Trame *)
{

  return (false);
}

bool				Trade::getMoney(Trame *)
{

  return (false);
}

bool				Trade::putMoney(Trame *)
{

  return (false);
}

bool				Trade::accept(Trame *)
{

  return (false);
}

bool				Trade::refuse(Trame *)
{

  return (false);
}
