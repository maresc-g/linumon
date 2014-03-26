//
// HealWater_TalentEffect.cpp for HealWater_TalentEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Mar 23 14:30:01 2014 alexis mestag
// Last update Tue Mar 25 23:27:29 2014 alexis mestag
//

#include				"HealWater_TalentEffect.hh"
#include				"Database/Repositories/TypeRepository.hpp"

HealWater_TalentEffect::HealWater_TalentEffect() :
  TalentEffect(true)
{

}

HealWater_TalentEffect::~HealWater_TalentEffect()
{

}

bool					HealWater_TalentEffect::apply(Player &player,
								      unsigned int const fromPts,
								      unsigned int const toPts)
{
  this->applyToAllMobs(player, fromPts, toPts);
  return (true);
}

bool					HealWater_TalentEffect::apply(Mob &mob,
								      unsigned int const fromPts,
								      unsigned int const toPts)
{
  static Type const			*type = Database::getRepository<Type>().getByName("Water");

  if (*type == mob.getType()) {
    for (unsigned int i = fromPts ; i <= toPts ; ++i)
      mob.incBonus("Heal", 1);
  }
  return (true);
}
