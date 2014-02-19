//
// DamageEffect.hpp for DamageEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Feb 16 16:53:19 2014 alexis mestag
// Last update Wed Feb 19 13:54:05 2014 alexis mestag
//

#ifndef				__DAMAGEEFFECT_HPP__
# define			__DAMAGEEFFECT_HPP__

# include			"Effects/IEffect.hpp"
# include			"Entities/Mob.hh"

class				DamageEffect : public AEffect<Mob>
{
private:
  int				_damage;

public:
  DamageEffect(int const damage);
  virtual ~DamageEffect();

public:
  virtual bool			apply(Mob &mob);
};

extern			"C" {
  DamageEffect		*getInstance() {
    return (new DamageEffect(0));
  }

  DamageEffect		*getParamInstance(int const p) {
    return (new DamageEffect(p));
  }
}

#endif
