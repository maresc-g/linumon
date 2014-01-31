//
// SFMLView.cpp for  in /home/jourda_c/Documents/Projets/PFA/Graphics
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Thu Sep 26 15:05:46 2013 cyril jourdain
// Last update Wed Jan 29 14:42:08 2014 cyril jourdain
//

#include		"SFML/SFMLView.hpp"

SFMLView::SFMLView(QWidget *parent, QPoint const &position, QSize const &size, WindowManager *w) :
  QSFMLWidget(parent, position, size), _wMan(w)
{
  _texture = new sf::Texture();
  _sprite = new Sprite();
  _clock = new sf::Clock();
}

SFMLView::~SFMLView()
{
}

void			SFMLView::onInit()
{
  /* Stuff needed when loading the view */

  _texture->loadFromFile("./res/back_button.png");
  if (!_texture)
    exit(-1);
  _sprite->setTexture(_texture);
  _clock->restart();
  //std::cout << _sprite1->getTexture() << std::endl;
}

void			SFMLView::onUpdate()
{
  clear(sf::Color(99, 99, 30));
  /* Draw stuff here */
  _sprite->update(*_clock);
  _clock->restart();
  draw(*_sprite);
}
