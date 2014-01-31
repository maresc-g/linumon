//
// Sprite.cpp for  in /home/jourda_c/Documents/PFA/Sources
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Tue Jan 28 14:19:12 2014 cyril jourdain
// Last update Thu Jan 30 11:08:08 2014 cyril jourdain
//

#include		"SFML/Sprite/Sprite.hh"

Sprite::Sprite():
  sf::Drawable(), sf::Transformable(), _texture(NULL),
  _anim(new std::map<std::string, Animation *>), _vertex(new sf::Vertex [4]),
  _current("")
{
  // _vertex[0].texCoords = sf::Vector2f(0,0);
  // _vertex[1].texCoords = sf::Vector2f(0,100);
  // _vertex[2].texCoords = sf::Vector2f(100,100);
  // _vertex[3].texCoords = sf::Vector2f(100,0);
  // _vertex[0].position = sf::Vector2f(0,0);
  // _vertex[1].position = sf::Vector2f(0,100);
  // _vertex[2].position = sf::Vector2f(100,100);
  // _vertex[3].position = sf::Vector2f(100,0);
  _vertex[0].color = sf::Color(255,255,255);
  _vertex[1].color = sf::Color(255,255,255);
  _vertex[2].color = sf::Color(255,255,255);
  _vertex[3].color = sf::Color(255,255,255);
  _anim->insert(std::pair<std::string, Animation*>("toto", new Animation()));
  _current = "toto";
}

Sprite::~Sprite()
{
}

void			Sprite::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  if (_texture && _vertex) {
    states.texture = _texture;
    states.transform *= getTransform();
    target.draw(_vertex, 4, sf::Quads, states);
  }
}

void			Sprite::update(sf::Clock &clock)
{
  sf::IntRect		*frame;

  if (_current != "" && (*_anim)[_current])
    {
      (*_anim)[_current]->update(clock); /* NOT WORKING */
      frame = (*_anim)[_current]->getCurrentCoord();
      _vertex[0].texCoords = sf::Vector2f(frame->left, frame->top);
      _vertex[1].texCoords = sf::Vector2f(frame->left, frame->top + frame->height);
      _vertex[2].texCoords = sf::Vector2f(frame->left + frame->width, frame->top + frame->height);
      _vertex[3].texCoords = sf::Vector2f(frame->left + frame->width, frame->top);
      _vertex[0].position = sf::Vector2f(0,0);
      _vertex[1].position = sf::Vector2f(0,frame->height);
      _vertex[2].position = sf::Vector2f(frame->width,frame->height);
      _vertex[3].position = sf::Vector2f(frame->width,0);
    }
}

void			Sprite::setTexture(sf::Texture *text)
{
  _texture = text;
}

void			Sprite::loadFromFile(std::string const path)
{
  
}
