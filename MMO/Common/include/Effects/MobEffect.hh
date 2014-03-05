//
// MobEffect.hh for MobEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Fri Feb 14 10:38:37 2014 alexis mestag
// Last update Wed Mar  5 15:50:56 2014 laurent ansel
//

#ifndef				__MOBEFFECT_HPP__
# define			__MOBEFFECT_HPP__

# include			"Effects/IEffect.hpp"
# include			"Entities/Mob.hh"

class				MobEffect : public AEffect<Mob>
{
protected:
  MobEffect();

public:
  virtual ~MobEffect();
};

#endif
