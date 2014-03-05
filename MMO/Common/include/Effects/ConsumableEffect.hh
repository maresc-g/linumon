//
// ConsumableEffect.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Wed Mar  5 11:22:13 2014 laurent ansel
// Last update Wed Mar  5 11:22:35 2014 laurent ansel
//

#ifndef 			__CONSUMABLEEFFECT_HH__
# define 			__CONSUMABLEEFFECT_HH__

# include			"Effects/IEffect.hpp"
# include			"Entities/Consumable.hh"

class				ConsumableEffect : AEffect<Consumable>
{
protected:
  ConsumableEffect();

public:
  virtual ~ConsumableEffect();
};

#endif
