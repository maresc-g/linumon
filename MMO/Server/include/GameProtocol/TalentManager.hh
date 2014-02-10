//
// TalentManager.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Sat Feb  8 17:23:53 2014 laurent ansel
// Last update Mon Feb 10 14:43:25 2014 laurent ansel
//

#ifndef 			__TALENTMANAGER_HH__
# define 			__TALENTMANAGER_HH__

#include			"Trame/Trame.hh"
#include			"Entities/Player.hh"

class				TalentManager
{
private:
  bool				talents(Trame *trame);
public:
  TalentManager();
  virtual ~TalentManager();

  static void			updateTalents(Trame *trame, Player *player);
};

#endif
