//
// ContreEffect.cpp for ContreEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Mar 25 15:35:08 2014 alexis mestag
// Last update Tue Mar 25 16:02:35 2014 alexis mestag
//

#include			"ContreEffect.hh"

ContreEffect::ContreEffect() :
  SpellEffect()
{

}

ContreEffect::~ContreEffect()
{

}

void				ContreEffect::initialize(Mob &launcher __attribute__((unused)),
							 Spell &spell __attribute__((unused)),
							 Mob &target,
							 BattleParams &battle)
{
  battle.setAutoAssignedTarget(&target, &target);
}

bool				ContreEffect::apply(Mob &mob __attribute__((unused)))
{
  return (true);
}
