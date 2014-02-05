//
// AEffect.hh for AEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Jan 29 16:06:44 2014 alexis mestag
// Last update Wed Feb  5 14:12:59 2014 alexis mestag
//

#ifndef			__IEFFECT_HH__
# define		__IEFFECT_HH__

# include		"Entities/ACharacter.hh"

class			IEffect
{
protected:
  virtual ~IEffect() {}

  virtual bool		apply(ACharacter &character) = 0;
};

#endif
