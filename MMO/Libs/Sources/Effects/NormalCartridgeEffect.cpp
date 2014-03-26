//
// NormalCartridgeEffect.cpp for NormalCartridgeEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Libs/Sources/Effects
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Mar 26 09:09:25 2014 alexis mestag
// Last update Wed Mar 26 09:11:39 2014 alexis mestag
//

#include				"NormalCartridgeEffect.hh"

NormalCartridgeEffect::NormalCartridgeEffect() :
  PlayerEffect()
{

}

NormalCartridgeEffect::~NormalCartridgeEffect()
{

}

bool					NormalCartridgeEffect::apply(Player &player)
{
  Cartridge				toAdd(1);

  for (unsigned int i = 0 ; i < 10 ; ++i)
    player.addCartridge(toAdd);
  return (true);
}
