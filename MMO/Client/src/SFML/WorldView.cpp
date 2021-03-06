//
// WorldView.cpp for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Mon Mar  3 14:01:32 2014 cyril jourdain
// Last update Tue Mar 25 23:27:39 2014 cyril jourdain
//

#include		"SFML/WorldView.hh"
#include		<stdexcept>
#include		<QMenu>
#include <QDebug>
#include		"SFML/Window/ComputerScreen.hh"
#include		"Sound/SoundManager.hh"

WorldView::WorldView(SFMLView *v, WindowManager *w) :
  ContextView(v, w), _mainPerso(NULL), _playerList(new std::vector<OPlayerSprite *>),
  _keyMap(new KeyMap()), _pressedKey(Qt::Key(0)), _ressourcesLoader(NULL), _currentWindow(NULL)
{
  (*_keyMap)[Qt::Key_Up] = &WorldView::keyUp;
  (*_keyMap)[Qt::Key_Down] = &WorldView::keyDown;
  (*_keyMap)[Qt::Key_Left] = &WorldView::keyLeft;
  (*_keyMap)[Qt::Key_Right] = &WorldView::keyRight;
  (*_keyMap)[Qt::Key_Control] = &WorldView::keyControl;
  (*_keyMap)[Qt::Key_I] = &WorldView::keyI;
  (*_keyMap)[Qt::Key_S] = &WorldView::keyS;
  (*_keyMap)[Qt::Key_J] = &WorldView::keyJ;
  (*_keyMap)[Qt::Key_D] = &WorldView::keyD;
  (*_keyMap)[Qt::Key_G] = &WorldView::keyG;
  (*_keyMap)[Qt::Key_T] = &WorldView::keyT;
  (*_keyMap)[Qt::Key_Escape] = &WorldView::keyEscape;
  (*_keyMap)[Qt::Key_Return] = &WorldView::keyReturn;
}


WorldView::~WorldView()
{
}

void			WorldView::onInit()
{
  Zone *zone = Map::getInstance()->getZone((**(_wMan->getMainPlayer()))->getZone());

  _ressourcesLoader = new RessourcesSpriteLoader(_wMan);
  _backgroundTexture = new sf::RenderTexture();
  _backgroundSprite = new sf::Sprite();
  _mainPerso = new PlayerSprite(sf::String((**(_wMan->getMainPlayer()))->getName()), _sfmlView->getFont());
  _sfmlView->getSpriteManager()->copySprite("perso1", *_mainPerso);
  _mainPerso->setPlayerZone(Map::getInstance()->getZone((**(_wMan->getMainPlayer()))->getZone())->getName());
  _mainPerso->setPlayerId((**(_wMan->getMainPlayer()))->getId());
  _mainPerso->play("default_down");
  _mainPerso->generateOffset();
  _mainPerso->setPosition((**(_wMan->getMainPlayer()))->getX() * CASE_SIZE,
			  (**(_wMan->getMainPlayer()))->getY() * CASE_SIZE - _mainPerso->getCurrentBound()->height / 2 + 4);
  resetPOV();
  // _sfmlView->getMainView()->move((**(_wMan->getMainPlayer()))->getX() * CASE_SIZE - WIN_W / 2,
  // 		  (**(_wMan->getMainPlayer()))->getY() * CASE_SIZE - WIN_H / 2);
  if (zone)
    _backgroundTexture->create(zone->getSizeX() * CASE_SIZE, zone->getSizeY()*CASE_SIZE);
  qDebug() << "loadBackgroundMap";
  loadBackgroundMap();
  loadBackgroundSprite();
  loadPlayerList();
  // loadEntities();
  _ressourcesLoader->loadRessources();
}

void			WorldView::onUpdate()
{
  _ressourcesLoader->checkCarcass();
  if (_mainPerso) {
    _mainPerso->moveFromServer(_sfmlView->getMainView());
    _mainPerso->updateMoves(_sfmlView->getMainClock(), _sfmlView->getMainView());
    _mainPerso->update(*(_sfmlView->getMainClock()));
  }
  if (**(_wMan->getNewPlayer()))
    {
      loadPlayerList();
      *(_wMan->getNewPlayer()) = false;
    }
  if (_currentWindow)
    _currentWindow->update(*(_sfmlView->getMainClock()));
  if ((**_wMan->getInvite())->invited)
    {
      _wMan->getSFMLView()->getInviteView()->setInfos((**_wMan->getInvite())->name);
      _wMan->getSFMLView()->getInviteView()->show();
      (**_wMan->getInvite())->invited = false;
    }
}

void			WorldView::drawView()
{
  _sfmlView->setView(*(_sfmlView->getMainView()));
  _backgroundSprite->setTexture(_backgroundTexture->getTexture());
  _sfmlView->draw(*_backgroundSprite);
  _ressourcesLoader->drawLayer(RessourcesSpriteLoader::FLOOR_LAYER);
  _ressourcesLoader->drawLayer(RessourcesSpriteLoader::CARCASS_LAYER);
  for (auto it = _playerList->begin(); it != _playerList->end(); ++it)
    {
      if ((**(_wMan->getMainPlayer()))->getId() == ((*it)->getPlayerId()))
      	continue;
      if (*it){
  	(*it)->moveFromServer();
  	(*it)->updateMoves(_sfmlView->getMainClock(), NULL);
  	(*it)->update(*_sfmlView->getMainClock());
  	_sfmlView->draw(**it);
      }      
    }
  if (_mainPerso) {
    _sfmlView->draw(*_mainPerso);
  }
  _ressourcesLoader->drawLayer(RessourcesSpriteLoader::TOP_LAYER);
  if (_currentWindow)
    _currentWindow->draw();
}

void			WorldView::onKeyEvent(QKeyEvent *event)
{
  CLIENT::eState s = **(_wMan->getState());
  if ((!_currentWindow) || (_currentWindow && !_currentWindow->isModal())){
    // CLIENT::eState s = **(_wMan->getState());
    if (s == CLIENT::PLAYING || s == CLIENT::TRADE){
      try {
	(this->*(_keyMap->at(Qt::Key(event->key()))))();
      }
      catch (std::out_of_range const &e) {
      }
    }
  }
  if (_currentWindow)
    _currentWindow->onKeyEvent(event);
}

void			WorldView::onMouseEvent(QMouseEvent *event)
{
  sf::Vector2f	v = _sfmlView->mapPixelToCoords(sf::Vector2i(event->x(), event->y()));

  if (event->button() == Qt::RightButton && _mainPerso->isClicked(v.x, v.y))
    {
      _mainPerso->onClick(event);
    }
  if (event->button() == Qt::RightButton){
    for (auto it = _playerList->begin(); it != _playerList->end(); it++)
      {
	if ((*it)->getPlayerId() != _mainPerso->getPlayerId())
	  {
	    if ((*it)->isClicked(v.x, v.y))
	      {
		(*it)->onClick(event);
		QMenu menu;

		menu.addAction("Trade");
		menu.addAction("Fight");
		QAction *action = menu.exec(QPoint(event->x(), event->y()));

		if (action)
		  {
		    if (action->text() == "Trade")
		      {
			std::string name = Map::getInstance()->getPlayerById((*it)->getPlayerId())->getName();
			Client::getInstance()->interaction(eInteraction::TRADE,
							   name);
		      }
		    if (action->text() == "Fight")
		      {
			std::string name = Map::getInstance()->getPlayerById((*it)->getPlayerId())->getName();
			Client::getInstance()->interaction(eInteraction::AGRO,
							   name);
		      }
		  }
		return;
	      }
	  }
      }
  }
  _ressourcesLoader->onMouseEvent(event);
}

void			WorldView::resetView()
{
  delete _mainPerso;
  _mainPerso = NULL;
  for (auto it = _playerList->begin(); it != _playerList->end(); ++it)
    delete *it;
  _playerList->clear();
  for (auto it = _spriteMap->begin(); it != _spriteMap->end(); it++)
    {
      for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
	{
	  delete (it2->second);
	  it2->second = NULL;
	}
      it->second.clear();
    }
  _spriteMap->clear();
  delete _backgroundTexture;
  _backgroundTexture = NULL;
  delete _backgroundSprite;
  _backgroundSprite = NULL;
  delete _ressourcesLoader;
  _ressourcesLoader = NULL;
}

void			WorldView::resetPOV()
{
  _sfmlView->getMainView()->reset(sf::FloatRect(0,0, WIN_W, WIN_H));
  _sfmlView->getMainView()->move((**(_wMan->getMainPlayer()))->getX() * CASE_SIZE - WIN_W / 2,
				 (**(_wMan->getMainPlayer()))->getY() * CASE_SIZE - WIN_H / 2);
  _sfmlView->clear(sf::Color(0,0,0));
  _sfmlView->getMainView()->zoom(0.8);
  // if ((**(_wMan->getMainPlayer()))->getX() <= 15)
  //   _sfmlView->getMainView()->move((15 - (**(_wMan->getMainPlayer()))->getX()) * CASE_SIZE, 0);
}

void			WorldView::setCurrentWindow(Window *w)
{
  if (_currentWindow)
    delete _currentWindow;
  _currentWindow = w;
}

void			WorldView::loadPlayerList()
{
  std::list<AEntity *>	list = Map::getInstance()->getZone((**(_wMan->getMainPlayer()))->getZone())->getPlayers();
  OPlayerSprite		*tmp = NULL;

  for (auto it = _playerList->begin(); it != _playerList->end(); it++)
    delete *it;
  _playerList->clear();
  for (auto it = list.begin(); it != list.end(); it++)
    {
      if ((static_cast<Player*>(*it))->getId() == _mainPerso->getPlayerId() || static_cast<Player*>(*it)->isInBattle())
  	continue;
      tmp = new OPlayerSprite((*it)->getName(),
			      _sfmlView->getFont());
      _sfmlView->getSpriteManager()->copySprite("perso1", *tmp);
      tmp->setPlayerZone(Map::getInstance()->getZone((**(_wMan->getMainPlayer()))->getZone())->getName());
      tmp->setPlayerId((static_cast<Player*>(*it))->getId());
      tmp->play("default_down");
      tmp->generateOffset();
      tmp->setPosition((static_cast<Player*>(*it))->getX() * CASE_SIZE,
		       (static_cast<Player*>(*it))->getY() * CASE_SIZE - tmp->getCurrentBound()->height / 2 + 4);
      _playerList->push_back(tmp);
    }
}

void			WorldView::loadEntities()
{
  // Zone	*zone = Map::getInstance()->getZone((**(_wMan->getMainPlayer()))->getZone());
  // std::list<AEntity*>	*list;
  // RessourceSprite	*tmp;
  // sf::Vector2i		*pos = new sf::Vector2i(0,0);

  // for (int y = 0; y < zone->getSizeY(); y++)
  //   {
  //     for (int x = 0; x < zone->getSizeX(); x++)
  // 	{
  // 	  list = zone->getCase(x,y)->getEntities();
  // 	  if (list && list->size() > 0)
  // 	    {
  // 	      for (auto it = list->begin(); it != list->end(); it++)
  // 		{
  // 		  std::cout << "RESSOURCE NAME : " << (*it)->getName() << std::endl;
  // 		  if ((*it)->getEntityType() == AEntity::RESSOURCE)
  // 		    {
  // 		      pos->x = static_cast<Ressource*>(*it)->getX();
  // 		      pos->y = static_cast<Ressource*>(*it)->getY();
  // 		      if ((*it)->getName() == "Tree")
  // 			{
  // 			  tmp = new RessourceSprite(static_cast<Ressource*>(*it));
  // 			  if (!_sfmlView->getSpriteManager()->copySprite("tree_trunk", *tmp))
  // 			    continue;
  // 			  tmp->play("default");
  // 			  tmp->setPosition(pos->x * CASE_SIZE,
  // 					   pos->y * CASE_SIZE);
  // 			  tmp->setPos(pos->x,
  // 				      pos->y);
  // 			  _entities->push_back(tmp);
  // 			  tmp = new RessourceSprite(static_cast<Ressource*>(*it));
  // 			  if (!_sfmlView->getSpriteManager()->copySprite("tree_top", *tmp))
  // 			    continue;
  // 			  tmp->play("default");
  // 			  tmp->setPosition(pos->x * CASE_SIZE- 64,
  // 					   pos->y * CASE_SIZE - 128);
  // 			  tmp->setPos(pos->x,
  // 				      pos->y);
  // 			  _topLayer->push_back(tmp);
  // 			}
  // 		      else
  // 			{
  // 			  tmp = new RessourceSprite(static_cast<Ressource*>(*it));
  // 			  if (!_sfmlView->getSpriteManager()->copySprite((*it)->getName(), *tmp))
  // 			    continue;
  // 			  tmp->play("default");
  // 			  tmp->setPosition(pos->x * CASE_SIZE,
  // 					   pos->y * CASE_SIZE);
  // 			  tmp->setPos(pos->x,
  // 				      pos->y);
  // 			  _entities->push_back(tmp);
  // 			}
  // 		    }
  // 		}
  // 	    }
  // 	}
  //   }
}

void			WorldView::keyUp()
{
  keyControl();
  if (!_mainPerso->isMoving())
    {
      _mainPerso->play("default_up");
      if (Client::getInstance()->move(CLIENT::UP)){
	  _pressedKey = Qt::Key_Up;
	  _mainPerso->setWaitingState();
      }
    }
  else if (_mainPerso->isMoving() && _mainPerso->isUserInputable() && _pressedKey == Qt::Key_Up)
    {
      if (Client::getInstance()->move(CLIENT::UP))
	_mainPerso->receivedInput();
    }
}

void			WorldView::keyDown()
{
  keyControl();
  if (!_mainPerso->isMoving())
    {
      _mainPerso->play("default_down");
      if (Client::getInstance()->move(CLIENT::DOWN)){
	_pressedKey = Qt::Key_Down;
	_mainPerso->setWaitingState();
      }
    }
  else if (_mainPerso->isMoving() && _mainPerso->isUserInputable() && _pressedKey == Qt::Key_Down)
    {
      if (Client::getInstance()->move(CLIENT::DOWN))
	_mainPerso->receivedInput();
    }
}

void			WorldView::keyLeft()
{
  keyControl();
  if (!_mainPerso->isMoving())
    {
      _mainPerso->play("default_left");
      if (Client::getInstance()->move(CLIENT::LEFT)){
	_pressedKey = Qt::Key_Left;
	_mainPerso->setWaitingState();
      }
    }
  else if (_mainPerso->isMoving() && _mainPerso->isUserInputable() && _pressedKey == Qt::Key_Left)
    {
      if (Client::getInstance()->move(CLIENT::LEFT))
	_mainPerso->receivedInput();
    }
}

void			WorldView::keyRight()
{
  keyControl();
  if (!_mainPerso->isMoving())
    {
      _mainPerso->play("default_right");
      if (Client::getInstance()->move(CLIENT::RIGHT)){
	_pressedKey = Qt::Key_Right;
	_mainPerso->setWaitingState();
      }
    }
  else if (_mainPerso->isMoving() && _mainPerso->isUserInputable() && _pressedKey == Qt::Key_Right)
    {
      if (Client::getInstance()->move(CLIENT::RIGHT))
	{
	  _mainPerso->receivedInput();
	}
    }
}

void			WorldView::keyControl()
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
    _mainPerso->setSpeed(PX_PER_SECOND + 200);
  else
    _mainPerso->setSpeed(PX_PER_SECOND);
}

void			WorldView::keyI()
{
  if (_sfmlView->getKeyDelayer()->isAvailable(Qt::Key_I) && !_sfmlView->getChatView()->getFocused())
    {
      std::cout << "KEY I" << std::endl;
      if (!_sfmlView->getInventoryView()->isVisible())
	{
	  SoundManager::getInstance()->playSoundForce("Inventory_open",30);
	  _sfmlView->getInventoryView()->initInventory();
	  _sfmlView->displayView(_sfmlView->getInventoryView());
	}
      else{
	_sfmlView->hideView(_sfmlView->getInventoryView());
	SoundManager::getInstance()->playSoundForce("Inventory_close",30);
      }
      _sfmlView->getKeyDelayer()->addWatcher(Qt::Key_I, 100000);
    }
}

void			WorldView::keyS()
{
  if (_sfmlView->getKeyDelayer()->isAvailable(Qt::Key_S) && !_sfmlView->getChatView()->getFocused())
    {
      if (!_sfmlView->getStuffView()->isVisible())
	{
	  _sfmlView->getStuffView()->initStuff(***(_wMan->getMainPlayer()));
	  _sfmlView->displayView(_sfmlView->getStuffView());
	}
      else
	_sfmlView->hideView(_sfmlView->getStuffView());
      _sfmlView->getKeyDelayer()->addWatcher(Qt::Key_S, 100000);
    }
}

void			WorldView::keyJ()
{
  if (_sfmlView->getKeyDelayer()->isAvailable(Qt::Key_J) && !_sfmlView->getChatView()->getFocused())
    {
      if (!_sfmlView->getJobMenuView()->isVisible())
	  _sfmlView->displayView(_sfmlView->getJobMenuView());
      else
	  _sfmlView->hideView(_sfmlView->getJobMenuView());
      _sfmlView->getKeyDelayer()->addWatcher(Qt::Key_J, 100000);
    }
}

void			WorldView::keyD()
{
  if (_sfmlView->getKeyDelayer()->isAvailable(Qt::Key_D) && !_sfmlView->getChatView()->getFocused())
    {
      if (!_sfmlView->getDigitaliserView()->isVisible())
	{
	  _sfmlView->getDigitaliserView()->initDigit((**_wMan->getMainPlayer())->getDigitaliser());
	  _sfmlView->displayView(_sfmlView->getDigitaliserView());
	}
      else
	_sfmlView->hideView(_sfmlView->getDigitaliserView());
      _sfmlView->getKeyDelayer()->addWatcher(Qt::Key_D, 100000);
    }
}

void			WorldView::keyG()
{
  if (_sfmlView->getKeyDelayer()->isAvailable(Qt::Key_G) && !_sfmlView->getChatView()->getFocused())
    {
      if (!_sfmlView->getGuildView()->isVisible())
	{
	  _sfmlView->getGuildView()->initGuild((**_wMan->getMainPlayer())->getGuild());
	  _sfmlView->displayView(_sfmlView->getGuildView());
	}
      else
	_sfmlView->hideView(_sfmlView->getGuildView());
      _sfmlView->getKeyDelayer()->addWatcher(Qt::Key_G, 100000);
    }
}

void			WorldView::keyT()
{
  if (_sfmlView->getKeyDelayer()->isAvailable(Qt::Key_T) && !_sfmlView->getChatView()->getFocused())
    {
      if (!_sfmlView->getTalentsView()->isVisible())
	{
	  _sfmlView->getTalentsView()->initTalents((**_wMan->getMainPlayer())->getTalentTree(),
						   (**_wMan->getMainPlayer())->getTalents().getCurrentPts());
	  _sfmlView->displayView(_sfmlView->getTalentsView());
	}
      else
	_sfmlView->hideView(_sfmlView->getTalentsView());
      _sfmlView->getKeyDelayer()->addWatcher(Qt::Key_T, 100000);
    }
}

void			WorldView::keyEscape()
{
  if (_sfmlView->getKeyDelayer()->isAvailable(Qt::Key_Escape) && !_sfmlView->getChatView()->getFocused())
    {
      if (!_sfmlView->getMenuView()->isVisible())
	_sfmlView->getMenuView()->show();
      else
	_sfmlView->getMenuView()->hide();
      _sfmlView->getKeyDelayer()->addWatcher(Qt::Key_Escape, 100000);
    }
}

void			WorldView::keyReturn()
{
  if (_sfmlView->getKeyDelayer()->isAvailable(Qt::Key_Return))
    {
      if (!_sfmlView->getChatView()->getFocused())
  	_sfmlView->getChatView()->setFocused(true);
      else
  	_sfmlView->getChatView()->submitText();
      _sfmlView->getKeyDelayer()->addWatcher(Qt::Key_Return, 100000);
    }
}
