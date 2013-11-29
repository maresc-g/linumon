//
// ISerialization.hh for  in /home/ansel_l/Documents/Pfa/work/Common
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Nov 29 15:22:29 2013 laurent ansel
// Last update Fri Nov 29 15:33:20 2013 laurent ansel
//

#ifndef 			__ISERIALIZATION_HH__
# define 			__ISERIALIZATION_HH__

#include			"Trame/Trame.hh"

class				ISerialization
{
public:
  virtual ~ISerialization(){}
  virtual bool			serialization(Trame &trame) = 0;
  virtual bool			deserialization(Trame const &trame) = 0;
};

#endif
