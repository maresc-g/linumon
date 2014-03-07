//
// Battle.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Wed Mar  5 12:23:42 2014 guillaume marescaux
// Last update Fri Mar  7 11:44:31 2014 guillaume marescaux
//

#include			"Battle/Battle.hh"

Battle::Battle():
  _id(0), _turnTo(0), _mobs(new std::list<Mob *>), _enemy(NULL), _nbMobs(0)
{
}

Battle::~Battle()
{
  delete _enemy;
}

void				Battle::setInfos(MutexVar<Player *> *player, unsigned int id, Player *enemy, unsigned int nbMobs)
{
  std::list<Mob *>		mobs = (**player)->getDigitaliser().getBattleMobs();

  _mobs->clear();
  for (auto it = mobs.begin() ; it != mobs.end() ; it++)
    _mobs->push_back(*it);
  _id = id;
  _enemy = enemy;
  _nbMobs = nbMobs;
}

void				Battle::setTurnTo(unsigned int id)
{
  _turnTo = id;
}

void				Battle::pushSpell(SpellContainer *container)
{
  _spells->push_back(container);
}

SpellContainer			*Battle::getSpell(void)
{
  SpellContainer		*ret = _spells->front();

  _spells->remove(ret);
  return (ret);
}
