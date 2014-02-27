//
// CelestiaEffect.cpp for CelestiaEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/EffectLibs
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Feb 26 13:59:15 2014 alexis mestag
// Last update Wed Feb 26 22:51:26 2014 alexis mestag
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
  player.setStat("Defense", 10, true);
  return (true);
}
