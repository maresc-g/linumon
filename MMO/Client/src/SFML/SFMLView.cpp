//
// SFMLView.cpp for  in /home/jourda_c/Documents/Projets/PFA/Graphics
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Thu Sep 26 15:05:46 2013 cyril jourdain
// Last update Thu Feb  6 12:36:41 2014 cyril jourdain
//

#include		"SFML/SFMLView.hpp"

SFMLView::SFMLView(QWidget *parent, QPoint const &position, QSize const &size, WindowManager *w) :
  QSFMLWidget(parent, position, size), _wMan(w), _sMan(new SpriteManager()), _mainPerso(NULL),
  _clock(new sf::Clock())
{
  _textureTest = new sf::Texture();
  _textureTest->loadFromFile("./Res/test.png");
  _spriteTest = new sf::Sprite(*_textureTest);
  _spriteTest->setScale(4,4);
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
    ;
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

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
      _mainView->move(0,px);
      _mainPerso->move(0,px);
    }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
      _mainView->move(0,-px);
      _mainPerso->move(0,-px);
    }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
      _mainView->move(-px,0);
      _mainPerso->move(-px,0);
    }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
      _mainView->move(px,0);
      _mainPerso->move(px,0);
    }
  setView(*_mainView);
}
