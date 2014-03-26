//
// DefSteel_TalentEffect.cpp for DefSteel_TalentEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Mar 23 14:27:51 2014 alexis mestag
// Last update Tue Mar 25 23:25:24 2014 alexis mestag
//

#include				"DefSteel_TalentEffect.hh"
#include				"Database/Repositories/TypeRepository.hpp"

DefSteel_TalentEffect::DefSteel_TalentEffect() :
  TalentEffect(true)
{

}

DefSteel_TalentEffect::~DefSteel_TalentEffect()
{

}

bool					DefSteel_TalentEffect::apply(Player &player,
								     unsigned int const fromPts,
								     unsigned int const toPts)
{
  this->applyToAllMobs(player, fromPts, toPts);
  return (true);
}

bool					DefSteel_TalentEffect::apply(Mob &mob,
								     unsigned int const fromPts,
								     unsigned int const toPts)
{
  static Type const			*type = Database::getRepository<Type>().getByName("Steel");

  if (*type == mob.getType()) {
    for (unsigned int i = fromPts ; i <= toPts ; ++i)
      mob.incBonus("Defense", 1);
  }
  return (true);
}
