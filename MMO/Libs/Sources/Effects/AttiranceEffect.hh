//
// AttiranceEffect.hh for AttiranceEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Mar 25 15:40:37 2014 alexis mestag
// Last update Tue Mar 25 15:44:21 2014 alexis mestag
//

#ifndef				__ATTIRANCEEFFECT_HH__
# define			__ATTIRANCEEFFECT_HH__

# include			"Effects/SpellEffect.hh"

class				AttiranceEffect : public SpellEffect
{
public:
  AttiranceEffect();
  virtual ~AttiranceEffect();

public:
  virtual void			initialize(Mob &launcer, Spell &spell, Mob &target, BattleParams &battle);
  virtual bool			apply(Mob &mob);
};

extern				"C"
{
  AttiranceEffect		*getInstance() {
    return (new AttiranceEffect);
  }
}

#endif
