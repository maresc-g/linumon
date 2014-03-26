//
// AtkFire_TalentEffect.cpp for AtkFire_TalentEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Mar 23 13:56:42 2014 alexis mestag
// Last update Tue Mar 25 23:12:09 2014 alexis mestag
//

#include				"AtkFire_TalentEffect.hh"
#include				"Database/Repositories/TypeRepository.hpp"

AtkFire_TalentEffect::AtkFire_TalentEffect() :
  TalentEffect(true)
{

}

AtkFire_TalentEffect::~AtkFire_TalentEffect()
{

}

bool					AtkFire_TalentEffect::apply(Player &player,
								    unsigned int const fromPts,
								    unsigned int const toPts)
{
  this->applyToAllMobs(player, fromPts, toPts);
  return (true);
}

bool					AtkFire_TalentEffect::apply(Mob &mob,
								    unsigned int const fromPts,
								    unsigned int const toPts)
{
  static Type const			*type = Database::getRepository<Type>().getByName("Fire");

  if (*type == mob.getType())
    for (unsigned int i = fromPts ; i <= toPts ; ++i)
      mob.incBonus("Attack", 1);
  return (true);
}
