//
// ContreEffect.hh for ContreEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Mar 25 15:32:21 2014 alexis mestag
// Last update Tue Mar 25 15:44:41 2014 alexis mestag
//

#ifndef				__CONTREEFFECT_HH__
# define			__CONTREEFFECT_HH__

# include			"Effects/SpellEffect.hh"

class				ContreEffect : public SpellEffect
{
public:
  ContreEffect();
  virtual ~ContreEffect();

public:
  virtual void			initialize(Mob &launcher, Spell &spell, Mob &target, BattleParams &battle);
  virtual bool			apply(Mob &mob);
};

extern				"C"
{
  ContreEffect			*getInstance() {
    return (new ContreEffect);
  }
}

#endif
