//
// BattleUpdater.cpp for Battler in /home/maitre_c/work/linumon/MMO/Server/include/Battle
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Wed Jan 29 13:30:14 2014 antoine maitre
// Last update Fri Feb  7 13:12:30 2014 antoine maitre
//

#include			"Battle/BattleUpdater.hh"
#include			"Server/Server.hh"

BattleUpdater::BattleUpdater()
  : _quit(false), _mutex(new Mutex), _funcs(new std::map<std::string, funcBattle>)
{
  std::string str = "CAPTURE";
  this->_mutex->init();
  // (*this->_funcs)[str] = std::bind1st(std::mem_fun(& BattleUpdater::capture), this);
  // str = "SWITCH"
  // (*this->_funcs)[str] = std::bind1st(std::mem_fun(& BattleUpdater::dswitch), this);
  // str = "SPELL"
  // (*this->_funcs)[str] = std::bind1st(std::mem_fun(& BattleUpdater::spell), this);
  //  this->create(&launch, this);
  // this->start();
  
}

BattleUpdater::~BattleUpdater()
{
  delete _mutex;
}

void				BattleUpdater::lock()
{
  this->_mutex->lock();
}

void				BattleUpdater::unlock()
{
  this->_mutex->unlock();
}

void				BattleUpdater::addTrame(Trame trame)
{
  this->_trames.push_back(&trame);
}

void				BattleUpdater::launch()
{
  while (!_quit)
    {
      this->_mutex->lock();
      if (!this->_trames.empty())
	{
	}
      this->_mutex->unlock();
      usleep(1000);
    }
}

bool				BattleUpdater::newBattle(Player *player1, Player *player2)
{
  unsigned int			id = 0;

  for (auto it = this->_battles->begin(); it != this->_battles->end(); it++)
    {
      if ((*it)->getID() != id)
	{
	  // if (player2->getType() == IA || player1->getType() == IA)
	  //   {
	  new Battle(id, Battle::PVE, 1, player1, player2);
	  Server::getInstance()->callProtocol<unsigned int const, Player *>("LAUNCHBATTLE", player2->getId(), id, player1);
	  Server::getInstance()->callProtocol<unsigned int const, Player *>("LAUNCHBATTLE", player1->getId(), id, player2);
	    // }
	  // else
	  //   {
	  //     new Battle(id, Battle::PVP, 1, player1, player2);
	  //     Server::getInstance()->callProtocol<unsigned int const, Player *>("LAUNCHBATTLE", player1->getId(), id, player2);
	  //   }
	}
    }
  return (true);
}


bool				BattleUpdater::spell(Trame *trame)
{
  (void) trame;
  return (true);
}

bool				BattleUpdater::capture(Trame *trame)
{
  if ((*trame)["CAPTURE"].isMember("IDBATTLE") && (*trame)["CAPTURE"].isMember("TARGET"))
    {
      for (auto it = this->_battles->begin(); it != this->_battles->end(); it++)
      	{
      	  if ((*it)->getID() == (*trame)["CAPTURE"]["IDBATTLE"].asUInt())
      	    {
      	      (*it)->capture((*trame)["CAPTURE"]["TARGET"].asInt());
      	      return (true);
      	    }
      	}
      return (false);
    }
  return (false);
}

bool				BattleUpdater::dswitch(Trame *trame)
{
  for (auto it = this->_battles->begin(); it != this->_battles->end(); it++)
    {
      if ((*it)->getID() == (*trame)["SWITCH"]["IDBATTLE"].asUInt())
	{
	  (*it)->dswitch((*trame)["SWITCH"]["TARGET"].asInt(), (*trame)["SWITCH"]["NEWMOB"].asInt());
	  return (true);
	}
    }
  return (false);
}

