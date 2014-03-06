//
// CharacterEffect.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Wed Mar  5 16:39:46 2014 laurent ansel
// Last update Wed Mar  5 17:04:22 2014 laurent ansel
//

#ifndef 			__STATENTITYEFFECT_HH__
# define 			__STATENTITYEFFECT_HH__

# include			"Entities/AStatEntity.hh"
# include			"Effects/IEffect.hpp"

class				StatEntityEffect : public AEffect<AStatEntity>
{
protected:
  StatEntityEffect();

public:
  virtual ~StatEntityEffect();
};

#endif
