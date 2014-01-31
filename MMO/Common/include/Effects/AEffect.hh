//
// AEffect.hh for AEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Jan 29 16:06:44 2014 alexis mestag
// Last update Thu Jan 30 13:59:42 2014 alexis mestag
//

#ifndef			__AEFFECT_HH__
# define		__AEFFECT_HH__

# include		"Entities/ACharacter.hh"

class			AEffect
{
protected:
  AEffect();
  virtual ~AEffect();

  virtual void		apply(ACharacter &character) const = 0;
};

#endif
