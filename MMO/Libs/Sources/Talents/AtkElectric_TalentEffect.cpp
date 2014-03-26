//
// AtkElectric_TalentEffect.cpp for AtkElectric_TalentEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Mar 23 14:26:11 2014 alexis mestag
// Last update Tue Mar 25 23:32:31 2014 alexis mestag
//

#include				"AtkElectric_TalentEffect.hh"
#include				"Database/Repositories/TypeRepository.hpp"

AtkElectric_TalentEffect::AtkElectric_TalentEffect() :
  TalentEffect(true)
{

}

AtkElectric_TalentEffect::~AtkElectric_TalentEffect()
{

}

bool					AtkElectric_TalentEffect::apply(Player &player,
									unsigned int const fromPts,
									unsigned int const toPts)
{
  this->applyToAllMobs(player, fromPts, toPts);
  return (true);
}

bool					AtkElectric_TalentEffect::apply(Mob &mob,
									unsigned int const fromPts,
									unsigned int const toPts)
{
  static Type const			*type = Database::getRepository<Type>().getByName("Electric");

  if (*type == mob.getType()) {
    for (unsigned int i = fromPts ; i <= toPts ; ++i)
      mob.incBonus("Attack", 1);
  }
  return (true);
}
