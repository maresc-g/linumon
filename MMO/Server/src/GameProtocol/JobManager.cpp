//
// JobManager.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Sat Feb  8 17:26:56 2014 laurent ansel
// Last update Wed Feb 19 12:58:25 2014 laurent ansel
//

#include			<functional>
#include			"GameProtocol/JobManager.hh"
#include			"Server/Server.hh"

JobManager::JobManager()
{
  std::function<bool (Trame *)> func;

  func = std::bind1st(std::mem_fun(&JobManager::craft), this);
  Server::getInstance()->addFuncProtocol("CRAFT", func);

  func = std::bind1st(std::mem_fun(&JobManager::gather), this);
  Server::getInstance()->addFuncProtocol("GATHER", func);
}

JobManager::~JobManager()
{

}

bool				JobManager::gather(Trame *trame)
{
  bool				ret = false;

  return (ret);
}

bool				JobManager::craft(Trame *trame)
{
  bool				ret = false;

  return (ret);
}
