//
// NormalEffect.cpp for NormalEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/EffectLibs
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Feb 27 16:57:56 2014 alexis mestag
// Last update Tue Mar 11 12:30:20 2014 antoine maitre
//

#include				"NormalEffect.hh"

NormalEffect::NormalEffect() :
  SpellEffect(), _hp(1)
{

}

NormalEffect::~NormalEffect()
{

}

#include				<iostream>

void					NormalEffect::initialize(Mob &caster, Spell &spell, Mob &target)
{
  double				hp;

  std::cout << caster.getName() << " is using " << spell.getName() << " against " << target.getName() << std::endl;
  // ((Pui
  hp = spell.getPower() * (caster.getType() == spell.getType() ? 1.5 : 1);
  // × Att × (2 + 0.4 × Niv))
  hp *= caster.getCurrentStat("Attack") * (2 + 0.4 * caster.getLevel());
  // ÷ (Def × 50)
  hp /= target.getCurrentStat("Defense") * 50;
  // + 2) * CE
  hp += 2;
  hp *= caster.getType().getCoeffAgainst(target.getType());
  _hp = hp;
}

bool					NormalEffect::apply(Mob &mob)
{
  std::cout << mob.getName() << " was hit by " << (int)_hp << std::endl;
  if (_hp > mob.getCurrentStat("HP"))
    _hp = mob.getCurrentStat("HP");
  mob.setCurrentStat("HP", mob.getCurrentStat("HP") - _hp);
  return (true);
}

// void					NormalEffect::initializeByCaster(Mob &caster)
// {

// }

// void					NormalEffect::initializeBySpell(Spell &spell)
// {
//   _power *= spell.getPower();
// }
