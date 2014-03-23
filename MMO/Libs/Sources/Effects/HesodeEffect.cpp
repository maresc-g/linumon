//
// HesodeEffect.cpp for HesodeEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/EffectLibs
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Feb 26 13:55:45 2014 alexis mestag
// Last update Sun Mar 23 18:59:42 2014 alexis mestag
//

#include				<algorithm>
#include				<functional>
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
  std::function<void(Mob *)>			f = [](Mob *m) -> void {
    m->incStat("Attack", 10);
  };

  std::for_each(player.getDigitaliser().begin(), player.getDigitaliser().end(), f);
  std::for_each(player.getDigitaliser().getBattleMobs().begin(),
		player.getDigitaliser().getBattleMobs().end(), f);
  return (true);
}
