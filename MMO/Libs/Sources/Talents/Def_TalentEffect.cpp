//
// Def_TalentEffect.cpp for Def_TalentEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Mar 23 13:07:27 2014 alexis mestag
// Last update Sun Mar 23 13:09:02 2014 alexis mestag
//

#include				"Def_TalentEffect.hh"

Def_TalentEffect::Def_TalentEffect() :
  TalentEffect(true)
{

}

Def_TalentEffect::~Def_TalentEffect()
{

}

bool					Def_TalentEffect::apply(Player &player __attribute__((unused)))
{
  return (true);
}

bool					Def_TalentEffect::apply(Mob &mob __attribute__((unused)))
{
  mob.incStat("Defense", 5);
  return (true);
}
