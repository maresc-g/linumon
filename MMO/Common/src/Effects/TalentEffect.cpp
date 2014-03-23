//
// TalentEffect.cpp for TalentEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat Mar 22 18:36:23 2014 alexis mestag
// Last update Sat Mar 22 18:48:22 2014 alexis mestag
//

#include			"Effects/TalentEffect.hh"

TalentEffect::TalentEffect() :
  PlayerEffect(), MobEffect(), _talent(NULL), _forMob(false)
{

}

TalentEffect::TalentEffect(bool const isForMob) :
  PlayerEffect(), MobEffect(), _talent(NULL), _forMob(isForMob)
{

}

TalentEffect::~TalentEffect()
{

}

void				TalentEffect::initialize(Talent const *talent)
{
  _talent = talent;
}

Talent const			*TalentEffect::getTalent() const
{
  return (_talent);
}

void				TalentEffect::setForMob(bool const isForMob)
{
  _forMob = isForMob;
}

bool				TalentEffect::isForMob() const
{
  return (_forMob);
}
