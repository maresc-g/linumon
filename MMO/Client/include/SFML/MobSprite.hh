//
// MobSprite.hh for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Fri Mar  7 14:44:23 2014 cyril jourdain
// Last update Fri Mar  7 15:14:45 2014 cyril jourdain
//

#ifndef 		__MOBSPRITE_HH__
# define 		__MOBSPRITE_HH__

#include		"SFML/PlayerSprite.hh"
#include		"Qt/Views/SpellBarView.hh"
#include		"Qt/Views/HUDView.hh"
#include		"Qt/WindowManager.hh"

class			MobSprite : public PlayerSprite
{
private:
  SpellBarView		*_spellBar;
  HUDView		*_hud;

public:
  MobSprite(sf::String const &, sf::Font *, WindowManager *);
  virtual ~MobSprite();

public:
  void				setHUDInfo(Mob const &);
void				setInfoVisibility(bool);
  virtual void			onClick();
};

#endif
