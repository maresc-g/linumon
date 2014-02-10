//
// TalentManager.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Sat Feb  8 17:23:10 2014 laurent ansel
// Last update Sat Feb  8 17:48:18 2014 laurent ansel
//

#include			<functional>
#include			"GameProtocol/TalentManager.hh"
#include			"Server/Server.hh"

TalentManager::TalentManager()
{
  std::function<bool (Trame *)> func;

  func = std::bind1st(std::mem_fun(&TalentManager::talents), this);
  Server::getInstance()->addFuncProtocol("TALENTS", func);
}

TalentManager::~TalentManager()
{

}

bool				TalentManager::talents(Trame *)
{

  return (false);
}
