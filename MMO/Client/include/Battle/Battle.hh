//
// Battle.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Wed Mar  5 12:22:49 2014 guillaume marescaux
// Last update Fri Mar  7 11:43:23 2014 guillaume marescaux
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
  int				_turnTo;
  std::list<Mob *>		*_mobs;
  Player			*_enemy;
  unsigned int			_nbMobs;
  std::list<SpellContainer *>	*_spells;

public:

  Battle();
  virtual ~Battle();

public:

  void				setInfos(MutexVar<Player *> *player, unsigned int id, Player *enemy, unsigned int nbMobs = 3);
  void				setTurnTo(unsigned int id);
  void				pushSpell(SpellContainer *container);
  SpellContainer		*getSpell(void);
};

#endif
