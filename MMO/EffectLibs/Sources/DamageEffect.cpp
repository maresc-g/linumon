//
// DamageEffect.cpp for DamageEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/EffectLibs
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Feb 19 13:51:52 2014 alexis mestag
// Last update Mon Feb 24 13:36:49 2014 alexis mestag
//

#include			"DamageEffect.hpp"

DamageEffect::DamageEffect(int const damage) :
  AEffect<Mob>(Effect::eType::MOB), _damage(damage)
{

}

DamageEffect::~DamageEffect()
{

}

bool				DamageEffect::apply(Mob &mob)
{
  std::cout << "DamageEffect::apply(Mob &); (" << _damage << ")" << std::endl;
  std::cout << "\t ===> " << mob.getName() << std::endl;
  for (auto it = mob.getStatKeys().getKeys().begin() ;
       it != mob.getStatKeys().getKeys().end() ;
       ++it)
    std::cout << "\t\t" << (*it)->getName() << std::endl;
  return (true);
}
