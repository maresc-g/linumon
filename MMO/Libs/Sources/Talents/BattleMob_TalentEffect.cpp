//
// BattleMob_TalentEffect.cpp for BattleMob_TalentEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Mar 23 17:40:45 2014 alexis mestag
// Last update Tue Mar 25 23:22:47 2014 alexis mestag
//

#include				"BattleMob_TalentEffect.hh"

BattleMob_TalentEffect::BattleMob_TalentEffect() :
  TalentEffect(false)
{

}

BattleMob_TalentEffect::~BattleMob_TalentEffect()
{

}

bool				BattleMob_TalentEffect::apply(Player &player,
							      unsigned int const fromPts,
							      unsigned int const toPts)
{
  for (unsigned int i = fromPts ; i <= toPts ; ++i)
    player.incStat("Limit mob", 1);
  return (true);
}

bool				BattleMob_TalentEffect::apply(Mob &mob __attribute__((unused)),
							      unsigned int const fromPts __attribute__((unused)), unsigned int const toPts __attribute__((unused)))
{
  return (true);
}
