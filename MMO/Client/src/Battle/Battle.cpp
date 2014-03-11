//
// Battle.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Wed Mar  5 12:23:42 2014 guillaume marescaux
// Last update Wed Mar 12 00:14:40 2014 laurent ansel
//

#include			<algorithm>
#include			"Battle/Battle.hh"

Battle::Battle():
  _id(0), _mobs(new std::list<Mob *>), _enemy(NULL), _maxMobs(0), _spells(new std::list<SpellContainer *>),
  _turnTo(new std::list<unsigned int>)
{
}

Battle::~Battle()
{
  delete _enemy;
}

void				Battle::setInfos(MutexVar<Player *> *player, unsigned int id, Player *enemy, unsigned int maxMobs)
{
  std::list<Mob *> const	mobs = (**player)->getDigitaliser().getBattleMobs();
  unsigned int			i = 0;

  _turnTo->clear();
  _mobs->clear();
  for (auto it = mobs.begin() ; it != mobs.end() && i < 3; it++)
    {
      (*it)->enterBattle();
      _mobs->push_back(*it);
      i++;
    }
  _id = id;
  _enemy = enemy;
  std::list<Mob *> const	mobs2 = enemy->getDigitaliser().getBattleMobs();
  i = 0;
  for (auto it = mobs2.begin() ; it != mobs2.end() && i < 3; it++)
    {
      std::cout << (*it)->getStat("HP") << std::endl;
      (*it)->enterBattle();
      i++;
    }
  _maxMobs = maxMobs;
}

void				Battle::pushTurnTo(unsigned int id)
{
  _turnTo->push_back(id);
}

void				Battle::pushSpell(SpellContainer *container)
{
  _spells->push_back(container);
  std::cout << "Adding spell : " << container->getSpell().getName() << std::endl;
}

SpellContainer			*Battle::getSpell(void)
{
  SpellContainer		*ret = NULL;

  if (!this->_spells->empty())
    {
      ret = _spells->front();
      if (ret)
	std::cout << "NAME OF SPELL : [" << ret->getSpell().getName() << "]" << std::endl;
      _spells->remove(ret);
    }
  return (ret);
}

unsigned int			Battle::getId() const { return (_id); }
unsigned int			Battle::getTurnTo() const
{
  if (_turnTo->size() == 0)
    return (-1);
  unsigned int			id = _turnTo->front();
  _turnTo->pop_front();
  return (id);
}

std::list<Mob *> const		&Battle::getMobs() const { return (*_mobs); }
Player const 			&Battle::getEnemy() const { return (*_enemy); }
unsigned int			Battle::getMaxMobs() const { return (_maxMobs); }

Mob				*Battle::getMobById(unsigned int id)
{
  std::list<Mob *> const	mobs = _enemy->getDigitaliser().getBattleMobs();

  auto it = find_if(_mobs->begin(), _mobs->end(), [&](Mob const *mob){
      if (mob->getId() == id)
  	return true;
      return false;
    });
  if (it != _mobs->end())
    return (*it);
  auto it2 = find_if(mobs.begin(), mobs.end(), [&](Mob const *mob){
      if (mob->getId() == id)
	return true;
      return false;
    });
  if (it2 != mobs.end())
    return *it2;
  return NULL;
}
