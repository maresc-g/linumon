//
// AttiranceEffect.cpp for AttiranceEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Mar 25 15:41:35 2014 alexis mestag
// Last update Tue Mar 25 16:02:54 2014 alexis mestag
//

#include			"AttiranceEffect.hh"

AttiranceEffect::AttiranceEffect() :
  SpellEffect()
{

}

AttiranceEffect::~AttiranceEffect()
{

}

void				AttiranceEffect::initialize(Mob &launcher,
							    Spell &spell __attribute__((unused)),
							    Mob &target,
							    BattleParams &battle)
{
  battle.setAutoAssignedTarget(&target, &launcher);
}

bool				AttiranceEffect::apply(Mob &mob __attribute__((unused)))
{
  return (true);
}
