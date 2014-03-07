//
// Battle.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Wed Mar  5 12:23:42 2014 guillaume marescaux
// Last update Fri Mar  7 13:17:30 2014 guillaume marescaux
//

#include			"Battle/Battle.hh"

Battle::Battle():
  _id(0), _turnTo(0), _mobs(new std::list<Mob *>), _enemy(NULL), _maxMobs(0)
{
}

Battle::~Battle()
{
  delete _enemy;
}

void				Battle::setInfos(MutexVar<Player *> *player, unsigned int id, Player *enemy, unsigned int maxMobs)
{
  std::list<Mob *>		mobs = (**player)->getDigitaliser().getBattleMobs();

  _mobs->clear();
  for (auto it = mobs.begin() ; it != mobs.end() ; it++)
    _mobs->push_back(*it);
  _id = id;
  _enemy = enemy;
  _maxMobs = maxMobs;
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

unsigned int			Battle::getId() const { return (_id); }
unsigned int			Battle::getTurnTo() const { return (_turnTo); }
std::list<Mob *> const		&Battle::getMobs() const { return (*_mobs); }
Player const 			&Battle::getEnemy() const { return (*_enemy); }
unsigned int			Battle::getMaxMobs() const { return (_maxMobs); }
