//
// JobManager.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Sat Feb  8 17:29:06 2014 laurent ansel
// Last update Sat Feb  8 17:55:55 2014 laurent ansel
//

#ifndef 			__JOBMANAGER_HH__
# define 			__JOBMANAGER_HH__

#include			"Trame/Trame.hh"

class				JobManager
{
private:
  bool				gather(Trame *trame);
  bool				craft(Trame *trame);

public:
  JobManager();
  virtual ~JobManager();
};

#endif
