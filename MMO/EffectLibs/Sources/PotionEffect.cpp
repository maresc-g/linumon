//
// PotionEffect.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Wed Mar  5 16:18:03 2014 laurent ansel
// Last update Tue Mar 11 14:58:17 2014 alexis mestag
//

#include				"PotionEffect.hh"

PotionEffect::PotionEffect() :
  MobEffect()
{

}

PotionEffect::~PotionEffect()
{

}

bool					PotionEffect::apply(Mob &mob)
{
  mob.incCurrentStat("HP", 20);
  return (true);
}
