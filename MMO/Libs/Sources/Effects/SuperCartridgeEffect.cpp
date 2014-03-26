//
// SuperCartridgeEffect.cpp for SuperCartridgeEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Libs/Sources/Effects
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Mar 26 09:11:16 2014 alexis mestag
// Last update Wed Mar 26 09:12:51 2014 alexis mestag
//

#include				"SuperCartridgeEffect.hh"

SuperCartridgeEffect::SuperCartridgeEffect() :
  PlayerEffect()
{

}

SuperCartridgeEffect::~SuperCartridgeEffect()
{

}

bool					SuperCartridgeEffect::apply(Player &player)
{
  Cartridge				toAdd(1.5);

  for (unsigned int i = 0 ; i < 10 ; ++i)
    player.addCartridge(toAdd);
  return (true);
}
