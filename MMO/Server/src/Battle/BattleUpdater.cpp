//
// BattleUpdater.cpp for Battler in /home/maitre_c/work/linumon/MMO/Server/include/Battle
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Wed Jan 29 13:30:14 2014 antoine maitre
// Last update Thu Jan 30 14:20:05 2014 antoine maitre
//

#include			"Battle/BattleUpdater.hh"
#include			"Server/Server.hh"

BattleUpdater::BattleUpdater()
  : _msg(new std::list<std::pair<bool, Trame *> >)
{
  Trame				*trame = NULL;

  for (int i = 0 ; i < DEFAULT_STORAGE_BATTLE ; ++i)
    _msg->push_back(std::make_pair(false, trame));
  std::function<bool (Trame *)> func2;
  std::function<bool (Trame *)> func3;
  std::function<bool (Trame *)> func4;
  std::function<bool (Trame *)> func5;
  std::function<bool (Trame *)> func6;
  std::function<bool (Trame *)> func7;
  std::function<bool (Trame *)> func8;

  // func2 = std::bind1st(std::mem_fun(& BattleUpdater::spell), this);
  // func3 = std::bind1st(std::mem_fun(& BattleUpdater::spellEffect), this);
  // func4 = std::bind1st(std::mem_fun(& BattleUpdater::capture), this);
  // func5 = std::bind1st(std::mem_fun(& BattleUpdater::captureEffect), this);
  // func6 = std::bind1st(std::mem_fun(& BattleUpdater::datSwitch), this);
  // func7 = std::bind1st(std::mem_fun(& BattleUpdater::deadMob), this);
  // func8 = std::bind1st(std::mem_fun(& BattleUpdater::endBattle), this);
  // Server::getInstance()->addFuncProtocol("SPELL", func2);
  // Server::getInstance()->addFuncProtocol("SPELLEFFECT", func3);
  // Server::getInstance()->addFuncProtocol("CAPTURE", func4);
  // Server::getInstance()->addFuncProtocol("CAPTUREEFFECT", func5);
  // Server::getInstance()->addFuncProtocol("SWITCH", func6);
  // Server::getInstance()->addFuncProtocol("DEADMOB", func7);
  // Server::getInstance()->addFuncProtocol("ENDBATTLE", func8);
}

BattleUpdater::~BattleUpdater()
{

}

bool				BattleUpdater::launchBattle(Player *player1, Player *player2)
{
  unsigned int			id = 0;

  for (auto it = this->_battles->begin(); it != this->_battles->end(); it++)
    {
      if ((*it)->getID() != id)
	{
	  // if (player2->getType() == IA || player1->getType() == IA)
	    new Battle(id, Battle::PVE, 1, player1, player2);
	  // else
	  //   new Battle(id, Battle::PVP, 1, player1, player2);
	}
    }
  return (true);
}

bool				BattleUpdater::spell(Trame *trame)
{
  (void) trame;
  if (trame->isMember("SPELL"))
    {
      if ((*trame)["SPELL"].isMember("idBattle") && (*trame)["SPELL"].isMember("spell") && (*trame)["SPELL"].isMember("target"))
	{
	  for (auto it = this->_battles->begin(); it != this->_battles->end(); it++)
	    if ((*it)->getID() == (*trame)["SPELL"]["idBattle"].asUInt())
	      {
		Trame trame_bis((*trame)["SPELL"]["spell"].asString());
		Spell *spell = Spell::deserialization(trame_bis);
		(void)spell;
	      }
	}
      return (true);
    }
    else
      return (false);
}

bool				BattleUpdater::spellEffect(Trame *trame)
{
  (void) trame;
  return (true);
}

bool				BattleUpdater::capture(Trame *trame)
{
  (void) trame;
  return (true);

}

bool				BattleUpdater::captureEffect(Trame *trame)
{
  (void) trame;
  return (true);

}

bool				BattleUpdater::datSwitch(Trame *trame)
{
  (void) trame;
  return (true);

}

bool				BattleUpdater::deadMob(Trame *trame)
{
  (void) trame;
  return (true);

}

bool				BattleUpdater::endBattle(Trame *trame)
{
  (void) trame;
  return (true);

}
