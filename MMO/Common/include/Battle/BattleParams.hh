//
// BattleParams.hh for BattleParams in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Mar 25 14:24:23 2014 alexis mestag
// Last update Tue Mar 25 15:37:15 2014 alexis mestag
//

#ifndef				__BATTLEPARAMS_HH__
# define			__BATTLEPARAMS_HH__

# include			<map>
# include			"Entities/Mob.hh"

class				BattleParams
{
private:
  Mob				*_launcherMob;
  Mob				*_targetMob;
  Spell				*_spell;
  std::list<Mob *>		*_mobs;
  std::map<Mob *, Mob *>	*_autoAssignedTargets;

private:
  BattleParams();

public:
  BattleParams(std::list<Mob *> *const mobs);
  virtual ~BattleParams();

public:
  Mob				*getLauncherMob();
  void				setLauncherMob(Mob *const mob);
  Mob				*getTargetMob();
  void				setTargetMob(Mob *const mob);
  Spell				*getSpell();
  void				setSpell(Spell *);
  void				setAutoAssignedTarget(Mob *, Mob *);
  Mob				*getAutoAssignedTargetFor(Mob *launcher);
  void				eraseAutoAssignedTargetFor(Mob *launcher);
};

#endif
