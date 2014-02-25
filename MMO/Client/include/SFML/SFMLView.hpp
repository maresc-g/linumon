//
// SFMLView.hpp for  in /home/jourda_c/Documents/Projets/PFA/Graphics
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Thu Sep 26 15:00:20 2013 cyril jourdain
// Last update Tue Feb 25 12:55:47 2014 guillaume marescaux
//

#ifndef 		__SFMLVIEW_HPP__
# define 		__SFMLVIEW_HPP__

#include		<map>

#include		"Qt/QSFMLWidget.hpp"
#include		"Qt/WindowManager.hh"
#include		"Qt/Views/SpellBarView.hh"
#include		"Qt/Views/ItemView.hh"
#include		"Qt/Views/InventoryView.hh"
#include		"Qt/Views/StuffView.hh"
#include		"Qt/Views/ChatView.hh"
#include		"Qt/Views/MenuView.hh"
#include		"Qt/Views/JobMenuView.hh"

#include		"SFML/Sprite/SpriteManager.hh"
#include		"SFML/Sprite/Sprite.hh"

#include		"SFML/GraphicEntities.hh"
#include		"SFML/PlayerSprite.hh"
#include		"SFML/KeyDelayer.hh"

#define			CASE_SIZE	64

class			WindowManager;
class			SpellBarView;
class			ItemView;
class			InventoryView;
class			StuffView;
class			ChatView;
class			MenuView;
class			JobMenuView;

class			SFMLView : public QSFMLWidget
{

private:
  typedef std::map<int, std::map<int, Sprite *>> SpriteMap;
  WindowManager		*_wMan;
  SpriteManager		*_sMan;
  PlayerSprite		*_mainPerso;
  sf::Clock		*_clock;
  SpriteMap		*_sprites;
  KeyDelayer		*_keyDelayer;
  std::vector<PlayerSprite *> *_playerList;
  sf::Sprite		*_spriteTest;
  sf::Texture		*_textureTest;
  sf::RenderTexture	*_winTexture;
  sf::Sprite		*_winSprite;
  bool			_changed;
  sf::Font		*_textFont;

  /* Child Views */
  SpellBarView		*_spellBar;
  ItemView		*_itemView;
  InventoryView		*_inventory;
  StuffView		*_stuff;
  ChatView		*_chat;
  MenuView		*_menu;
  JobMenuView		*_jobMenu;

public:
  SFMLView(QWidget *, QPoint const &, QSize const &, WindowManager *_wMan);
  virtual ~SFMLView();

private :
  virtual void			onInit();
  virtual void			onUpdate();
  virtual void			onResize(QResizeEvent *);
  void				drawView();
  void				checkKeys();
  void				loadPlayerList();
  void				loadMap();
  void                          reloadBackgroundSprite();
};

#endif
