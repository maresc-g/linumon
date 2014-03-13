//
// DigitaliserManager.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Mar 13 18:41:58 2014 laurent ansel
// Last update Thu Mar 13 18:43:04 2014 laurent ansel
//

#ifndef 			__DIGITALISERMANAGER_HH__
# define 			__DIGITALISERMANAGER_HH__

#include			"Trame/Trame.hh"

class				DigitaliserManager
{
private:
  bool				mobToBattleMob(Trame *trame);
  bool				battleMobToMob(Trame *trame);
  bool				switchMobs(Trame *trame);

public:
  DigitaliserManager();
  virtual ~DigitaliserManager();
};

#endif
