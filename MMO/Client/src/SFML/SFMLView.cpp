//
// SFMLView.cpp for  in /home/jourda_c/Documents/Projets/PFA/Graphics
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Thu Sep 26 15:05:46 2013 cyril jourdain
// Last update Wed Mar  5 15:04:03 2014 cyril jourdain
//

/*

  Need to :	Add bubble when getting message (using player pos ?)
		Add border on map
		Other entities
		
		Test loading another map

		TO DO FIRST :
		get the player real position at start.
		check if it can move (map border)
 */

#include		<stdexcept>
#include		"SFML/SFMLView.hpp"
#include		"Map/Map.hh"
#include		"Common/eState.hh"
#include		"SFML/WorldView.hh"
#include		"SFML/BattleView.hh"

SFMLView::SFMLView(QWidget *parent, QPoint const &position, QSize const &size, WindowManager *w) :
  QSFMLWidget(parent, position, size), _wMan(w), _sMan(new SpriteManager()),
  _clock(new sf::Clock()), _keyDelayer(new KeyDelayer()),
  _spellBar(new SpellBarView(this, w)), _inventory(new InventoryView(this, w)),
  _stuff(new StuffView(this, w)), _chat(new ChatView(this, w)), _menu(new MenuView(this, w)),
  _jobMenu(new JobMenuView(this, w)), _job(new JobView(this, w)), _digit(new DigitaliserView(this, w)),
  _clickView(new PlayerClickView(this, w))
{
  _spellBar->hide();
  _stuff->hide();
  _inventory->hide();
  _jobMenu->hide();
  _clickView->hide();
  _job->move(300, 100);
  _digit->hide();
  _digit->move(800, 0);
  _inventory->move(1500, 0);
  _job->hide();
  _menu->move(WIN_W / 2 - _menu->size().width() / 2, WIN_H / 2 - _menu->size().height() / 2);
  _menu->hide();
  _chat->move(0, WIN_H - _chat->size().height());
  _textFont = new sf::Font();
  if (!_textFont->loadFromFile("./Res/arial.ttf"))
     std::cout << "Error while loading font" << std::endl;
  _reset = false;
  _sMan->loadTextures("./Res/textureList.json");
  _sMan->loadAnimations("./Res/perso1.json");
  _sMan->loadAnimations("./Res/textures.json");
  _sMan->loadAnimations("./Res/selectedPlayer.json");
  _grow = false;

  _worldView = new WorldView(this, w);
  _battleView = new BattleView(this, w);
}

SFMLView::~SFMLView()
{
}

void			SFMLView::onInit()
{
  _reset = false;
  _clock->restart();
  _inventory->initInventory();
  _digit->initDigit((**_wMan->getMainPlayer())->getDigitaliser());
  _worldView->onInit();
  // *(_wMan->getState()) = CLIENT::LOADING_BATTLE;
  _battleView->onInit();
  _currentView = _worldView;
  _currentView->resetPOV();
}

void			SFMLView::onUpdate()
{
  sf::Event event;

  if (_reset)
    {
      onInit();
      _reset = false;
    }

  while (pollEvent(event))
    {
      if (event.type == sf::Event::KeyPressed)
	_currentView->onKeyEvent(event);
    }
  /* Not used here but SFML need it to handle internal events */

  CLIENT::eState s = **(_wMan->getState());
  switch (s)
    {
    case CLIENT::ENTER_BATTLE:
      _mainView->rotate(-10);
      _mainView->zoom(1.2);
      if (_mainView->getSize().x > WIN_W)
	{
	  *(_wMan->getState()) = CLIENT::BATTLE;
	  _battleView->resetPOV();
	}
      break;
    case CLIENT::LOADING_BATTLE:
      if (!_grow)
	{
	  _mainView->rotate(10);
	  _mainView->zoom(0.8);
	  if (_mainView->getSize().x <= 10)
	    {
	      _grow = true;
	      _currentView = _battleView;
	      *(_wMan->getState()) = CLIENT::ENTER_BATTLE;
	      _currentView->centerView();
	    }
	}
      std::cout << _mainView->getSize().x << std::endl;
      break;
    case CLIENT::CHOOSE_PLAYER:
      reset();
      _wMan->hideSfmlView();
      _menu->hide();
      _wMan->showCharacter();
      break;
    case CLIENT::LOGIN:
      _wMan->hideSfmlView();
      _wMan->showLogin();
      break;
    default:
      break;
    }
  // Need to : Destroy map, entites, etc ...
  clear(sf::Color(0,0,0));
  if (_reset)
    return;
  _keyDelayer->update(_clock);
  _currentView->onUpdate();
  _currentView->drawView();
  _clock->restart();
  _chat->update();
}

void			SFMLView::onResize(QResizeEvent *e)
{
  setSize(sf::Vector2u(e->size().width(), e->size().height()));
}

void			SFMLView::reset()
{
  _worldView->resetView();
  _reset = true;
}
void			SFMLView::mousePressEvent(QMouseEvent *event)
{
  _currentView->onMouseEvent(event);
}

SpellBarView		*SFMLView::getSpellBarView(void){return (_spellBar); }
InventoryView		*SFMLView::getInventoryView(void){return (_inventory); }
StuffView		*SFMLView::getStuffView(void){return (_stuff); }
ChatView		*SFMLView::getChatView(void){return (_chat); }
MenuView		*SFMLView::getMenuView(void){return (_menu); }
JobMenuView		*SFMLView::getJobMenuView(void){return (_jobMenu); }
JobView			*SFMLView::getJobView(void) { return (_job); }
sf::Font		*SFMLView::getFont(void) const {return _textFont; }
SpriteManager		*SFMLView::getSpriteManager(void) const {return _sMan; }
sf::Clock		*SFMLView::getMainClock(void) const {return _clock; }
KeyDelayer		*SFMLView::getKeyDelayer(void) {return _keyDelayer; }
