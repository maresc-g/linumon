//
// SFMLView.cpp for  in /home/jourda_c/Documents/Projets/PFA/Graphics
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Thu Sep 26 15:05:46 2013 cyril jourdain
// Last update Thu Feb 27 00:07:17 2014 cyril jourdain
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

SFMLView::SFMLView(QWidget *parent, QPoint const &position, QSize const &size, WindowManager *w) :
  QSFMLWidget(parent, position, size), _wMan(w), _sMan(new SpriteManager()), _mainPerso(NULL),
  _clock(new sf::Clock()), _sprites(new SpriteMap), _keyDelayer(new KeyDelayer()),
  _playerList(new std::vector<OPlayerSprite*>), _entities(new std::list<RessourceSprite*>()), _keyMap(new KeyMap),
  _spellBar(new SpellBarView(this, w)), _itemView(new ItemView(this, w)),
  _inventory(new InventoryView(this, w)), _stuff(new StuffView(this, w)),
  _chat(new ChatView(this, w)), _menu(new MenuView(this, w)), _jobMenu(new JobMenuView(this, w)),
  _job(new JobView(this, w))
{
  _textureTest = new sf::Texture();
  _textureTest->loadFromFile("./Res/test.png");
  _spriteTest = new sf::Sprite(*_textureTest);
  _spriteTest->setScale(4,4);
  _spellBar->hide();
  _itemView->hide();
  _stuff->hide();
  _inventory->hide();
  _jobMenu->hide();
  _job->move(300, 100);
  _job->hide();
  _menu->move(WIN_W / 2 - _menu->size().width() / 2, WIN_H / 2 - _menu->size().height() / 2);
  _menu->hide();
  _chat->move(0, WIN_H - _chat->size().height());
  _winTexture = new sf::RenderTexture();
  _winTexture->create(100*CASE_SIZE, 100*CASE_SIZE);
  _winSprite = new sf::Sprite();
  _changed = false;
  // _mainPName = new sf::Text();
  _textFont = new sf::Font();
  if (!_textFont->loadFromFile("./Res/arial.ttf"))
     std::cout << "Error while loading font" << std::endl;
  _pressedKey = sf::Keyboard::Unknown;
  _reset = false;

  (*_keyMap)[sf::Keyboard::Up] = &SFMLView::keyUp;
  (*_keyMap)[sf::Keyboard::Down] = &SFMLView::keyDown;
  (*_keyMap)[sf::Keyboard::Left] = &SFMLView::keyLeft;
  (*_keyMap)[sf::Keyboard::Right] = &SFMLView::keyRight;
  (*_keyMap)[sf::Keyboard::I] = &SFMLView::keyI;
  (*_keyMap)[sf::Keyboard::S] = &SFMLView::keyS;
  (*_keyMap)[sf::Keyboard::J] = &SFMLView::keyJ;
  (*_keyMap)[sf::Keyboard::Escape] = &SFMLView::keyEscape;
  (*_keyMap)[sf::Keyboard::Return] = &SFMLView::keyReturn;
  _sMan->loadTextures("./Res/textureList.json");
  _sMan->loadAnimations("./Res/perso1.json");
  _sMan->loadAnimations("./Res/textures.json");

}

SFMLView::~SFMLView()
{
}

void			SFMLView::onInit()
{
  std::cout << "-------------- INIT SFML -------------------" << std::endl;
  /* Stuff needed when loading the view */
  // _sMan->loadTextures("./Res/textureList.json");
  // _sMan->loadAnimations("./Res/perso1.json");
  // _sMan->loadAnimations("./Res/textures.json");
  /* MUST be the first things to do */
  _mainView->reset(sf::FloatRect(0,0, WIN_W, WIN_H));
  _reset = false;
  _changed = false;
  _clock->restart();
  loadMap();
  _mainPerso = new PlayerSprite(sf::String((**(_wMan->getMainPlayer()))->getName()), _textFont);
  _sMan->copySprite("perso1", *_mainPerso);
  // _mainPerso->setFont(_textFont);
  // _mainPerso->setText(sf::String((**(_wMan->getMainPlayer()))->getName()));
  // _mainPerso = (*_playerList)[0];
  _mainPerso->setPlayerZone(Map::getInstance()->getZone((**(_wMan->getMainPlayer()))->getZone())->getName());
  _mainPerso->setPlayerId((**(_wMan->getMainPlayer()))->getId());
  std::cout << "MAIN PLAYER HAS ID : " << (**(_wMan->getMainPlayer()))->getId() << std::endl;
  _mainPerso->play("default_down");
  _mainPerso->generateOffset();
  _mainPerso->setPosition((**(_wMan->getMainPlayer()))->getX() * CASE_SIZE,
  			  (**(_wMan->getMainPlayer()))->getY() * CASE_SIZE - _mainPerso->getCurrentBound()->height / 2 + 4);
  _mainView->move((**(_wMan->getMainPlayer()))->getX() * CASE_SIZE - WIN_W / 2,
  		  (**(_wMan->getMainPlayer()))->getY() * CASE_SIZE - WIN_H / 2);
  loadPlayerList();
  _inventory->initInventory();
  _stuff->initStuff(***(_wMan->getMainPlayer()));
  /* Theorically, generateOffset should be called everytime play() is called with another anim.
   But as far as i know, they are all of the same size, so offsets are OK for eveyone */
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
	{
	  try {
	    (this->*(_keyMap->at(event.key.code)))();
	  }
	  catch (std::out_of_range const &e) {
	  }
	}
    }
  /* Not used here but SFML need it to handle internal events */

  CLIENT::eState s = **(_wMan->getState());
  if (s != CLIENT::PLAYING)
    {
      switch (s)
  	{
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
    }
  if (**(_wMan->getNewPlayer()))
    {
      loadPlayerList();
      *(_wMan->getNewPlayer()) = false;
    }
  if (!_mainPerso->isMoving())
    _pressedKey = sf::Keyboard::Unknown;
  clear(sf::Color(0,0,0));
  drawView();
  _keyDelayer->update(_clock);
  // checkKeys();
  _clock->restart();
  _chat->update();
}

void			SFMLView::onResize(QResizeEvent *e)
{
  setSize(sf::Vector2u(e->size().width(), e->size().height()));
}

void			SFMLView::drawView()
{
  if (_reset)
    return;
  if (!_changed){
    reloadBackgroundSprite();
  }
  _winSprite->setTexture(_winTexture->getTexture());
  draw(*_winSprite);
  // std::cout << "drawView" << std::endl;
  for (auto it = _entities->begin(); it != _entities->end(); ++it)
    {
      (*it)->update(*_clock);
      draw(**it);
    }
  if (_mainPerso) {
    _mainPerso->moveFromServer(_mainView);
    _mainPerso->updateMoves(_clock, _mainView);
    _mainPerso->update(*_clock);
    draw(*_spriteTest);
    draw(*_mainPerso);
  }
  setView(*_mainView);
  for (auto it = _playerList->begin(); it != _playerList->end(); ++it)
    {
      if ((**(_wMan->getMainPlayer()))->getId() == ((*it)->getPlayerId()))
      	continue;
      (*it)->moveFromServer();
      (*it)->updateMoves(_clock, NULL);
      (*it)->update(*_clock);
      draw(**it);
    }
  // std::cout << "end drawView" << std::endl;
}

void			SFMLView::checkKeys()
{
  if (_mainPerso->isMoving())
    _mainPerso->updateMoves(_clock, NULL);
  setView(*_mainView);
}

void			SFMLView::loadPlayerList()
{
  std::list<AEntity *>	list = Map::getInstance()->getZone((**(_wMan->getMainPlayer()))->getZone())->getPlayers();

  for (auto it = _playerList->begin(); it != _playerList->end(); it++)
    delete *it;
  _playerList->clear();
  for (auto it = list.begin(); it != list.end(); it++)
    {
      if ((static_cast<Player*>(*it))->getId() == _mainPerso->getPlayerId())
	continue;
      _playerList->push_back(new OPlayerSprite((static_cast<Player*>(*it))->getName(), _textFont));
      _sMan->copySprite("perso1", *_playerList->back());
      _playerList->back()->setPlayerZone(Map::getInstance()->getZone((**(_wMan->getMainPlayer()))->getZone())->getName());
      _playerList->back()->setPlayerId((static_cast<Player*>(*it))->getId());
      _playerList->back()->play("default_down");
      _playerList->back()->generateOffset();
      _playerList->back()->setPosition((static_cast<Player*>(*it))->getX() * CASE_SIZE,
				       (static_cast<Player*>(*it))->getY() * CASE_SIZE - _playerList->back()->getCurrentBound()->height / 2 + 4);
    }
}

void			SFMLView::loadMap()
{
  Zone	*zone = Map::getInstance()->getZone((**(_wMan->getMainPlayer()))->getZone());
  std::list<AEntity*>	*list;

  for (int y = 0; y < zone->getSizeY(); y++)
    {
      for (int x = 0; x < zone->getSizeX(); x++)
	{
	  if (zone->getCase(x,y) && zone->getCase(x,y)->getSafe())
	    ((*_sprites)[y])[x] = _sMan->copySprite("grass");
	  else
	    ((*_sprites)[y])[x] = _sMan->copySprite("grass"); // Play rock
	  ((*_sprites)[y])[x]->play("default");
	  list = zone->getCase(x,y)->getEntities();
	  if (list && list->size() > 0)
	    {
	      for (auto it = list->begin(); it != list->end(); it++)
		{
		  if ((*it)->getEntityType() == AEntity::RESSOURCE) {
		    _entities->push_back(new RessourceSprite(static_cast<Ressource*>(*it)));
		    _sMan->copySprite(static_cast<Ressource*>(*it)->getName(), *_entities->back());
		    _entities->back()->play("default");
		    _entities->back()->setPosition(static_cast<Ressource*>(*it)->getX() * CASE_SIZE,
						   static_cast<Ressource*>(*it)->getY() * CASE_SIZE);
		  }
		}
	    }
	}
    }
  // for (auto it = cases->begin(); it != cases->end(); ++it)
  //   {
  //     std::cout << (*it)->getSafe() << std::endl;
  //   }
}

void			SFMLView::reloadBackgroundSprite()
{
  _winTexture->clear(sf::Color(0,0,0));
  for (unsigned int y = 0; y != _sprites->size(); ++y)
    {
      for (unsigned int x = 0; x != (*_sprites)[y].size(); ++x)
	{
	  (*_sprites)[y][x]->setPosition(x * CASE_SIZE, y * CASE_SIZE);
	  (*_sprites)[y][x]->update(*_clock);
	  _winTexture->draw(*((*_sprites)[y][x]));
	}
    }
  _winTexture->display();
  _changed = true;
}

void			SFMLView::reset()
{
  _reset = true;
  delete _mainPerso;
  for (auto it = _entities->begin(); it != _entities->end(); ++it)
    delete *it;
  _entities->clear();
  for (auto it = _playerList->begin(); it != _playerList->end(); ++it)
    delete *it;
  _playerList->clear();
  for (auto it = _sprites->begin(); it != _sprites->end(); it++)
    {
      for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
  	delete (it2->second);
      it->second.clear();
    }  
  _sprites->clear();
}

void			SFMLView::keyUp()
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

void			SFMLView::keyDown()
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

void			SFMLView::keyLeft()
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

void			SFMLView::keyRight()
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

void			SFMLView::keyI()
{
  if (_keyDelayer->isAvailable(sf::Keyboard::I) && !_chat->getFocused())
    {
      if (!_inventory->isVisible())
	_inventory->show();
      else
	_inventory->hide();
      _keyDelayer->addWatcher(sf::Keyboard::I, 100000);
    }
}

void			SFMLView::keyS()
{
  if (_keyDelayer->isAvailable(sf::Keyboard::S) && !_chat->getFocused())
    {
      if (!_stuff->isVisible())
	_stuff->show();
      else
	_stuff->hide();
      _keyDelayer->addWatcher(sf::Keyboard::S, 100000);
    }
}

void			SFMLView::keyJ()
{
  if (_keyDelayer->isAvailable(sf::Keyboard::J) && !_chat->getFocused())
    {
      if (!_jobMenu->isVisible())
	_jobMenu->show();
      else
	_jobMenu->hide();
      _keyDelayer->addWatcher(sf::Keyboard::J, 100000);
    }
}

void			SFMLView::keyEscape()
{
  if (_keyDelayer->isAvailable(sf::Keyboard::Escape) && !_chat->getFocused())
    {
      if (!_menu->isVisible())
	_menu->show();
      else
	_menu->hide();
      _keyDelayer->addWatcher(sf::Keyboard::Escape, 100000);
    }
}

void			SFMLView::keyReturn()
{
  if (_keyDelayer->isAvailable(sf::Keyboard::Return))
    {
      if (!_chat->getFocused())
	_chat->setFocused(true);
      else
	_chat->submitText();
      _keyDelayer->addWatcher(sf::Keyboard::Return, 100000);
    }
}

void			SFMLView::keyControl()
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
    _mainPerso->setSpeed(PX_PER_SECOND + 100);
  else
    _mainPerso->setSpeed(PX_PER_SECOND);
}

JobView			*SFMLView::getJobView(void) const { return (_job); }
