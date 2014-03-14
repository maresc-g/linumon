//
// Interaction.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Sat Feb  8 17:36:31 2014 laurent ansel
// Last update Fri Mar 14 16:05:09 2014 laurent ansel
//

#ifndef 			__INTERACTION_HH__
# define 			__INTERACTION_HH__

#include			"Trame/Trame.hh"
#include			"Trade/TradeManager.hh"

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
