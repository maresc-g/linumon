//
// AI.cpp for AI in /home/maitre_c/work/linumon/MMO/Server
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Sun Mar  2 22:33:20 2014 antoine maitre
// Last update Thu Mar  6 16:51:56 2014 antoine maitre
//

#include			"AI/AI.hh"

AI::AI(std::string const &name, std::string const &factionName) :
  Player(name, factionName)//, _type(PlayerType::AI)
{
  Player::setType(PlayerType::AI);
}

AI::~AI()
{
  
}

void				AI::setAdv(Player *const player)
{
  this->_adv = player;
}

void				AI::addEnemy(std::list<Mob *> mob)
{
  this->_mobs = mob;
}

void				AI::remove(unsigned int const target)
{
  for (auto it = this->_mobs.begin(); it != this->_mobs.end(); it++)
    if ((*it)->getId() == target)
      this->_mobs.erase(it);
}

int				AI::getRandomMob()
{
  int i = rand() % this->_mobs.size();
  for (auto it = this->_mobs.begin(); it != this->_mobs.end() && i >= 0; it++)
    {
      if (i == 0 && (*it)->getTmpStat("HP") != 0)
	return ((*it)->getId());
      else if (i == 0 && (*it)->getTmpStat("HP") == 0)
	return (this->getRandomMob());
      i--;
    }
  return (-1);
}

std::tuple<unsigned int const, unsigned int const, Spell const *>			AI::action(unsigned int const mob)
{
  Spell const			*tmp;
  // int				target;

  for (auto it = this->getDigitaliser().begin(); it != this->getDigitaliser().end(); it++)
    if ((*it)->getId() == mob)
      {
	int i = rand() % (*it)->getModel().getSpells().size();
	for (auto itb = (*it)->getModel().getSpells().begin(); itb != (*it)->getModel().getSpells().end() && i >= 0; itb++)
	  {
	    if (i == 0)
	      tmp = (*itb);
	    i--;
	  }
      }
  std::tuple<unsigned int const, unsigned int const, Spell const *> ret(mob, this->getRandomMob(), tmp);
  return (ret);
}

