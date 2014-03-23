//
// Atk_TalentEffect.cpp for Atk_TalentEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Mar 23 13:06:12 2014 alexis mestag
// Last update Sun Mar 23 13:06:44 2014 alexis mestag
//

#include				"Atk_TalentEffect.hh"

Atk_TalentEffect::Atk_TalentEffect() :
  TalentEffect(true)
{

}

Atk_TalentEffect::~Atk_TalentEffect()
{

}

bool					Atk_TalentEffect::apply(Player &player __attribute__((unused)))
{
  return (true);
}

bool					Atk_TalentEffect::apply(Mob &mob __attribute__((unused)))
{
  mob.incStat("Attack", 5);
  return (true);
}
