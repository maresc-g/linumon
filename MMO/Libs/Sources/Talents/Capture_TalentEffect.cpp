//
// Capture_TalentEffect.cpp for Capture_TalentEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Mar 23 17:33:46 2014 alexis mestag
// Last update Sun Mar 23 17:40:02 2014 alexis mestag
//

#include				"Capture_TalentEffect.hh"

Capture_TalentEffect::Capture_TalentEffect() :
  TalentEffect(false)
{

}

Capture_TalentEffect::~Capture_TalentEffect()
{

}

bool				Capture_TalentEffect::apply(Player &player)
{
  player.incStat("Capture", 1);
  return (true);
}

bool				Capture_TalentEffect::apply(Mob &mob __attribute__((unused)))
{
  return (true);
}
