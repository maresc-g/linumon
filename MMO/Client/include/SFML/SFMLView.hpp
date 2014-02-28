//
// SFMLView.hpp for  in /home/jourda_c/Documents/Projets/PFA/Graphics
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Thu Sep 26 15:00:20 2013 cyril jourdain
// Last update Fri Feb 28 12:56:30 2014 cyril jourdain
//

#ifndef 		__SFMLVIEW_HPP__
# define 		__SFMLVIEW_HPP__

#include		<map>

#include		"Qt/QSFMLWidget.hpp"
#include		"Qt/WindowManager.hh"
#include		"Qt/Views/SpellBarView.hh"
#include		"Qt/Views/InventoryView.hh"
#include		"Qt/Views/StuffView.hh"
#include		"Qt/Views/ChatView.hh"
#include		"Qt/Views/MenuView.hh"
#include                "Qt/Views/JobMenuView.hh"
#include                "Qt/Views/JobView.hh"

#include		"SFML/Sprite/SpriteManager.hh"
#include		"SFML/Sprite/Sprite.hh"

#include		"SFML/GraphicEntities.hh"
#include		"SFML/PlayerSprite.hh"
#include		"SFML/KeyDelayer.hh"
#include		"SFML/OPlayerSprite.hh"
#include		"SFML/RessourceSprite.hh"

#define			CASE_SIZE	64

class			WindowManager;
class			SpellBarView;
class			InventoryView;
class			StuffView;
class			ChatView;
class			MenuView;
class			JobMenuView;
class			JobView;

class			SFMLView : public QSFMLWidget
{

private:
  typedef std::map<int, std::map<int, Sprite *>> SpriteMap;
  typedef std::map<sf::Keyboard::Key, void (SFMLView::*)()> KeyMap;
  WindowManager		*_wMan;
  SpriteManager		*_sMan;
  PlayerSprite		*_mainPerso;
  sf::Clock		*_clock;
  SpriteMap		*_sprites;
  KeyDelayer		*_keyDelayer;
  std::vector<OPlayerSprite *> *_playerList;
  std::list<RessourceSprite*>	*_entities;
  KeyMap		*_keyMap;
  sf::Sprite		*_spriteTest;
  sf::Texture		*_textureTest;
  sf::RenderTexture	*_winTexture;
  sf::Sprite		*_winSprite;
  bool			_changed;
  sf::Font		*_textFont;
  sf::Keyboard::Key	_pressedKey;
  bool			_reset;

  /* Child Views */
  SpellBarView		*_spellBar;
  InventoryView		*_inventory;
  StuffView		*_stuff;
  ChatView		*_chat;
  MenuView		*_menu;
  JobMenuView		*_jobMenu;
  JobView		*_job;

public:
  SFMLView(QWidget *, QPoint const &, QSize const &, WindowManager *_wMan);
  virtual ~SFMLView();

public:
  JobView		*getJobView(void) const;

private :
  virtual void			onInit();
  virtual void			onUpdate();
  virtual void			onResize(QResizeEvent *);
  void				drawView();
  void				checkKeys();
  void				loadPlayerList();
  void				loadMap();
  void                          reloadBackgroundSprite();
  void				reset();

private:
  void				keyUp();
  void				keyDown();
  void				keyLeft();
  void				keyRight();
  void				keyI();
  void				keyS();
  void				keyJ();
  void				keyEscape();
  void				keyReturn();
  void				keyControl();
  virtual void		        mousePressEvent(QMouseEvent *);
};

#endif
