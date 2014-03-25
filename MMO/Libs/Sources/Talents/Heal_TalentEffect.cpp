//
// Heal_TalentEffect.cpp for Heal_TalentEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Mar 23 13:08:41 2014 alexis mestag
// Last update Tue Mar 25 23:27:09 2014 alexis mestag
//

#include				"Heal_TalentEffect.hh"

Heal_TalentEffect::Heal_TalentEffect() :
  TalentEffect(true)
{

}

Heal_TalentEffect::~Heal_TalentEffect()
{

}

bool					Heal_TalentEffect::apply(Player &player,
								 unsigned int const fromPts,
								 unsigned int const toPts)
{
  this->applyToAllMobs(player, fromPts, toPts);
  return (true);
}

bool					Heal_TalentEffect::apply(Mob &mob,
								 unsigned int const fromPts,
								 unsigned int const toPts)
{
  for (unsigned int i = fromPts ; i <= toPts ; ++i)
    mob.incStat("Heal", 5);
  return (true);
}
