//
// Def_TalentEffect.cpp for Def_TalentEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Mar 23 13:07:27 2014 alexis mestag
// Last update Tue Mar 25 23:25:55 2014 alexis mestag
//

#include				"Def_TalentEffect.hh"

Def_TalentEffect::Def_TalentEffect() :
  TalentEffect(true)
{

}

Def_TalentEffect::~Def_TalentEffect()
{

}

bool					Def_TalentEffect::apply(Player &player,
								unsigned int const fromPts,
								unsigned int const toPts)
{
  this->applyToAllMobs(player, fromPts, toPts);
  return (true);
}

bool					Def_TalentEffect::apply(Mob &mob,
								unsigned int const fromPts,
								unsigned int const toPts)
{
  for (unsigned int i = fromPts ; i <= toPts ; ++i)
    mob.incStat("Defense", 5);
  return (true);
}
