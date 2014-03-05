//
// StuffActions.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Sat Feb  8 16:32:32 2014 laurent ansel
// Last update Tue Mar  4 11:21:05 2014 laurent ansel
//

#ifndef 			__STUFFACTIONS_HH__
# define 			__STUFFACTIONS_HH__

#include			"Trame/Trame.hh"

class				StuffActions
{
private:
  bool				stuffAction(Trame *trame);
  bool				getStuff(Trame *trame);
  bool				putStuff(Trame *trame);

public:
  StuffActions();
  virtual ~StuffActions();
};

#endif
