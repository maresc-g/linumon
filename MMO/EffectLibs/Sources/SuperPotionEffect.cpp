//
// SuperPotionEffect.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Wed Mar  5 16:18:45 2014 laurent ansel
// Last update Mon Mar 10 16:00:50 2014 alexis mestag
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
  mob.setCurrentStat("HP", mob.getCurrentStat("HP") + 50);
  return (true);
}
