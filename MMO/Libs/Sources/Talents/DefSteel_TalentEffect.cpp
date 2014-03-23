//
// DefSteel_TalentEffect.cpp for DefSteel_TalentEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Mar 23 14:27:51 2014 alexis mestag
// Last update Sun Mar 23 14:35:11 2014 alexis mestag
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

bool					DefSteel_TalentEffect::apply(Player &player __attribute__((unused)))
{
  return (true);
}

bool					DefSteel_TalentEffect::apply(Mob &mob __attribute__((unused)))
{
  static Type const			*type = Database::getRepository<Type>().getByName("Steel");

  if (*type == mob.getType())
    mob.incBonus("Defense", 1);
  return (true);
}
