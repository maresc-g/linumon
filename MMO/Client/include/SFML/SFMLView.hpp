//
// SFMLView.hpp for  in /home/jourda_c/Documents/Projets/PFA/Graphics
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Thu Sep 26 15:00:20 2013 cyril jourdain
// Last update Tue Feb 11 13:56:12 2014 cyril jourdain
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

#include		"SFML/Sprite/SpriteManager.hh"
#include		"SFML/Sprite/Sprite.hh"

#include		"SFML/GraphicEntities.hh"


class			WindowManager;
class			SpellBarView;
class			ItemView;
class			InventoryView;
class			StuffView;
class			ChatView;

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
  Sprite		*_mainPerso;
  sf::Clock		*_clock;
  std::list<GraphicPlayer*> _players;
  SpriteMap		*_sprites;
  sf::View		*_view;
  sf::Sprite		*_spriteTest;
  sf::Texture		*_textureTest;
  sf::Vector2f		_pos;
  sf::Vector2f		_deltaPos;
  bool			_moving;
  eDir			_dir;

  /* Child Views */
  SpellBarView		*_spellBar;
  ItemView		*_itemView;
  InventoryView		*_inventory;
  StuffView		*_stuff;
  ChatView		*_chat;

public:
  SFMLView(QWidget *, QPoint const &, QSize const &, WindowManager *_wMan);
  virtual ~SFMLView();

private :
  virtual void			onInit();
  virtual void			onUpdate();
  virtual void			onResize(QResizeEvent *);
  void				drawView();
  void				checkKeys();
  void				moveMainPerso(float const elapsedTime);
  void				loadPlayerList();
  void				loadMap();
};

#endif
