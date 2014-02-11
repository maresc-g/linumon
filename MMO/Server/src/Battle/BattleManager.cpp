//
// BattleManager.cpp for Battle in /home/maitre_c/work/linumon/MMO/Server/include/Battle
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Wed Jan 29 13:29:21 2014 antoine maitre
// Last update Tue Feb 11 12:24:46 2014 antoine maitre
//

#include			"Battle/BattleManager.hh"
#include			"Server/Server.hh"

BattleManager::BattleManager()
  : Singleton<BattleManager>(), _mutex(new Mutex)
{
  this->_mutex->init();
  std::function<bool (Trame *)> func;

  func = std::bind1st(std::mem_fun(&BattleManager::capture), this);
  Server::getInstance()->addFuncProtocol("CAPTURE", func);
  func = std::bind1st(std::mem_fun(&BattleManager::spell), this);
  Server::getInstance()->addFuncProtocol("SPELL", func);
  func = std::bind1st(std::mem_fun(&BattleManager::dswitch), this);
  Server::getInstance()->addFuncProtocol("SWITCH", func);
}

BattleManager::~BattleManager()
{
  this->deleteBattleUpdaters();
  this->_mutex->destroy();
  delete _mutex;
}

void				BattleManager::deleteBattleUpdaters()
{
  static std::function<bool(BattleUpdater *)>	battleUpdaterDeleter = [](BattleUpdater *bu) -> bool {
    delete bu;
    return (true);
  };
  this->_mutex->lock();
  _battleUpdaters.remove_if(battleUpdaterDeleter);
  this->_mutex->unlock();
}

bool				BattleManager::spell(Trame *trame)
{
  std::list<Battle *>		*tmp;

  if ((*trame)[CONTENT]["SPELL"].isMember("IDBATTLE") &&
      (*trame)[CONTENT]["SPELL"].isMember("SPELL") &&
      (*trame)[CONTENT]["SPELL"].isMember("TARGET"))
    {
      for (auto it = this->_battleUpdaters.begin(); it != this->_battleUpdaters.end(); it++)
	{
	  (*it)->lock();
	  tmp = (*it)->getBattles();
	  for (auto itb = tmp->begin(); itb != tmp->end(); it++)
	    if ((*itb)->getID() == (*trame)[CONTENT]["SPELL"]["IDBATTLE"].asUInt())
	      (*it)->addTrame((*trame)((*trame)[CONTENT]));
	  (*it)->unlock();
	}
      return (true);
    }
  return (false);
}

bool				BattleManager::capture(Trame *trame)
{
  std::list<Battle *>		*tmp;

  if ((*trame)[CONTENT]["CAPTURE"].isMember("IDBATTLE") &&
      (*trame)[CONTENT]["CAPTURE"].isMember("TARGET"))
    {
      for (auto it = this->_battleUpdaters.begin(); it != this->_battleUpdaters.end(); it++)
	{
	  (*it)->lock();
	  tmp = (*it)->getBattles();
	  for (auto itb = tmp->begin(); itb != tmp->end(); it++)
	    if ((*itb)->getID() == (*trame)[CONTENT]["CAPTURE"]["IDBATTLE"].asUInt())
	      (*it)->addTrame((*trame)((*trame)[CONTENT]));
	  (*it)->unlock();
	}
      return (true);
    }
  return (false);
}

bool				BattleManager::dswitch(Trame *trame)
{
  std::list<Battle *>		*tmp;

  if ((*trame)[CONTENT]["SWITCH"].isMember("IDBATTLE") &&
      (*trame)[CONTENT]["SWITCH"].isMember("TARGET") &&
      (*trame)[CONTENT]["SWITCH"].isMember("NEWMOB"))
    {
      for (auto it = this->_battleUpdaters.begin(); it != this->_battleUpdaters.end(); it++)
	{
	  (*it)->lock();
	  tmp = (*it)->getBattles();
	  for (auto itb = tmp->begin(); itb != tmp->end(); it++)
	    if ((*itb)->getID() == (*trame)[CONTENT]["SWITCH"]["IDBATTLE"].asUInt())
	      (*it)->addTrame((*trame)((*trame)[CONTENT]));
	  (*it)->unlock();
	}
      return (true);
    }
  return (false);
}

