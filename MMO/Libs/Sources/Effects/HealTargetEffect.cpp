//
// HealTargetEffect.cpp for HealTargetEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Mar 25 10:23:19 2014 alexis mestag
// Last update Tue Mar 25 14:48:11 2014 alexis mestag
//

#include				"HealTargetEffect.hh"

HealTargetEffect::HealTargetEffect() :
  SpellEffect(), _hp(1)
{

}

HealTargetEffect::~HealTargetEffect()
{

}

void				HealTargetEffect::initialize(Mob &caster __attribute__((unused)),
							     Spell &spell __attribute__((unused)),
							     Mob &target,
							     BattleParams &battle __attribute__((unused)))
{
  double				hp = target.getCurrentStat("HP") / 2.0;

  _hp = hp > 1 ? hp : 10;
}

bool					HealTargetEffect::apply(Mob &mob)
{
  mob.incCurrentStat("HP", _hp);
  return (true);
}
