//
// HealGrass_TalentEffect.cpp for HealGrass_TalentEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Mar 23 14:29:19 2014 alexis mestag
// Last update Tue Mar 25 23:26:54 2014 alexis mestag
//

#include				"HealGrass_TalentEffect.hh"
#include				"Database/Repositories/TypeRepository.hpp"

HealGrass_TalentEffect::HealGrass_TalentEffect() :
  TalentEffect(true)
{

}

HealGrass_TalentEffect::~HealGrass_TalentEffect()
{

}

bool					HealGrass_TalentEffect::apply(Player &player,
								      unsigned int const fromPts,
								      unsigned int const toPts)
{
  this->applyToAllMobs(player, fromPts, toPts);
  return (true);
}

bool					HealGrass_TalentEffect::apply(Mob &mob,
								      unsigned int const fromPts,
								      unsigned int const toPts)
{
  static Type const			*type = Database::getRepository<Type>().getByName("Grass");

  if (*type == mob.getType()) {
    for (unsigned int i = fromPts ; i <= toPts ; ++i)
      mob.incBonus("Heal", 1);
  }
  return (true);
}
