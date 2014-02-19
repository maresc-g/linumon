//
// DamageEffect.cpp for DamageEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/EffectLibs
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Feb 19 13:51:52 2014 alexis mestag
// Last update Wed Feb 19 13:58:15 2014 alexis mestag
//

#include			"DamageEffect.hpp"

DamageEffect::DamageEffect(int const damage __attribute__((unused))) :
  AEffect<Mob>(Effect::eType::MOB), _damage(damage)
{

}

DamageEffect::~DamageEffect()
{

}

bool				DamageEffect::apply(Mob &mob)
{
  (void)mob;
  std::cout << "DamageEffect::apply(Mob &); (" << _damage << ")" << std::endl;
  return (true);
}
