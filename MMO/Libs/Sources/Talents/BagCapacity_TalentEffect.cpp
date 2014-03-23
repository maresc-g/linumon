//
// BagCapacity_TalentEffect.cpp for BagCapacity_TalentEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Mar 23 17:40:14 2014 alexis mestag
// Last update Sun Mar 23 17:40:31 2014 alexis mestag
//

#include				"BagCapacity_TalentEffect.hh"

BagCapacity_TalentEffect::BagCapacity_TalentEffect() :
  TalentEffect(false)
{

}

BagCapacity_TalentEffect::~BagCapacity_TalentEffect()
{

}

bool				BagCapacity_TalentEffect::apply(Player &player)
{
  player.incStat("Bag capacity", 5);
  return (true);
}

bool				BagCapacity_TalentEffect::apply(Mob &mob __attribute__((unused)))
{
  return (true);
}
