//
// PotionEffect.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Wed Mar  5 16:18:03 2014 laurent ansel
// Last update Wed Mar  5 16:21:54 2014 laurent ansel
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
  mob.setTmpStat("HP", 40, true);
  return (true);
}
