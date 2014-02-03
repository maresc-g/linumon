//
// BattleUpdater.cpp for Battler in /home/maitre_c/work/linumon/MMO/Server/include/Battle
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Wed Jan 29 13:30:14 2014 antoine maitre
// Last update Mon Feb  3 16:02:53 2014 laurent ansel
//

#include			"Battle/BattleUpdater.hh"
#include			"Server/Server.hh"

BattleUpdater::BattleUpdater()
{
  // Trame				*trame = NULL;

  // for (int i = 0 ; i < DEFAULT_STORAGE_BATTLE ; ++i)
  //   _msg->push_back(std::make_pair(false, trame));
  std::function<bool (Trame *)> func;
  // std::function<bool (Trame *)> func3;
  // std::function<bool (Trame *)> func4;
  // std::function<bool (Trame *)> func5;
  // std::function<bool (Trame *)> func6;
  // std::function<bool (Trame *)> func7;
  // std::function<bool (Trame *)> func8;

  // func2 = std::bind1st(std::mem_fun(& BattleUpdater::spell), this);
  // func3 = std::bind1st(std::mem_fun(& BattleUpdater::spellEffect), this);
  func = std::bind1st(std::mem_fun(& BattleUpdater::capture), this);
  // func5 = std::bind1st(std::mem_fun(& BattleUpdater::captureEffect), this);
  // func6 = std::bind1st(std::mem_fun(& BattleUpdater::datSwitch), this);
  // func7 = std::bind1st(std::mem_fun(& BattleUpdater::deadMob), this);
  // func8 = std::bind1st(std::mem_fun(& BattleUpdater::endBattle), this);
  // Server::getInstance()->addFuncProtocol("SPELL", func2);
  // Server::getInstance()->addFuncProtocol("SPELLEFFECT", func3);
  Server::getInstance()->addFuncProtocol("CAPTURE", func);
  // Server::getInstance()->addFuncProtocol("CAPTUREEFFECT", func5);
  // Server::getInstance()->addFuncProtocol("SWITCH", func6);
  // Server::getInstance()->addFuncProtocol("DEADMOB", func7);
  // Server::getInstance()->addFuncProtocol("ENDBATTLE", func8);
}

BattleUpdater::~BattleUpdater()
{

}

bool				BattleUpdater::newBattle(Player *player1, Player *player2)
{
  unsigned int			id = 0;

  for (auto it = this->_battles->begin(); it != this->_battles->end(); it++)
    {
      if ((*it)->getID() != id)
	{
	  // if (player2->getType() == IA || player1->getType() == IA)
	  new Battle(id, Battle::PVE, 1, player1, player2);
	  Server::getInstance()->callProtocol<unsigned int const, unsigned int const, Player *>("LAUNCHBATTLE", true, player1->getId(), id, player2);
	  Server::getInstance()->callProtocol<unsigned int const, unsigned int const, Player *>("LAUNCHBATTLE", true, player2->getId(), id, player1);
	    // else
	    //   new Battle(id, Battle::PVP, 1, player1, player2);
	}
    }
  return (true);
}

bool				BattleUpdater::capture(Trame *trame)
{
  if ((*trame).isMember("CAPTURE"))
    {
      
      return (true);
    }
  return (false);
}
