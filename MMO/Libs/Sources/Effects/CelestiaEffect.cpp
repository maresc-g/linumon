//
// CelestiaEffect.cpp for CelestiaEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/EffectLibs
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Feb 26 13:59:15 2014 alexis mestag
// Last update Tue Mar 11 14:57:03 2014 alexis mestag
//

#include				"CelestiaEffect.hh"

CelestiaEffect::CelestiaEffect() :
  PlayerEffect()
{

}

CelestiaEffect::~CelestiaEffect()
{

}

bool					CelestiaEffect::apply(Player &player)
{
  player.incStat("Defense", 10);
  return (true);
}
