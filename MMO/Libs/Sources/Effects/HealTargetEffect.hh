//
// HealTargetEffect.hh for HealTargetEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Mar 25 10:17:29 2014 alexis mestag
// Last update Tue Mar 25 10:20:58 2014 alexis mestag
//

#ifndef				__HEALTARGETEFFECT_HH__
# define			__HEALTARGETEFFECT_HH__

# include			"Effects/SpellEffect.hh"

class				HealTargetEffect : public SpellEffect
{
private:
  Stat::value_type		_hp;

public:
  HealTargetEffect();
  virtual ~HealTargetEffect();

public:
  virtual void			initialize(Mob &caster, Spell &spell, Mob &target);
  virtual bool			apply(Mob &mob);
};

extern				"C"
{
  HealTargetEffect		*getInstance() {
    return (new HealTargetEffect);
  }
}

#endif
