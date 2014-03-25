//
// HP_TalentEffect.cpp for HP_TalentEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Mar 23 12:57:49 2014 alexis mestag
// Last update Tue Mar 25 23:28:04 2014 alexis mestag
//

#include				"HP_TalentEffect.hh"

HP_TalentEffect::HP_TalentEffect() :
  TalentEffect(true)
{

}

HP_TalentEffect::~HP_TalentEffect()
{

}

bool					HP_TalentEffect::apply(Player &player,
							       unsigned int const fromPts,
							       unsigned int const toPts)
{
  this->applyToAllMobs(player, fromPts, toPts);
  return (true);
}

bool					HP_TalentEffect::apply(Mob &mob,
							       unsigned int const fromPts,
							       unsigned int const toPts)
{
  for (unsigned int i = fromPts ; i <= toPts ; ++i)
    mob.incStat("HP", 5);
  return (true);
}
