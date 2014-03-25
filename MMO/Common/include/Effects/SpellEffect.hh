//
// SpellEffect.hh for SpellEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Feb 27 11:26:48 2014 alexis mestag
// Last update Tue Mar 25 14:47:29 2014 alexis mestag
//

#ifndef				__SPELLEFFECT_HH__
# define			__SPELLEFFECT_HH__

# include			"Effects/IEffect.hpp"
# include			"Effects/MobEffect.hh"
# include			"Entities/Mob.hh"
# include			"Entities/Spell.hh"
# include			"Battle/BattleParams.hh"

class				SpellEffect : public MobEffect
{
protected:
  SpellEffect();
public:
  virtual ~SpellEffect();

  virtual void			initialize(Mob &caster, Spell &spell, Mob &target,
					   BattleParams &battle) = 0;
};

#endif
