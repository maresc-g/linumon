//
// MobSprite.hh for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Fri Mar  7 14:44:23 2014 cyril jourdain
// Last update Sun Mar  9 16:14:24 2014 guillaume marescaux
//

#ifndef 		__MOBSPRITE_HH__
# define 		__MOBSPRITE_HH__

#include		<QProgressBar>
#include		"SFML/PlayerSprite.hh"
#include		"Qt/Views/SpellBarView.hh"
#include		"Qt/Views/HUDView.hh"
#include		"Qt/WindowManager.hh"

class			MobSprite : public PlayerSprite
{
private:
  SpellBarView		*_spellBar;
  HUDView		*_hud;
  QProgressBar		*_pb;
  Mob const		*_mob;

public:
  MobSprite(sf::String const &, sf::Font *, WindowManager *);
  virtual ~MobSprite();

public:
  void				setHUDInfo(Mob const &);
  void				initHealthBar(Mob const &mob);
  void				upHealthBar();
  void				setInfoVisibility(bool);
  virtual void			onClick();
  virtual void			setPosition(int x, int y);
};

#endif
