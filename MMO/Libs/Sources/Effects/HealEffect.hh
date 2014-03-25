//
// HealEffect.hh for HealEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Mar 25 09:35:03 2014 alexis mestag
// Last update Tue Mar 25 14:47:05 2014 alexis mestag
//

#ifndef				__HEALEFFECT_HH__
# define			__HEALEFFECT_HH__

# include			"Effects/SpellEffect.hh"

class				HealEffect : public SpellEffect
{
private:
  Stat::value_type		_hp;

public:
  HealEffect();
  virtual ~HealEffect();

public:
  virtual void			initialize(Mob &caster, Spell &spell, Mob &target,
					   BattleParams &battle);
  virtual bool			apply(Mob &mob);
};

extern				"C"
{
  HealEffect			*getInstance() {
    return (new HealEffect);
  }
}

#endif
