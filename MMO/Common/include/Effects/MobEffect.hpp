//
// MobEffect.hh for MobEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Fri Feb 14 10:38:37 2014 alexis mestag
// Last update Fri Feb 14 10:46:12 2014 alexis mestag
//

#ifndef				__MOBEFFECT_HPP__
# define			__MOBEFFECT_HPP__

class				MobEffect : public AEffect<Mob>
{
protected:
  MobEffect() : AEffect<Mob>(Effect::eType::MOB) {}
  virtual ~MobEffect() {}
};

#endif
