//
// Atk_TalentEffect.cpp for Atk_TalentEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Mar 23 13:06:12 2014 alexis mestag
// Last update Tue Mar 25 23:18:45 2014 alexis mestag
//

#include				"Atk_TalentEffect.hh"

Atk_TalentEffect::Atk_TalentEffect() :
  TalentEffect(true)
{

}

Atk_TalentEffect::~Atk_TalentEffect()
{

}

bool					Atk_TalentEffect::apply(Player &player,
								unsigned int const fromPts,
								unsigned int const toPts)
{
  this->applyToAllMobs(player, fromPts, toPts);
  return (true);
}

bool					Atk_TalentEffect::apply(Mob &mob,
								unsigned int const fromPts,
								unsigned int const toPts)
{
  for (unsigned int i = fromPts ; i <= toPts ; ++i)
    mob.incStat("Attack", 5);
  return (true);
}
