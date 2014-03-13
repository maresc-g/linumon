//
// SuperPotionEffect.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Wed Mar  5 16:18:45 2014 laurent ansel
// Last update Tue Mar 11 14:58:28 2014 alexis mestag
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
  mob.incCurrentStat("HP", 50);
  return (true);
}
