//
// JobManager.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Sat Feb  8 17:26:56 2014 laurent ansel
// Last update Sat Feb  8 17:48:27 2014 laurent ansel
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

bool				JobManager::gather(Trame *)
{

  return (false);
}

bool				JobManager::craft(Trame *)
{

  return (false);
}
