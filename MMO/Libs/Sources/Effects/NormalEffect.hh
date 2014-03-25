//
// NormalEffect.hh for NormalEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Feb 27 16:46:56 2014 alexis mestag
// Last update Tue Mar 25 14:48:23 2014 alexis mestag
//

#ifndef				__NORMALEFFECT_HH__
# define			__NORMALEFFECT_HH__

# include			"Effects/SpellEffect.hh"

class				NormalEffect : public SpellEffect
{
private:
  Stat::value_type		_hp;

public:
  NormalEffect();
  virtual ~NormalEffect();

public:
  virtual void			initialize(Mob &caster, Spell &spell, Mob &target,
					   BattleParams &battle);
  virtual bool			apply(Mob &mob);
};

extern				"C" {
  NormalEffect			*getInstance() {
    return (new NormalEffect);
  }
}

#endif
