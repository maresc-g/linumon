//
// AtkElectric_TalentEffect.cpp for AtkElectric_TalentEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Mar 23 14:26:11 2014 alexis mestag
// Last update Sun Mar 23 14:35:01 2014 alexis mestag
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

bool					AtkElectric_TalentEffect::apply(Player &player __attribute__((unused)))
{
  return (true);
}

bool					AtkElectric_TalentEffect::apply(Mob &mob __attribute__((unused)))
{
  static Type const			*type = Database::getRepository<Type>().getByName("Electric");

  if (*type == mob.getType())
    mob.incBonus("Attack", 1);
  return (true);
}
