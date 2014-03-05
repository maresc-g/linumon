//
// PlayerEffect.hh for PlayerEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Feb 26 14:37:41 2014 alexis mestag
// Last update Wed Mar  5 16:40:54 2014 laurent ansel
//

#ifndef				__PLAYEREFFECT_HH__
# define			__PLAYEREFFECT_HH__

# include			"Effects/IEffect.hpp"
# include			"Entities/Player.hh"

class				PlayerEffect : public AEffect<Player>
{
protected:
  PlayerEffect();

public:
  virtual ~PlayerEffect();
};

#endif
