//
// CelestiaEffect.cpp for CelestiaEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/EffectLibs
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Feb 26 13:59:15 2014 alexis mestag
// Last update Sun Mar 23 18:59:37 2014 alexis mestag
//

#include				<algorithm>
#include				<functional>
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
  std::function<void(Mob *)>			f = [](Mob *m) -> void {
    m->incStat("Defense", 10);
  };

  std::for_each(player.getDigitaliser().begin(), player.getDigitaliser().end(), f);
  std::for_each(player.getDigitaliser().getBattleMobs().begin(),
		player.getDigitaliser().getBattleMobs().end(), f);
  return (true);
}
