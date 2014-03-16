//
// SFMLView.cpp for  in /home/jourda_c/Documents/Projets/PFA/Graphics
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Thu Sep 26 15:05:46 2013 cyril jourdain
// Last update Sun Mar 16 16:53:27 2014 cyril jourdain
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

#include <QDebug>
#include		<stdexcept>
#include		"SFML/SFMLView.hpp"
#include		"Map/Map.hh"
#include		"Common/eState.hh"
#include		"SFML/WorldView.hh"
#include		"SFML/BattleView.hh"
#include		"Sound/SoundManager.hh"

SFMLView::SFMLView(QWidget *parent, QPoint const &position, QSize const &size, WindowManager *w) :
  QSFMLWidget(parent, position, size), _wMan(w), _sMan(new SpriteManager()),
  _clock(new sf::Clock()),  _keyDelayer(new KeyDelayer()),
  _inventory(new InventoryView(this, w)),
  _stuff(new StuffView(this, w)), _chat(new ChatView(this, w)), _menu(new MenuView(this, w)),
  _jobMenu(new JobMenuView(this, w)), _job(new JobView(this, w)), _digit(new DigitaliserView(this, w)),
  _clickView(new PlayerClickView(this, w)), _splitStack(new SplitStackView(this, w)),
  _guild(new GuildView(this, w)), _trade(new TradeView(this, w)),
  _worldView(new WorldView(this, w)), _battleView(new BattleView(this, w)),
  _currentView(NULL), _view1(NULL), _view2(NULL)
{
  _stuff->hide();
  _inventory->hide();
  _jobMenu->hide();
  _clickView->hide();
  // _job->move(300, 100);
  _digit->hide();
  // _digit->move(800, 0);
  // _inventory->move(1500, 0);
  _splitStack->hide();
  _job->hide();
  _menu->move(WIN_W / 2 - _menu->size().width() / 2, WIN_H / 2 - _menu->size().height() / 2);
  _menu->hide();
  _guild->hide();
  _trade->hide();
  _chat->move(0, WIN_H - _chat->size().height());
  _textFont = new sf::Font();
  if (!_textFont->loadFromFile("./Res/arial.ttf"))
     std::cout << "Error while loading font" << std::endl;
  _reset = false;
  _sMan->loadTextures("./Res/textureList.json");
  _sMan->loadSprites("./Res/spriteList.json");
  // _sMan->loadAnimations("./Res/perso1.json");
  // _sMan->loadAnimations("./Res/textures.json");
  // _sMan->loadAnimations("./Res/selectedPlayer.json");
  // _sMan->loadAnimations("./Res/Spell/Lance-Flamme.json");
  // _sMan->loadAnimations("./Res/Spell/Surf.json");
  // _sMan->loadAnimations("./Res/Spell/Boutefeu.json");
  // _sMan->loadAnimations("./Res/Spell/Danse-Fleur.json");
  _grow = false;
  _enterBattle = false;

  setMouseTracking(true);
  (static_cast<QApplication *>(QApplication::instance()))->setOverrideCursor(QCursor(QPixmap("./Res/cursor.png"), 0, 0));
}

SFMLView::~SFMLView()
{
}

void			SFMLView::onInit()
{
  std::cout << "INIT SFML" << std::endl;
  SoundManager::getInstance()->stopMusic(MENU_THEME);
  SoundManager::getInstance()->playMusic(WORLD_THEME);
  _reset = false;
  _clock->restart();
  _inventory->initInventory();
  _digit->initDigit((**_wMan->getMainPlayer())->getDigitaliser());
  // _worldView->onInit();
  // _currentView = _worldView;
  // _currentView->resetPOV();
  static_cast<BattleView*>(_battleView)->setLifeVisibility(false);
  raise();
  setFocus(Qt::OtherFocusReason);
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
      // if (**(_wMan->getState()) != CLIENT::ENTER_BATTLE)
      // 	if (event.type == sf::Event::KeyPressed)
      // 	  _currentView->onKeyEvent(event);
    }
  CLIENT::eState s = **(_wMan->getState());
  switch (s)
    {
    case CLIENT::LAUNCH_TRADE:
      _trade->show();
      _trade->move(800, 0);
      _trade->setInfos(_wMan->getTrade());
      (*_wMan->getState()) = CLIENT::TRADE;
      break;
    case CLIENT::TRADE:
      if ((**_wMan->getTrade())->getEnd())
	{
	  _trade->hide();
	  _inventory->initInventory();
	  _digit->initDigit((**_wMan->getMainPlayer())->getDigitaliser());
	  (*_wMan->getState()) = CLIENT::PLAYING;
	}
      else if ((**_wMan->getTrade())->getChanged())
	{
	  std::cout << "SOMETHING CHANGED" << std::endl;
	  _trade->setInfos(_wMan->getTrade());
	  (**_wMan->getTrade())->setChanged(false);
	}
      break;
    case CLIENT::NEWZONE:
      *(_wMan->getState()) = CLIENT::LOADING;
      break;
    case CLIENT::LOADED:
      _worldView->resetView();
      _worldView->onInit();
      _worldView->resetPOV();
      _worldView->centerView();
      _currentView = _worldView;
      *(_wMan->getState()) = CLIENT::PLAYING;
      return;
      break;
    case CLIENT::LEAVING_BATTLE:
      if (static_cast<BattleView*>(_battleView)->isBattleEnded()){
	_currentView = _worldView;
	_currentView->resetPOV();
	static_cast<BattleView*>(_battleView)->setLifeVisibility(false);
	static_cast<BattleView*>(_battleView)->quitBattle();
	*(_wMan->getState()) = CLIENT::PLAYING;      
	_grow = false;
      }
      break;
    case CLIENT::ENTER_BATTLE:
      if (static_cast<BattleView*>(_battleView)->canStartBattle()){
	static_cast<BattleView*>(_battleView)->battleStart();
	*(_wMan->getState()) = CLIENT::BATTLE;
	_battleView->resetPOV();
	static_cast<BattleView*>(_battleView)->resetHUDPos();
	static_cast<BattleView*>(_battleView)->setLifeVisibility(true);
	// SoundManager::getInstance()->playMusic(BATTLE_THEME);
	_chat->show();
      }
      break;
    case CLIENT::LOADING_BATTLE:
      if (!_grow)
	{
	  if (!_enterBattle){
	    SoundManager::getInstance()->stopMusic(WORLD_THEME);
	    SoundManager::getInstance()->playSound(TO_BATTLE);
	    _chat->hide();
	    _enterBattle = true;
	  }
	  _mainView->rotate(10);
	  _mainView->zoom(0.8);
	  if (_mainView->getSize().x <= 10)
	    {
	      _grow = true;
	      _battleView->onInit();
	      _currentView = _battleView;
	      *(_wMan->getState()) = CLIENT::ENTER_BATTLE;
	      _currentView->centerView();
	      _mainView->reset(sf::FloatRect(0,0,WIN_W, WIN_H));
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
      _menu->hide();
      _wMan->showLogin();
      break;
    default:
      break;
    }

  // Need to : Destroy map, entites, etc ...
  // std::cout << "clear screen" << std::endl;
  clear(sf::Color(0,183,235));
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

void			SFMLView::mouseMoveEvent(QMouseEvent *event)
{
  _currentView->onMouseEvent(event);
}

void			SFMLView::keyPressEvent(QKeyEvent *event)
{
  if (**(_wMan->getState()) != CLIENT::ENTER_BATTLE)
    _currentView->onKeyEvent(event);
}

void			SFMLView::displayView(QWidget *view)
{
  if (_view1 == view || _view2 == view)
    return;
  if (!_view1)
    {
      _view1 = view;
      _view1->show();
      _view1->move(0, 0);
    }
  else if (_view1 && !_view2)
    {
      _view2 = _view1;
      _view1 = view;
      _view1->show();
      _view2->move(_view1->size().width() + 50, 0);
      _view1->move(0, 0);
    }
  else
    {
      _view2->hide();
      _view2 = _view1;
      _view1 = view;
      _view2->move(_view1->size().width() + 50, 0);
      _view1->move(0, 0);
      _view1->show();
    }
}

void			SFMLView::hideView(QWidget *view)
{
  if (_view2 == view)
    {
      _view2->hide();
      _view2 = NULL;
    }
  else
    {
      _view1->hide();
      if (_view2)
	{
	  _view1 = _view2;
	  _view1->move(0, 0);
	  _view2 = NULL;
	}
      else
	_view1 = NULL;
    }
}

InventoryView		*SFMLView::getInventoryView(void){return (_inventory); }
StuffView		*SFMLView::getStuffView(void){return (_stuff); }
ChatView		*SFMLView::getChatView(void){return (_chat); }
MenuView		*SFMLView::getMenuView(void){return (_menu); }
JobMenuView		*SFMLView::getJobMenuView(void){return (_jobMenu); }
JobView			*SFMLView::getJobView(void) { return (_job); }
DigitaliserView		*SFMLView::getDigitaliserView(void) { return (_digit); }
sf::Font		*SFMLView::getFont(void) const {return _textFont; }
SpriteManager		*SFMLView::getSpriteManager(void) const {return _sMan; }
sf::Clock		*SFMLView::getMainClock(void) const {return _clock; }
KeyDelayer		*SFMLView::getKeyDelayer(void) {return _keyDelayer; }
ContextView		*SFMLView::getBattleView(void) {return _battleView; };
SplitStackView		*SFMLView::getSplitStackView(void) {return _splitStack; };
GuildView		*SFMLView::getGuildView(void) {return _guild; };
TradeView		*SFMLView::getTradeView(void) {return _trade; };
