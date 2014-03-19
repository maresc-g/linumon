//
// MobSprite.hh for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Fri Mar  7 14:44:23 2014 cyril jourdain
// Last update Tue Mar 18 23:32:59 2014 cyril jourdain
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
  WindowManager		*_wMan;
  SpellBarView		*_spellBar;
  HUDView		*_hud;
  QProgressBar		*_pb;
  Mob const		*_mob;
  bool			_isVisible;
  double		_mcurrent;

public:
  MobSprite(sf::String const &, sf::Font *, WindowManager *);
  virtual ~MobSprite();

public:
  void				setHUDInfo(Mob const &);
  void				initHealthBar(Mob const &mob);
  void				upHealthBar();
  void				setInfoVisibility(bool);
  void				resetHUDPos();
  void				setLifeVisibility(bool);
  virtual void			onClick(QMouseEvent *);
  virtual void			setPosition(int x, int y);
  virtual void			update(sf::Clock &);
  bool				isHealthBarUpdated() const;
};

#endif
