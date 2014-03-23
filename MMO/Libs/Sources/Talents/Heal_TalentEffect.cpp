//
// Heal_TalentEffect.cpp for Heal_TalentEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Mar 23 13:08:41 2014 alexis mestag
// Last update Sun Mar 23 13:56:55 2014 alexis mestag
//

#include				"Heal_TalentEffect.hh"

Heal_TalentEffect::Heal_TalentEffect() :
  TalentEffect(true)
{

}

Heal_TalentEffect::~Heal_TalentEffect()
{

}

bool					Heal_TalentEffect::apply(Player &player __attribute__((unused)))
{
  return (true);
}

bool					Heal_TalentEffect::apply(Mob &mob __attribute__((unused)))
{
  mob.incStat("Heal", 5);
  return (true);
}
