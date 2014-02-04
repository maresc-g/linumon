//
// SFMLView.cpp for  in /home/jourda_c/Documents/Projets/PFA/Graphics
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Thu Sep 26 15:05:46 2013 cyril jourdain
// Last update Tue Feb  4 13:56:00 2014 cyril jourdain
//

#include		"SFML/SFMLView.hpp"

SFMLView::SFMLView(QWidget *parent, QPoint const &position, QSize const &size, WindowManager *w) :
  QSFMLWidget(parent, position, size), _wMan(w), _sMan(new SpriteManager())
{
  _clock = new sf::Clock();
  _sprite = NULL;
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
  _sprite = _sMan->copySprite("perso1");
}

void			SFMLView::onUpdate()
{
  _sprite->play("down");
  clear(sf::Color(15, 150, 30));
  /* Draw stuff here */
  if (_sprite) {
    _sprite->update(*_clock);
    _clock->restart();
    draw(*_sprite);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    _sprite->move(0,10);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    _sprite->move(0,-10);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    _sprite->move(-10,0);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    _sprite->move(10,0);
  /* This is only for test purpose. But remember to add  :
     x pixels by loop (check loop time)
   */
}
