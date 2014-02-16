//
// SFMLView.cpp for  in /home/jourda_c/Documents/Projets/PFA/Graphics
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Thu Sep 26 15:05:46 2013 cyril jourdain
// Last update Fri Feb 14 16:53:10 2014 cyril jourdain
//

/*

  Need to :	Add bubble when getting message (using player pos ?)
		Add border on map
		Other entities
		
		Test loading another map



 */


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
  _stuff->hide();
  _inventory->hide();
  _chat->move(0, WIN_H - _chat->size().height());
  _dir = NONE;
  _winTexture = new sf::RenderTexture();
  _winTexture->create(100*50, 100*50);
  _winSprite = new sf::Sprite();
  _changed = false;
  _mainPName = new sf::Text();
}

SFMLView::~SFMLView()
{
}

void			SFMLView::onInit()
{
  /* Stuff needed when loading the view */
  if (!_nameFont.loadFromFile("./Res/arial.ttf"))
    std::cout << "Error while loading font" << std::endl;
  //_mainPName("", _nameFont, 14);
  _mainPName->setFont(_nameFont);
  _mainPName->setCharacterSize(14);
  _clock->restart();
  _sMan->loadTextures("./Res/textureList.json");
  _sMan->loadAnimations("./Res/perso1.json");
  _sMan->loadAnimations("./Res/textures.json");
  _mainPerso = _sMan->copySprite("perso1");
  _mainPerso->setPosition(WIN_W / 2, WIN_H / 2);
  loadPlayerList();
  loadMap();
  _mainPName->setColor(sf::Color(15,15,240));
  _mainPName->setStyle(sf::Text::Bold);
  _mainPName->setString(sf::String((**(_wMan->getMainPlayer()))->getName()));
  _mainPerso->play("default_down");
  _nameOffset.x = _mainPerso->getCurrentBound()->width / 2 - _mainPName->getLocalBounds().width / 2;
  _nameOffset.y = 15;
  _mainPName->setPosition(sf::Vector2f(_mainPerso->getPosition().x + _nameOffset.x, _mainPerso->getPosition().y - _nameOffset.y));
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
  if (!_changed){
    _winTexture->clear(sf::Color(0,0,0));
    for (unsigned int y = 0; y != _sprites->size() - 1; ++y)
      {
	for (unsigned int x = 0; x != (*_sprites)[y].size() - 1; ++x)
	  {
	    // std::cout << x << "/" << y << std::endl;
	    (*_sprites)[y][x]->setPosition(x * 50, y * 50);
	    (*_sprites)[y][x]->update(*_clock);
	    _winTexture->draw(*((*_sprites)[y][x]));
	  }
      }
    _winTexture->display();
    _changed = true;
  }
  _winSprite->setTexture(_winTexture->getTexture());
  draw(*_winSprite);
  if (_mainPerso) {
    _mainPerso->update(*_clock);
    draw(*_spriteTest);
    draw(*_mainPerso);
    draw(*_mainPName);
  }
}

void			SFMLView::checkKeys()
{
  float time = _clock->getElapsedTime().asMicroseconds();

  if (_keyPressDelay > 0)
    _keyPressDelay -= time;
  else
    _keyPressDelay = 0;
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
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::I) && _keyPressDelay <= 0 && !_chat->getFocused())
    {
      if (!_inventory->isVisible()){
	_inventory->show();
	std::cout << "show inventory" << std::endl;
      }
	else {
	_inventory->hide();
	std::cout << "hide inventory" << std::endl;
      }
	_keyPressDelay = 100000;
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
  _mainPName->setPosition(sf::Vector2f(_mainPerso->getPosition().x + _nameOffset.x, _mainPerso->getPosition().y - _nameOffset.y));
  // std::cout << _mainPerso->getPosition().x << "/" << _mainPerso->getPosition().y << std::endl;
  // if (**(_wMan->getMainPlayer()))
  //   std::cout << (**(_wMan->getMainPlayer()))->getX() << std::endl;
}

void			SFMLView::loadPlayerList()
{
  // std::cout << " \nplayerList\n" << std::endl;

  // std::list<AEntity *>	list = Map::getInstance()->getZone((**(_wMan->getMainPlayer()))->getZone())->getPlayers();
  std::list<AEntity *>	list = Map::getInstance()->getZone((**(_wMan->getMainPlayer()))->getZone())->getPlayers();
  
  std::cout << "Zone name : " <<  Map::getInstance()->getZone((**(_wMan->getMainPlayer()))->getZone())->getName() << std::endl;
  std::cout << "Player number : " << list.size() << std::endl;

  for (auto it = list.begin(); it != list.end(); it++)
    {
      std::cout << (static_cast<Player*>(*it))->getX() << std::endl;
    }
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
