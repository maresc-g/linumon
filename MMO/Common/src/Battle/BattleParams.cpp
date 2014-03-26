//
// BattleParams.cpp for BattleParams in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Mar 25 14:34:19 2014 alexis mestag
// Last update Tue Mar 25 15:37:27 2014 alexis mestag
//

#include				<algorithm>
#include				<functional>
#include				"Battle/BattleParams.hh"

BattleParams::BattleParams(std::list<Mob *> *const mobs) :
  _mobs(mobs), _autoAssignedTargets(new std::map<Mob *, Mob *>)
{

}

BattleParams::~BattleParams()
{
  delete _autoAssignedTargets;
}

Mob				*BattleParams::getLauncherMob()
{
  return (_launcherMob);
}

void				BattleParams::setLauncherMob(Mob *const mob)
{
  _launcherMob = mob;
}

Mob				*BattleParams::getTargetMob()
{
  return (_targetMob);
}

void				BattleParams::setTargetMob(Mob *const mob)
{
  _targetMob = mob;
}

Spell				*BattleParams::getSpell()
{
  return (_spell);
}

void				BattleParams::setSpell(Spell *s)
{
  _spell = s;
}

void				BattleParams::setAutoAssignedTarget(Mob *launcher, Mob *target)
{
  (*_autoAssignedTargets)[launcher] = target;
}

Mob				*BattleParams::getAutoAssignedTargetFor(Mob *launcher)
{
  auto				it = _autoAssignedTargets->find(launcher);

  return (it != _autoAssignedTargets->end() ? it->second : NULL);
}

void				BattleParams::eraseAutoAssignedTargetFor(Mob *launcher)
{
  _autoAssignedTargets->erase(launcher);
}
