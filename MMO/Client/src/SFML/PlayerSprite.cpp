//
// PlayerSprite.cpp for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Sun Feb 16 04:20:51 2014 cyril jourdain
// Last update Sun Feb 16 04:20:51 2014 cyril jourdain
//

#include		"SFML/PlayerSprite.hh"

PlayerSprite::PlayerSprite() : Sprite(),
  _name(new sf::Text()), _textFont(NULL), _nameOffset(sf::Vector2f(0,0))
{
  _name->setString("!_uninitialized");
  _name->setCharacterSize(14);
  _name->setColor(sf::Color(15,15,240));
  _name->setStyle(sf::Text::Bold);

}

PlayerSprite::PlayerSprite(sf::String const &name, sf::Font *font) : Sprite(),
  _name(new sf::Text()), _textFont(font), _nameOffset(sf::Vector2f(0,0))
{
  _name->setString(name);
  _name->setFont(*_textFont);
  _name->setCharacterSize(14);
  _name->setColor(sf::Color(15,15,240));
  _name->setStyle(sf::Text::Bold);

}

PlayerSprite::~PlayerSprite()
{
  delete _name;
}

void			PlayerSprite::setText(sf::String const &name)
{
  _name->setString(name);
  _name->setCharacterSize(14);
  _name->setColor(sf::Color(15,15,240));
  _name->setStyle(sf::Text::Bold);
}

void			PlayerSprite::setFont(sf::Font *font)
{
  _textFont = font;
  _name->setFont(*_textFont);
}

void			PlayerSprite::generateOffset()
{
  if (getCurrentBound())
    {
      _nameOffset.x = getCurrentBound()->width / 2 - _name->getLocalBounds().width / 2;
      _nameOffset.y = -15;
      _name->setPosition(sf::Vector2f(_nameOffset.x, _nameOffset.y));
    }
  else
    {
      std::cout << "Warning: generateOffset in PlayerSprite - Cannot get bounds. play() might not have been called yet" << std::endl;
    }
}

void			PlayerSprite::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  if (_texture && _vertex) {
    states.texture = _texture;
    states.transform *= getTransform();
    target.draw(_vertex, 4, sf::Quads, states);
    states.texture = NULL;
    target.draw(*_name, states);
  }
}
