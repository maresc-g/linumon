//
// SFMLView.cpp for  in /home/jourda_c/Documents/Projets/PFA/Graphics
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Thu Sep 26 15:05:46 2013 cyril jourdain
// Last update Mon Feb 10 13:26:37 2014 cyril jourdain
//

#include		"SFML/SFMLView.hpp"

SFMLView::SFMLView(QWidget *parent, QPoint const &position, QSize const &size, WindowManager *w) :
  QSFMLWidget(parent, position, size), _wMan(w), _sMan(new SpriteManager()), _mainPerso(NULL),
  _clock(new sf::Clock()), _spellBar(new SpellBarView(this, w)), _itemView(new ItemView(this, w)),
  _inventory(new InventoryView(this, w)), _stuff(new StuffView(this, w)),
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
  _mainPerso = _sMan->copySprite("perso1");
  _mainPerso->setPosition(WIN_W / 2, WIN_H / 2);
}

void			SFMLView::onUpdate()
{
  sf::Event event;
  while (pollEvent(event))
    ; /* Not used here but SFML need it to handle internal events */

  clear(sf::Color(15, 150, 30));
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
  _mainPerso->play("down");
  if (_mainPerso) {
    _mainPerso->update(*_clock);
    draw(*_spriteTest);
    draw(*_mainPerso);
  }
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
      Client::getInstance()->move(CLIENT::DOWN);
    }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !_moving)
    {
      _pos.y -= 50;
      _deltaPos.y = -50;
      _moving = true;
      Client::getInstance()->move(CLIENT::UP);
    }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !_moving)
    {
      _pos.x -= 50;
      _deltaPos.x = -50;
      _moving = true;
      Client::getInstance()->move(CLIENT::LEFT);
    }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !_moving)
    {
      _pos.x += 50;
      _deltaPos.x = 50;
      _moving = true;
      Client::getInstance()->move(CLIENT::RIGHT);
    }
  if (_moving)
    moveMainPerso(time);
  setView(*_mainView);
}

void			SFMLView::moveMainPerso(float const elapsedTime)
{
  float px = elapsedTime * PX_PER_SECOND / 1000000;

  if (_deltaPos.y > 0)
    {
      _mainView->move(0, px);
      _mainPerso->move(0, px);
      _deltaPos.y -= px;
      if (_deltaPos.y <= 0)
	{
	  _mainView->move(0, _deltaPos.y);
	  _mainPerso->move(0, _deltaPos.y);
	  _deltaPos.y = 0;
	  _moving = false;
	}
    }
  if (_deltaPos.y < 0)
    {
      _mainView->move(0, -px);
      _mainPerso->move(0, -px);
      _deltaPos.y += px;
      if (_deltaPos.y >= 0)
	{
	  _mainView->move(0, _deltaPos.y);
	  _mainPerso->move(0, _deltaPos.y);
	  _deltaPos.y = 0;
	  _moving = false;
	}
    }
  if (_deltaPos.x > 0)
    {
      _mainView->move(px, 0);
      _mainPerso->move(px, 0);
      _deltaPos.x -= px;
      if (_deltaPos.x <= 0)
	{
	  _mainView->move(_deltaPos.x, 0);
	  _mainPerso->move(_deltaPos.x, 0);
	  _deltaPos.x = 0;
	  _moving = false;
	}
    }
  if (_deltaPos.x < 0)
    {
      _mainView->move(-px, 0);
      _mainPerso->move(-px, 0);
      _deltaPos.x += px;
      if (_deltaPos.x >= 0)
	{
	  _mainView->move(_deltaPos.x, 0);
	  _mainPerso->move(_deltaPos.x, 0);
	  _deltaPos.x = 0;
	  _moving = false;
	}
    }
  std::cout << _mainPerso->getPosition().x << "/" << _mainPerso->getPosition().y << std::endl;
  // if (**(_wMan->getMainPlayer()))
  //   std::cout << (**(_wMan->getMainPlayer()))->getX() << std::endl;
}
