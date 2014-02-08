//
// Interaction.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Sat Feb  8 17:36:31 2014 laurent ansel
// Last update Sat Feb  8 17:56:37 2014 laurent ansel
//

#ifndef 			__INTERACTION_HH__
# define 			__INTERACTION_HH__

#include			"Trame/Trame.hh"

class				Interaction
{
public:
  typedef enum			eInteraction
    {
      NONE,
      AGRO,
      TRADE
    }				eInteraction;

private:
  bool				interaction(Trame *trame);
  bool				agro(Trame *trame);
  bool				trade(Trame *trame);

public:
  Interaction();
  virtual ~Interaction();
};

#endif
