//
// HealWater_TalentEffect.cpp for HealWater_TalentEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Mar 23 14:30:01 2014 alexis mestag
// Last update Sun Mar 23 14:35:24 2014 alexis mestag
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

bool					HealWater_TalentEffect::apply(Player &player __attribute__((unused)))
{
  return (true);
}

bool					HealWater_TalentEffect::apply(Mob &mob __attribute__((unused)))
{
  static Type const			*type = Database::getRepository<Type>().getByName("Water");

  if (*type == mob.getType())
    mob.incBonus("Heal", 1);
  return (true);
}
