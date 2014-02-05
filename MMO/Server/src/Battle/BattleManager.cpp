//
// BattleManager.cpp for Battle in /home/maitre_c/work/linumon/MMO/Server/include/Battle
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Wed Jan 29 13:29:21 2014 antoine maitre
// Last update Wed Feb  5 12:22:04 2014 antoine maitre
//

#include			"Battle/BattleManager.hh"
#include			"Server/Server.hh"

BattleManager::BattleManager()
  : _quit(false), _mutex(new Mutex)
{
  this->_mutex->init();
  this->_mutex->lock();
  std::function<bool (Trame *)> func;

  func = std::bind1st(std::mem_fun(& BattleManager::capture), this);
  Server::getInstance()->addFuncProtocol("CAPTURE", func);
  func = std::bind1st(std::mem_fun(& BattleManager::spell), this);
  Server::getInstance()->addFuncProtocol("SPELL", func);
  func = std::bind1st(std::mem_fun(& BattleManager::dswitch), this);
  Server::getInstance()->addFuncProtocol("SWITCH", func);
}

BattleManager::~BattleManager()
{

}

bool				BattleManager::spell(Trame *trame)
{
  (void) trame;
  return (true);
}

bool				BattleManager::capture(Trame *trame)
{
  if ((*trame)[CONTENT]["CAPTURE"].isMember("IDBATTLE") && (*trame)[CONTENT]["CAPTURE"].isMember("TARGET"))
    {
      // for (auto it = this->_battles->begin(); it != this->_battles->end(); it++)
      // 	{
      // 	  if ((*it)->getID() == (*trame)["CAPTURE"]["IDBATTLE"].asUInt())
      // 	    {
      // 	      (*it)->capture((*trame)["CAPTURE"]["TARGET"].asInt());
      // 	      return (true);
      // 	    }
      // 	}
      return (false);
    }
  return (false);
}

bool				BattleManager::dswitch(Trame *trame)
{
  if ((*trame)[CONTENT]["SWITCH"].isMember("IDBATTLE") && (*trame)[CONTENT]["SWITCH"].isMember("TARGET") && (*trame)[CONTENT]["SWITCH"].isMember("NEWMOB"))
    {
      // for (auto it = this->_battles->begin(); it != this->_battles->end(); it++)
      // 	{
      // 	  if ((*it)->getID() == (*trame)["SWITCH"]["IDBATTLE"].asUInt())
      // 	    {
      // 	      (*it)->dswitch((*trame)["SWITCH"]["TARGET"].asInt(), (*trame)["SWITCH"]["NEWMOB"].asInt());
      // 	      return (true);
      // 	    }
      // 	}
      return (false);
    }
  return (false);
}
