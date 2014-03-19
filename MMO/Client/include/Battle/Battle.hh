//
// Battle.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Wed Mar  5 12:22:49 2014 guillaume marescaux
// Last update Wed Mar 19 11:41:17 2014 guillaume marescaux
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
  std::list<Mob *>		*_mobs;
  Player			*_enemy;
  unsigned int			_maxMobs;
  std::list<SpellContainer *>	*_spells;
  std::list<unsigned int>	*_turnTo;
  MutexVar<bool>		*_switch;
  MutexVar<Player *>		*_player;
  bool				_win;

public:

  Battle();
  virtual ~Battle();

public:

  void				setInfos(MutexVar<Player *> *player, unsigned int id, Player *enemy, unsigned int maxMobs = 3);
  void				pushTurnTo(unsigned int id);
  void				pushSpell(SpellContainer *container);
  SpellContainer		*getSpell(void);
  unsigned int			getId(void) const;
  unsigned int			getTurnTo(void) const;
  std::list<Mob *> const	&getMobs(void) const;
  Player const			&getEnemy(void) const;
  unsigned int			getMaxMobs(void) const;
  Mob				*getMobById(unsigned int id);
  void				switchPlayerMobs(unsigned int target, unsigned int newMob);
  void				switchEnemyMobs(unsigned int target, unsigned int newMob);
  MutexVar<bool>		*getSwitch(void) const;
  bool				getWin(void) const;
  void				setWin(bool);
  void				leaveBattle(void);
};

#endif
