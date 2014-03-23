//
// BattleMob_TalentEffect.cpp for BattleMob_TalentEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Mar 23 17:40:45 2014 alexis mestag
// Last update Sun Mar 23 17:41:05 2014 alexis mestag
//

#include				"BattleMob_TalentEffect.hh"

BattleMob_TalentEffect::BattleMob_TalentEffect() :
  TalentEffect(false)
{

}

BattleMob_TalentEffect::~BattleMob_TalentEffect()
{

}

bool				BattleMob_TalentEffect::apply(Player &player)
{
  player.incStat("Limit mob", 1);
  return (true);
}

bool				BattleMob_TalentEffect::apply(Mob &mob __attribute__((unused)))
{
  return (true);
}
