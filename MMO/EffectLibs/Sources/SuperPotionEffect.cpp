//
// SuperPotionEffect.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Wed Mar  5 16:18:45 2014 laurent ansel
// Last update Wed Mar  5 16:22:08 2014 laurent ansel
//

#include				"SuperPotionEffect.hh"

SuperPotionEffect::SuperPotionEffect() :
  MobEffect()
{

}

SuperPotionEffect::~SuperPotionEffect()
{

}

bool					SuperPotionEffect::apply(Mob &mob)
{
  mob.setTmpStat("HP", 40, true);
  return (true);
}
