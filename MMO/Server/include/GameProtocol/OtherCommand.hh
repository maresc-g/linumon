//
// otherCommand.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Sat Feb  8 17:47:42 2014 laurent ansel
// Last update Sat Feb  8 17:55:51 2014 laurent ansel
//

#ifndef 			__OTHERCOMMAND_HH__
# define 			__OTHERCOMMAND_HH__

#include			"Trame/Trame.hh"

class				OtherCommand
{
private:
  bool				heal(Trame *trame);

public:
  OtherCommand();
  virtual ~OtherCommand();
};

#endif
