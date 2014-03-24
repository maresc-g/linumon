//
// AtkFire_TalentEffect.cpp for AtkFire_TalentEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Mar 23 13:56:42 2014 alexis mestag
// Last update Sun Mar 23 14:36:10 2014 alexis mestag
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

bool					AtkFire_TalentEffect::apply(Player &player __attribute__((unused)))
{
  return (true);
}

bool					AtkFire_TalentEffect::apply(Mob &mob __attribute__((unused)))
{
  static Type const			*type = Database::getRepository<Type>().getByName("Fire");

  if (*type == mob.getType())
    mob.incBonus("Attack", 1);
  return (true);
}
