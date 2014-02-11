//
// SFMLView.cpp for  in /home/jourda_c/Documents/Projets/PFA/Graphics
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Thu Sep 26 15:05:46 2013 cyril jourdain
// Last update Tue Feb 11 14:28:10 2014 cyril jourdain
//

#include		"SFML/SFMLView.hpp"
#include		"Map/Map.hh"

SFMLView::SFMLView(QWidget *parent, QPoint const &position, QSize const &size, WindowManager *w) :
  QSFMLWidget(parent, position, size), _wMan(w), _sMan(new SpriteManager()), _mainPerso(NULL),
  _clock(new sf::Clock()), _sprites(new SpriteMap), _spellBar(new SpellBarView(this, w)), _itemView(new ItemView(this, w)), _inventory(new InventoryView(this, w)), _stuff(new StuffView(this, w)),
  _chat(new ChatView(this, w))
{
  _textureTest = new sf::Texture();
  _textureTest->loadFromFile("./Res/test.png");
  _spriteTest = new sf::Sprite(*_textureTest);
  _spriteTest->setScale(4,4);
  _pos.x = WIN_W / 2;
  _pos.y = WIN_H / 2;
  _deltaPos.x = 0;
  _deltaPos.y = 0;
  _moving = false;
  _spellBar->hide();
  _itemView->hide();
  _inventory->hide();
  _chat->move(0, WIN_H - _chat->size().height());
  _dir = NONE;
}

SFMLView::~SFMLView()
{
}

void			SFMLView::onInit()
{
  /* Stuff needed when loading the view */
  _clock->restart();
  _sMan->loadTextures("./Res/textureList.json");
  _sMan->loadAnimations("./Res/perso1.json");
  _sMan->loadAnimations("./Res/textures.json");
  _mainPerso = _sMan->copySprite("perso1");
  _mainPerso->setPosition(WIN_W / 2, WIN_H / 2);
  loadPlayerList();
  sleep(1);
  loadMap();
  _mainPerso->play("default_down");
}

void			SFMLView::onUpdate()
{
  sf::Event event;
  while (pollEvent(event))
    ; /* Not used here but SFML need it to handle internal events */

  clear(sf::Color(0,0,0));
  drawView();
  checkKeys();
  _clock->restart();
}

void			SFMLView::onResize(QResizeEvent *e)
{
  setSize(sf::Vector2u(e->size().width(), e->size().height()));
}

void			SFMLView::drawView()
{
  for (int y = 0; y != _sprites->size() - 1; ++y)
    {
      for (int x = 0; x != (*_sprites)[y].size() - 1; ++x)
      	{
      	  (*_sprites)[y][x]->setPosition(x * 50, y * 50);
  	  (*_sprites)[y][x]->update(*_clock);
  	  //std::cout << x << "/" << y << std::endl;
      	  draw(*((*_sprites)[y][x]));
      	}
    }
  if (_mainPerso) {
    _mainPerso->update(*_clock);
    draw(*_spriteTest);
    draw(*_mainPerso);
  }
  // (*_sprites)[0][0]->play("down");
  // (*_sprites)[0][0]->update(*_clock);;  
  // (*_sprites)[0][0]->setPosition(_mainPerso->getPosition().x + 50, _mainPerso->getPosition().y + 50);
  //std::cout << x << "/" << y << std::endl;
}

void			SFMLView::checkKeys()
{
  float time = _clock->getElapsedTime().asMicroseconds();
  float px = time * PX_PER_SECOND / 1000000;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !_moving)
    {
      _pos.y += 50;
      _deltaPos.y = 50;
      _moving = true;
      _dir = DOWN;
      Client::getInstance()->move(CLIENT::DOWN);
      _mainPerso->play("down");
    }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !_moving)
    {
      _pos.y -= 50;
      _deltaPos.y = -50;
      _moving = true;
      _dir = UP;
      Client::getInstance()->move(CLIENT::UP);
      _mainPerso->play("up");
    }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !_moving)
    {
      _pos.x -= 50;
      _deltaPos.x = -50;
      _moving = true;
      _dir = LEFT;
      Client::getInstance()->move(CLIENT::LEFT);
      _mainPerso->play("left");
    }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !_moving)
    {
      _pos.x += 50;
      _deltaPos.x = 50;
      _moving = true;
      _dir = RIGHT;
      Client::getInstance()->move(CLIENT::RIGHT);
      _mainPerso->play("right");
    }
  if (_moving)
    moveMainPerso(time);
  setView(*_mainView);
}

void			SFMLView::moveMainPerso(float const elapsedTime)
{
  float px = elapsedTime * PX_PER_SECOND / 1000000;

  if (_dir == eDir::DOWN)
    {
      _mainView->move(0, px);
      _mainPerso->move(0, px);
      _deltaPos.y -= px;
      if (_deltaPos.y < 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	_deltaPos.y += 50;
      if (_deltaPos.y <= 0 && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
	  _mainView->move(0, _deltaPos.y);
	  _mainPerso->move(0, _deltaPos.y);
	  _deltaPos.y = 0;
	  _moving = false;
	  _dir = eDir::NONE;
	  _mainPerso->play("default_down");
	}
    }
  else if (_deltaPos.y < 0)
    {
      _mainView->move(0, -px);
      _mainPerso->move(0, -px);
      _deltaPos.y += px;
      if (_deltaPos.y > 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	_deltaPos.y -= 50;
      if (_deltaPos.y >= 0 && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
	  _mainView->move(0, _deltaPos.y);
	  _mainPerso->move(0, _deltaPos.y);
	  _deltaPos.y = 0;
	  _moving = false;
	  _dir = eDir::NONE;
	  _mainPerso->play("default_up");
	}
    }
  else if (_deltaPos.x > 0)
    {
      _mainView->move(px, 0);
      _mainPerso->move(px, 0);
      _deltaPos.x -= px;
      if (_deltaPos.x < 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	_deltaPos.x += 50;
      if (_deltaPos.x <= 0 && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
	  _mainView->move(_deltaPos.x, 0);
	  _mainPerso->move(_deltaPos.x, 0);
	  _deltaPos.x = 0;
	  _moving = false;
	  _dir = eDir::NONE;
	  _mainPerso->play("default_right");
	}
    }
  else if (_deltaPos.x < 0)
    {
      _mainView->move(-px, 0);
      _mainPerso->move(-px, 0);
      _deltaPos.x += px;
      if (_deltaPos.x > 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	_deltaPos.x -= 50;
      if (_deltaPos.x >= 0 && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
	  _mainView->move(_deltaPos.x, 0);
	  _mainPerso->move(_deltaPos.x, 0);
	  _deltaPos.x = 0;
	  _moving = false;
	  _dir = eDir::NONE;
	  _mainPerso->play("default_left");
	}
    }
  // std::cout << _mainPerso->getPosition().x << "/" << _mainPerso->getPosition().y << std::endl;
  // if (**(_wMan->getMainPlayer()))
  //   std::cout << (**(_wMan->getMainPlayer()))->getX() << std::endl;
}

void			SFMLView::loadPlayerList()
{
  // std::cout << " \nplayerList\n" << std::endl;

  // std::list<AEntity *>	list = Map::getInstance()->getZone((**(_wMan->getMainPlayer()))->getZone())->getPlayers();
  // std::list<AEntity *>	list = Map::getInstance()->getZone((**(_wMan->getMainPlayer()))->getZone())->getPlayers();
  
  // std::cout << Map::getInstance()->getZone((**(_wMan->getMainPlayer()))->getZone()) << std::endl;

  // std::cout << "get" << std::endl;

  // for (auto it = list.begin(); it != list.end(); it++)
  //   {
  //     std::cout << (static_cast<Player*>(*it))->getX() << std::endl;
  //   }
}

void			SFMLView::loadMap()
{
  Zone	*zone = Map::getInstance()->getZone((**(_wMan->getMainPlayer()))->getZone());

  for (int y = 0; y != zone->getSizeX(); y++)
    {
      for (int x = 0; x != zone->getSizeY(); x++)
	{
	  ((*_sprites)[y])[x] = _sMan->copySprite("grass");
	  ((*_sprites)[y])[x]->play("default");
	}
    }
  // for (auto it = cases->begin(); it != cases->end(); ++it)
  //   {
  //     std::cout << (*it)->getSafe() << std::endl;
  //   }
}
