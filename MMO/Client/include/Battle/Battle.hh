//
// Battle.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Wed Mar  5 12:22:49 2014 guillaume marescaux
// Last update Fri Mar  7 13:17:21 2014 guillaume marescaux
//

#ifndef 			__BATTLE_HH__
# define 			__BATTLE_HH__

#include			<list>
#include			"Entities/Player.hh"
#include			"Mutex/MutexVar.hpp"
#include			"Battle/SpellContainer.hh"

class				Battle
{
private:

  Battle(Battle const &);
  Battle			&operator=(Battle const &);

private:

  unsigned int			_id;
  unsigned int			_turnTo;
  std::list<Mob *>		*_mobs;
  Player			*_enemy;
  unsigned int			_maxMobs;
  std::list<SpellContainer *>	*_spells;

public:

  Battle();
  virtual ~Battle();

public:

  void				setInfos(MutexVar<Player *> *player, unsigned int id, Player *enemy, unsigned int maxMobs = 3);
  void				setTurnTo(unsigned int id);
  void				pushSpell(SpellContainer *container);
  SpellContainer		*getSpell(void);
  unsigned int			getId(void) const;
  unsigned int			getTurnTo(void) const;
  std::list<Mob *> const	&getMobs(void) const;
  Player const			&getEnemy(void) const;
  unsigned int			getMaxMobs(void) const;
};

#endif
