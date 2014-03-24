//
// HealGrass_TalentEffect.cpp for HealGrass_TalentEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Mar 23 14:29:19 2014 alexis mestag
// Last update Sun Mar 23 14:35:15 2014 alexis mestag
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

bool					HealGrass_TalentEffect::apply(Player &player __attribute__((unused)))
{
  return (true);
}

bool					HealGrass_TalentEffect::apply(Mob &mob __attribute__((unused)))
{
  static Type const			*type = Database::getRepository<Type>().getByName("Grass");

  if (*type == mob.getType())
    mob.incBonus("Heal", 1);
  return (true);
}
