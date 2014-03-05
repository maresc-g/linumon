//
// WorldView.cpp for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Mon Mar  3 14:01:32 2014 cyril jourdain
// Last update Wed Mar  5 15:03:30 2014 cyril jourdain
//

#include		"SFML/WorldView.hh"
#include		<stdexcept>

/*
  Load player list
  Uncomment entities
  Map for key handling
  Clean SFMLView class plz
 */

WorldView::WorldView(SFMLView *v, WindowManager *w) :
  ContextView(v, w), _mainPerso(NULL), _playerList(new std::vector<OPlayerSprite *>),
  _entities(new std::list<RessourceSprite *>), _keyMap(new KeyMap()), _pressedKey(sf::Keyboard::Unknown),
  _clickView(new PlayerClickView(v, w))
{
  (*_keyMap)[sf::Keyboard::Up] = &WorldView::keyUp;
  (*_keyMap)[sf::Keyboard::Down] = &WorldView::keyDown;
  (*_keyMap)[sf::Keyboard::Left] = &WorldView::keyLeft;
  (*_keyMap)[sf::Keyboard::Right] = &WorldView::keyRight;
  (*_keyMap)[sf::Keyboard::LControl] = &WorldView::keyControl;
  (*_keyMap)[sf::Keyboard::I] = &WorldView::keyI;
  (*_keyMap)[sf::Keyboard::S] = &WorldView::keyS;
  (*_keyMap)[sf::Keyboard::J] = &WorldView::keyJ;
  (*_keyMap)[sf::Keyboard::Escape] = &WorldView::keyEscape;
  (*_keyMap)[sf::Keyboard::Return] = &WorldView::keyReturn;
  _clickView->hide();
}


WorldView::~WorldView()
{
}

void			WorldView::onInit()
{
  /* This function MUST be called after player init
   */
  Zone *zone = Map::getInstance()->getZone((**(_wMan->getMainPlayer()))->getZone());

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
  loadBackgroundMap();
  loadBackgroundSprite();
  loadPlayerList();
  loadEntities();
}

void			WorldView::onUpdate()
{
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
}

void			WorldView::onKeyEvent(sf::Event const &event)
{
  try {
    (this->*(_keyMap->at(event.key.code)))();
  }
  catch (std::out_of_range const &e) {
  }
}

void			WorldView::onMouseEvent(QMouseEvent *event)
{
  sf::Vector2f	v = _sfmlView->mapPixelToCoords(sf::Vector2i(event->x(), event->y()));

  _clickView->hide();
  if (event->button() == Qt::RightButton && _mainPerso->isClicked(v.x, v.y))
    {
      _mainPerso->onClick();
      _clickView->move(event->x(), event->y());
      _clickView->show();
    }
  for (auto it = _playerList->begin(); it != _playerList->end(); it++)
    {
      if ((*it)->getPlayerId() != _mainPerso->getPlayerId())
  	{
  	  if ((*it)->isClicked(v.x, v.y))
  	    {
  	      _clickView->move(event->x(), event->y());
  	      _clickView->show();
  	      (*it)->onClick();
  	    }
  	}
    }
  for (auto it = _entities->begin(); it != _entities->end(); it++)
    {
      if ((*it)->isVisible())
  	{
  	  if ((*it)->isClicked(v.x, v.y))
  	    (*it)->onClick();
  	}
    }
}

void			WorldView::resetView()
{
  delete _mainPerso;
  for (auto it = _entities->begin(); it != _entities->end(); ++it)
    delete *it;
  _entities->clear();
  for (auto it = _playerList->begin(); it != _playerList->end(); ++it)
    delete *it;
  _playerList->clear();
  for (auto it = _spriteMap->begin(); it != _spriteMap->end(); it++)
    {
      for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
  	delete (it2->second);
      it->second.clear();
    }
  _spriteMap->clear();
}

void			WorldView::drawView()
{
  _backgroundSprite->setTexture(_backgroundTexture->getTexture());
  _sfmlView->draw(*_backgroundSprite);
  if (_mainPerso) {
    _sfmlView->draw(*_mainPerso);
  }
  for (auto it = _entities->begin(); it != _entities->end(); ++it)
    {
      (*it)->update(*_sfmlView->getMainClock());
      _sfmlView->draw(**it);
    }
  for (auto it = _playerList->begin(); it != _playerList->end(); ++it)
    {
      if ((**(_wMan->getMainPlayer()))->getId() == ((*it)->getPlayerId()))
      	continue;
      (*it)->moveFromServer();
      (*it)->updateMoves(_sfmlView->getMainClock(), NULL);
      (*it)->update(*_sfmlView->getMainClock());
      _sfmlView->draw(**it);
    }
  _sfmlView->setView(*(_sfmlView->getMainView()));
}

void			WorldView::loadPlayerList()
{
  std::list<AEntity *>	list = Map::getInstance()->getZone((**(_wMan->getMainPlayer()))->getZone())->getPlayers();

  for (auto it = _playerList->begin(); it != _playerList->end(); it++)
    delete *it;
  _playerList->clear();
  for (auto it = list.begin(); it != list.end(); it++)
    {
      if ((static_cast<Player*>(*it))->getId() == _mainPerso->getPlayerId())
  	continue;
      _playerList->push_back(new OPlayerSprite((static_cast<Player*>(*it))->getName(),
					       _sfmlView->getFont()));
      _sfmlView->getSpriteManager()->copySprite("perso1", *_playerList->back());
      _playerList->back()->setPlayerZone(Map::getInstance()->getZone((**(_wMan->getMainPlayer()))->getZone())->getName());
      _playerList->back()->setPlayerId((static_cast<Player*>(*it))->getId());
      _playerList->back()->play("default_down");
      _playerList->back()->generateOffset();
      _playerList->back()->setPosition((static_cast<Player*>(*it))->getX() * CASE_SIZE,
  				       (static_cast<Player*>(*it))->getY() * CASE_SIZE - _playerList->back()->getCurrentBound()->height / 2 + 4);
    }
}

void			WorldView::loadEntities()
{
  Zone	*zone = Map::getInstance()->getZone((**(_wMan->getMainPlayer()))->getZone());
  std::list<AEntity*>	*list;

  for (int y = 0; y < zone->getSizeY(); y++)
    {
      for (int x = 0; x < zone->getSizeX(); x++)
	{
	  list = zone->getCase(x,y)->getEntities();
	  if (list && list->size() > 0)
	    {
	      for (auto it = list->begin(); it != list->end(); it++)
	  	{
	  	  if ((*it)->getEntityType() == AEntity::RESSOURCE) {
	  	    _entities->push_back(new RessourceSprite(static_cast<Ressource*>(*it)));
	  	    _sfmlView->getSpriteManager()->copySprite(static_cast<Ressource*>(*it)->getName(),
							      *_entities->back());
	  	    _entities->back()->play("default");
	  	    _entities->back()->setPosition(static_cast<Ressource*>(*it)->getX() * CASE_SIZE,
	  					   static_cast<Ressource*>(*it)->getY() * CASE_SIZE);
		    _entities->back()->setPos(static_cast<Ressource*>(*it)->getX(),
					      static_cast<Ressource*>(*it)->getY());
	  	  }
	  	}
	    }
	}
    }
}

void			WorldView::keyUp()
{
  keyControl();
  if (!_mainPerso->isMoving())
    {
      _mainPerso->play("default_up");
      if (Client::getInstance()->move(CLIENT::UP)){
	  _pressedKey = sf::Keyboard::Up;
	  _mainPerso->setWaitingState();
      }
    }
  else if (_mainPerso->isMoving() && _mainPerso->isUserInputable() && _pressedKey == sf::Keyboard::Up)
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
	_pressedKey = sf::Keyboard::Down;
	_mainPerso->setWaitingState();
      }
    }
  else if (_mainPerso->isMoving() && _mainPerso->isUserInputable() && _pressedKey == sf::Keyboard::Down)
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
	_pressedKey = sf::Keyboard::Left;
	_mainPerso->setWaitingState();
      }
    }
  else if (_mainPerso->isMoving() && _mainPerso->isUserInputable() && _pressedKey == sf::Keyboard::Left)
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
	_pressedKey = sf::Keyboard::Right;
	_mainPerso->setWaitingState();
      }
    }
  else if (_mainPerso->isMoving() && _mainPerso->isUserInputable() && _pressedKey == sf::Keyboard::Right)
    {
      if (Client::getInstance()->move(CLIENT::RIGHT))
	_mainPerso->receivedInput();
    }
}

void			WorldView::keyControl()
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
    _mainPerso->setSpeed(PX_PER_SECOND + 100);
  else
    _mainPerso->setSpeed(PX_PER_SECOND);
}

void			WorldView::keyI()
{
  if (_sfmlView->getKeyDelayer()->isAvailable(sf::Keyboard::I) && !_sfmlView->getChatView()->getFocused())
    {
      if (!_sfmlView->getInventoryView()->isVisible())
	{
	  _sfmlView->getInventoryView()->initInventory();
	  _sfmlView->getInventoryView()->show();
	}
      else
	_sfmlView->getInventoryView()->hide();
      _sfmlView->getKeyDelayer()->addWatcher(sf::Keyboard::I, 100000);
    }
}

void			WorldView::keyS()
{
  if (_sfmlView->getKeyDelayer()->isAvailable(sf::Keyboard::S) && !_sfmlView->getChatView()->getFocused())
    {
      if (!_sfmlView->getStuffView()->isVisible())
	{
	  _sfmlView->getStuffView()->initStuff(***(_wMan->getMainPlayer()));
	  _sfmlView->getStuffView()->show();
	}
      else
	_sfmlView->getStuffView()->hide();
      _sfmlView->getKeyDelayer()->addWatcher(sf::Keyboard::S, 100000);
    }
}

void			WorldView::keyJ()
{
  if (_sfmlView->getKeyDelayer()->isAvailable(sf::Keyboard::J) && !_sfmlView->getChatView()->getFocused())
    {
      if (!_sfmlView->getJobMenuView()->isVisible())
	_sfmlView->getJobMenuView()->show();
      else
	_sfmlView->getJobMenuView()->hide();
      _sfmlView->getKeyDelayer()->addWatcher(sf::Keyboard::J, 100000);
    }
}

void			WorldView::keyEscape()
{
  if (_sfmlView->getKeyDelayer()->isAvailable(sf::Keyboard::Escape) && !_sfmlView->getChatView()->getFocused())
    {
      if (!_sfmlView->getMenuView()->isVisible())
	_sfmlView->getMenuView()->show();
      else
	_sfmlView->getMenuView()->hide();
      _sfmlView->getKeyDelayer()->addWatcher(sf::Keyboard::Escape, 100000);
    }
}

void			WorldView::keyReturn()
{
  // if (_sfmlView->getKeyDelayer()->isAvailable(sf::Keyboard::Return))
  //   {
  //     if (!_sfmlView->getChatView()->getFocused())
  // 	_sfmlView->getChatView()->setFocused(true);
  //     else
  // 	_sfmlView->getChatView()->submitText();
  //     _sfmlView->getKeyDelayer()->addWatcher(sf::Keyboard::Return, 100000);
  //   }
  *(_wMan->getState()) = CLIENT::LOADING_BATTLE;
}

void			WorldView::resetPOV()
{
  _sfmlView->getMainView()->reset(sf::FloatRect(0,0, WIN_W, WIN_H));
  _sfmlView->getMainView()->move((**(_wMan->getMainPlayer()))->getX() * CASE_SIZE - WIN_W / 2,
				 (**(_wMan->getMainPlayer()))->getY() * CASE_SIZE - WIN_H / 2);
}
