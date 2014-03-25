//
// HealEffect.cpp for HealEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Mar 25 09:38:15 2014 alexis mestag
// Last update Tue Mar 25 10:23:10 2014 alexis mestag
//

#include				"HealEffect.hh"

HealEffect::HealEffect() :
  SpellEffect(), _hp(1)
{

}

HealEffect::~HealEffect()
{

}

void					HealEffect::initialize(Mob &caster, Spell &spell, Mob &target)
{
  double				hp;

  // ((Pui * STAB
  hp = spell.getPower() * (caster.getType() == spell.getType() ? 1.5 : 1.0);
  // × Att × (2 + 0.4 × Niv))
  hp *= ((caster.getCurrentStat("Heal") + caster.getCurrentStat("Attack")) / 2.0) *
    (2.0 + 0.4 * caster.getLevel());
  // ÷ (Def × 50)
  hp /= target.getCurrentStat("Defense") * 50.0;
  // + 2) * CE
  hp += 2.0;
  hp *= caster.getType().getCoeffAgainst(target.getType());
  _hp = hp ? hp : 1;
  caster.incCurrentStat("HP", _hp > 1 ? _hp / 2 : 1);
}

bool					HealEffect::apply(Mob &mob)
{
  mob.decCurrentStat("HP", _hp);
  return (true);
}
