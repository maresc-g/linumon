//
// DefRock_TalentEffect.cpp for DefRock_TalentEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Mar 23 14:26:50 2014 alexis mestag
// Last update Sun Mar 23 14:35:06 2014 alexis mestag
//

#include				"DefRock_TalentEffect.hh"
#include				"Database/Repositories/TypeRepository.hpp"

DefRock_TalentEffect::DefRock_TalentEffect() :
  TalentEffect(true)
{

}

DefRock_TalentEffect::~DefRock_TalentEffect()
{

}

bool					DefRock_TalentEffect::apply(Player &player __attribute__((unused)))
{
  return (true);
}

bool					DefRock_TalentEffect::apply(Mob &mob __attribute__((unused)))
{
  static Type const			*type = Database::getRepository<Type>().getByName("Rock");

  if (*type == mob.getType())
    mob.incBonus("Defense", 1);
  return (true);
}
