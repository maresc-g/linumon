//
// DefRock_TalentEffect.cpp for DefRock_TalentEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Mar 23 14:26:50 2014 alexis mestag
// Last update Tue Mar 25 23:24:40 2014 alexis mestag
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

bool					DefRock_TalentEffect::apply(Player &player,
								    unsigned int const fromPts,
								    unsigned int const toPts)
{
  this->applyToAllMobs(player, fromPts, toPts);
  return (true);
}

bool					DefRock_TalentEffect::apply(Mob &mob,
								    unsigned int const fromPts,
								    unsigned int const toPts)
{
  static Type const			*type = Database::getRepository<Type>().getByName("Rock");

  if (*type == mob.getType()) {
    for (unsigned int i = fromPts ; i <= toPts ; ++i)
      mob.incBonus("Defense", 1);
  }
  return (true);
}
