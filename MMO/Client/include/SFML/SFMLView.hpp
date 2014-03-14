//
// SFMLView.hpp for  in /home/jourda_c/Documents/Projets/PFA/Graphics
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Thu Sep 26 15:00:20 2013 cyril jourdain
<<<<<<< HEAD
// Last update Fri Mar 14 13:27:48 2014 guillaume marescaux
=======
// Last update Fri Mar 14 12:45:07 2014 cyril jourdain
>>>>>>> cfa7e2858b3ff50fba73d4f5643022a9a341fc5e
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
#include                "Qt/Views/DigitaliserView.hh"
#include                "Qt/Views/PlayerClickView.hh"
#include                "Qt/Views/SplitStackView.hh"
#include                "Qt/Views/GuildView.hh"
#include                "Qt/Views/TradeView.hh"
#include		"SFML/Sprite/SpriteManager.hh"
#include		"SFML/Sprite/Sprite.hh"

#include		"SFML/GraphicEntities.hh"
#include		"SFML/PlayerSprite.hh"
#include		"SFML/KeyDelayer.hh"
#include		"SFML/OPlayerSprite.hh"
#include		"SFML/RessourceSprite.hh"
#include		"SFML/defines.hh"
#include		"SFML/ContextView.hh"
// #include		"SFML/WorldView.hh"

class			WindowManager;
class			SpellBarView;
class			InventoryView;
class			StuffView;
class			ChatView;
class			MenuView;
class			JobMenuView;
class			JobView;
class			DigitaliserView;
class			PlayerClickView;
class			SplitStackView;
class			GuildView;
class			TradeView;
class			ContextView;

class			SFMLView : public QSFMLWidget
{

private:
  typedef std::map<int, std::map<int, Sprite *>> SpriteMap;
  typedef std::map<sf::Keyboard::Key, void (SFMLView::*)()> KeyMap;
  WindowManager		*_wMan;
  SpriteManager		*_sMan;
  sf::Clock		*_clock;
  KeyDelayer		*_keyDelayer;
  sf::Font		*_textFont;
  bool			_reset;
  bool			_grow;
  bool			_enterBattle;

  /* Child Views */
  InventoryView		*_inventory;
  StuffView		*_stuff;
  ChatView		*_chat;
  MenuView		*_menu;
  JobMenuView		*_jobMenu;
  JobView		*_job;
  DigitaliserView	*_digit;
  PlayerClickView	*_clickView;
  SplitStackView	*_splitStack;
  GuildView		*_guild;
  TradeView		*_trade;

  ContextView		*_worldView;
  ContextView		*_battleView;
  ContextView		*_currentView;
  QWidget		*_view1;
  QWidget		*_view2;

public:
  SFMLView(QWidget *, QPoint const &, QSize const &, WindowManager *_wMan);
  virtual ~SFMLView();

public:
  sf::Font			*getFont(void) const;
  SpriteManager			*getSpriteManager(void) const;
  sf::Clock			*getMainClock(void) const;
  KeyDelayer			*getKeyDelayer(); /* Not const, used by W&B view */

private :
  virtual void			onInit();
  virtual void			onUpdate();
  virtual void			onResize(QResizeEvent *);
  void				reset();

private:
  virtual void		        mousePressEvent(QMouseEvent *);
  virtual void			mouseMoveEvent(QMouseEvent *);
  virtual void			keyPressEvent(QKeyEvent *);

public:
  void				displayView(QWidget *view);
  void				hideView(QWidget *view);

public: /* Child view accessors for World and Battle view, not const */
  SpellBarView			*getSpellBarView(void);
  InventoryView			*getInventoryView(void);
  StuffView			*getStuffView(void);
  ChatView			*getChatView(void);
  MenuView			*getMenuView(void);
  JobMenuView			*getJobMenuView(void);
  JobView			*getJobView(void);
  DigitaliserView		*getDigitaliserView(void);
  ContextView			*getBattleView(void);
  SplitStackView		*getSplitStackView(void);
  GuildView			*getGuildView(void);
  TradeView			*getTradeView(void);
};

#endif
