//
// Capture_TalentEffect.cpp for Capture_TalentEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Mar 23 17:33:46 2014 alexis mestag
// Last update Tue Mar 25 23:23:53 2014 alexis mestag
//

#include				"Capture_TalentEffect.hh"

Capture_TalentEffect::Capture_TalentEffect() :
  TalentEffect(false)
{

}

Capture_TalentEffect::~Capture_TalentEffect()
{

}

bool				Capture_TalentEffect::apply(Player &player,
							    unsigned int const fromPts,
							    unsigned int const toPts)
{
  for (unsigned int i = fromPts ; i <= toPts ; ++i)
    player.incStat("Capture", 1);
  return (true);
}

bool				Capture_TalentEffect::apply(Mob &mob __attribute__((unused)),
							    unsigned int const fromPts __attribute__((unused)), unsigned int const toPts __attribute__((unused)))
{
  return (true);
}
