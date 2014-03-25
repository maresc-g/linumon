//
// DigitaliserManager.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Mar 13 18:32:05 2014 laurent ansel
// Last update Tue Mar 25 19:10:15 2014 laurent ansel
//

#include			<functional>
#include			"GameProtocol/DigitaliserManager.hh"
#include			"Server/Server.hh"

DigitaliserManager::DigitaliserManager()
{
  std::function<bool (Trame *)> func;

  func = std::bind1st(std::mem_fun(&DigitaliserManager::mobToBattleMob), this);
  Server::getInstance()->addFuncProtocol("MOBTOBATTLEMOB", func);

  func = std::bind1st(std::mem_fun(&DigitaliserManager::battleMobToMob), this);
  Server::getInstance()->addFuncProtocol("BATTLEMOBTOMOB", func);

  func = std::bind1st(std::mem_fun(&DigitaliserManager::switchMobs), this);
  Server::getInstance()->addFuncProtocol("SWITCHMOBS", func);
}

DigitaliserManager::~DigitaliserManager()
{

}

bool				DigitaliserManager::mobToBattleMob(Trame *trame)
{
  if ((*trame)[CONTENT].isMember("MOBTOBATTLEMOB"))
    {
      ClientManager::getInstance()->modifyDigitaliser((*trame)[HEADER]["IDCLIENT"].asInt(), (*trame)[CONTENT]["MOBTOBATTLEMOB"].asUInt(), 0, true);
      return (true);
    }
  return (false);
}

bool				DigitaliserManager::battleMobToMob(Trame *trame)
{
  if ((*trame)[CONTENT].isMember("BATTLEMOBTOMOB"))
    {
      ClientManager::getInstance()->modifyDigitaliser((*trame)[HEADER]["IDCLIENT"].asInt(), (*trame)[CONTENT]["BATTLEMOBTOMOB"].asUInt(), 0, false);
      return (true);
    }
  return (false);
}

bool				DigitaliserManager::switchMobs(Trame *trame)
{
  if ((*trame)[CONTENT].isMember("SWITCHMOBS"))
    {
      ClientManager::getInstance()->modifyDigitaliser((*trame)[HEADER]["IDCLIENT"].asInt(), (*trame)[CONTENT]["SWITCHMOBS"]["IDMOB1"].asUInt(), (*trame)[CONTENT]["SWITCHMOBS"]["IDMOB2"].asUInt(), false);
      return (true);
    }
  return (false);
}
