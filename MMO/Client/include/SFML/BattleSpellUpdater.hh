//
// BattleSpellUpdater.hh for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Sat Mar  8 20:48:47 2014 cyril jourdain
// Last update Tue Mar 18 23:50:52 2014 cyril jourdain
//

#ifndef 		__BATTLESPELLUPDATER_HH__
# define 		__BATTLESPELLUPDATER_HH__

#include		"SFML/Sprite/Sprite.hh"
#include		"SFML/SFMLView.hpp"
#include		"Qt/WindowManager.hh"
#include		"SFML/BattleView.hh"

class BattleView;
class BattleMob;

class			BattleSpellUpdater
{
private:
  SFMLView		*_sfmlView;
  WindowManager		*_wMan;
  Sprite		*_currentSpell;
  BattleMob		*_previousTarget;

public:
  BattleSpellUpdater(SFMLView *, WindowManager *);
  virtual ~BattleSpellUpdater();

public:
  void			update(BattleView *);
  void			draw();
  bool			endTurn();
  BattleMob		*getPreviousTarget() const;
};

#endif
