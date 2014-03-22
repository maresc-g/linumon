//
// NormalEffect.cpp for NormalEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/EffectLibs
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Feb 27 16:57:56 2014 alexis mestag
// Last update Fri Mar 21 20:12:10 2014 alexis mestag
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

  // ((Pui * STAB
  hp = spell.getPower() * (caster.getType() == spell.getType() ? 1.5 : 1.0);
  // × Att × (2 + 0.4 × Niv))
  hp *= caster.getCurrentStat("Attack") * (2.0 + 0.4 * caster.getLevel());
  // ÷ (Def × 50)
  hp /= target.getCurrentStat("Defense") * 50.0;
  // + 2) * CE
  hp += 2.0;
  hp *= caster.getType().getCoeffAgainst(target.getType());
  _hp = hp;
}


bool					NormalEffect::apply(Mob &mob)
{
  mob.decCurrentStat("HP", _hp);
  return (true);
}
