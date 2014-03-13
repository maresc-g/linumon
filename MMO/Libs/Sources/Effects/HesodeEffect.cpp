//
// HesodeEffect.cpp for HesodeEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/EffectLibs
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Feb 26 13:55:45 2014 alexis mestag
// Last update Tue Mar 11 14:57:12 2014 alexis mestag
//

#include				"HesodeEffect.hh"

HesodeEffect::HesodeEffect() :
  PlayerEffect()
{

}

HesodeEffect::~HesodeEffect()
{

}

bool					HesodeEffect::apply(Player &player)
{
  player.incStat("Attack", 10);
  return (true);
}
