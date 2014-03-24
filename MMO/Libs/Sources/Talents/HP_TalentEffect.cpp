//
// HP_TalentEffect.cpp for HP_TalentEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Mar 23 12:57:49 2014 alexis mestag
// Last update Sun Mar 23 13:06:27 2014 alexis mestag
//

#include				"HP_TalentEffect.hh"

HP_TalentEffect::HP_TalentEffect() :
  TalentEffect(true)
{

}

HP_TalentEffect::~HP_TalentEffect()
{

}

bool					HP_TalentEffect::apply(Player &player __attribute__((unused)))
{
  return (true);
}

bool					HP_TalentEffect::apply(Mob &mob __attribute__((unused)))
{
  mob.incStat("HP", 5);
  return (true);
}
