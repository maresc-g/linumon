//
// TalentEffect.cpp for TalentEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat Mar 22 18:36:23 2014 alexis mestag
// Last update Tue Mar 25 23:32:00 2014 alexis mestag
//

#include			<algorithm>
#include			<functional>
#include			<iostream>
#include			"Effects/TalentEffect.hh"

TalentEffect::TalentEffect() :
  PlayerEffect(), /*_talent(NULL), */_forMob(false)
{

}

TalentEffect::TalentEffect(bool const isForMob) :
  PlayerEffect(), /*_talent(NULL), */_forMob(isForMob)
{

}

TalentEffect::~TalentEffect()
{

}

// void				TalentEffect::initialize(Talent const *talent)
// {
//   _talent = talent;
// }

// Talent const			*TalentEffect::getTalent() const
// {
//   return (_talent);
// }

void				TalentEffect::applyToAllMobs(Player &player, unsigned int const fromPts,
							     unsigned int const toPts)
{
  std::function<void(Mob *)>	mobEffectApplier = [&](Mob *mob) -> void {
    this->apply(*mob, fromPts, toPts);
  };
  std::for_each(player.getDigitaliser().begin(),
		player.getDigitaliser().end(),
		mobEffectApplier);
  std::for_each(player.getDigitaliser().getBattleMobs().begin(),
		player.getDigitaliser().getBattleMobs().end(),
		mobEffectApplier);
}

void				TalentEffect::setForMob(bool const isForMob)
{
  _forMob = isForMob;
}

bool				TalentEffect::isForMob() const
{
  return (_forMob);
}

bool				TalentEffect::apply(Player &player __attribute__((unused)))
{
  std::cerr << "This method should not be called !" << std::endl;
  return (false);
}
