//
// SFMLView.hpp for  in /home/jourda_c/Documents/Projets/PFA/Graphics
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Thu Sep 26 15:00:20 2013 cyril jourdain
// Last update Tue Feb 18 11:49:28 2014 guillaume marescaux
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

#include		"SFML/Sprite/SpriteManager.hh"
#include		"SFML/Sprite/Sprite.hh"

#include		"SFML/GraphicEntities.hh"
#include		"SFML/PlayerSprite.hh"
#include		"SFML/KeyDelayer.hh"


class			WindowManager;
class			SpellBarView;
class			ItemView;
class			InventoryView;
class			StuffView;
class			ChatView;
class			MenuView;

class			SFMLView : public QSFMLWidget
{
private:
  enum	eDir
    {
      LEFT,
      DOWN,
      RIGHT,
      UP,
      NONE
    };

private:
  typedef std::map<int, std::map<int, Sprite *>> SpriteMap;
  WindowManager		*_wMan;
  SpriteManager		*_sMan;
  PlayerSprite		*_mainPerso;
  sf::Clock		*_clock;
  std::list<GraphicPlayer*> _players; // Might be useless, since players are PlayerSprite
  SpriteMap		*_sprites;
  KeyDelayer		*_keyDelayer;
  sf::View		*_view;
  sf::Sprite		*_spriteTest;
  sf::Texture		*_textureTest;
  sf::RenderTexture	*_winTexture;
  sf::Sprite		*_winSprite;
  bool			_changed;
  float			_keyPressDelay; // Check key fast repeat - millisecond
  sf::Font		*_textFont;

  /* Child Views */
  SpellBarView		*_spellBar;
  ItemView		*_itemView;
  InventoryView		*_inventory;
  StuffView		*_stuff;
  ChatView		*_chat;
  MenuView		*_menu;

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
};

#endif
