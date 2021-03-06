//
// Sprite.cpp for  in /home/jourda_c/Documents/PFA/Sources
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Tue Jan 28 14:19:12 2014 cyril jourdain
// Last update Wed Mar 26 14:32:50 2014 cyril jourdain
//

#include		<stdexcept>
#include		"SFML/Sprite/Sprite.hh"
#include		"SFML/defines.hh"

Sprite::Sprite():
  sf::Drawable(), sf::Transformable(), Clickable(), _texture(NULL),
  _anim(new std::map<std::string, Animation *>), _vertex(new sf::Vertex [4]),
  _current(""), _playing(false), _visible(true), _name("")
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
  _playCount = 0;
}

Sprite::Sprite(Sprite const &other) :
  sf::Drawable(), sf::Transformable(), Clickable(),
  _texture(other._texture), _anim(new std::map<std::string, Animation *>)
{
  for (auto it = other._anim->begin(); it != other._anim->end(); it++)
    {
      _anim->insert(std::pair<std::string, Animation*>(it->first, new Animation(*(it->second))));
    }
  _vertex = new sf::Vertex[4]();
  _vertex[0].color = sf::Color(255,255,255);
  _vertex[1].color = sf::Color(255,255,255);
  _vertex[2].color = sf::Color(255,255,255);
  _vertex[3].color = sf::Color(255,255,255);
  _current = "";
  _playing = false;
  _visible = other._visible;
  _texture = other._texture;
  _name = other._name;
  _playCount = 0;
  // Remember to add other things
}

Sprite			&Sprite::operator=(Sprite const &other)
{
  for (auto it = _anim->begin(); it != _anim->end(); it++)
    delete it->second;
  _anim->clear();
  for (auto it = other._anim->begin(); it != other._anim->end(); it++)
    {
      _anim->insert(std::pair<std::string, Animation*>(it->first, new Animation(*(it->second))));
    }
  _vertex = new sf::Vertex[4]();
  _vertex[0].color = sf::Color(255,255,255);
  _vertex[1].color = sf::Color(255,255,255);
  _vertex[2].color = sf::Color(255,255,255);
  _vertex[3].color = sf::Color(255,255,255);
  _current = other._current;
  _playing = other._playing;
  _texture = other._texture;
  _name = other._name;
  _playCount = 0;
  return *this;
}

Sprite::~Sprite()
{
}

Animation		*Sprite::operator[](std::string const &id)
{
  try {
    return (*_anim).at(id);
  } catch (std::out_of_range const &e) {
    std::cerr << "operator[] in Sprite. No animation named" << id << std::endl;
    return NULL;
  }
}

void			Sprite::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  if (_visible && _texture && _vertex && _current != "" && !(*_anim)[_current]->isEnded()) {
    states.texture = _texture;
    states.transform *= getTransform();
    target.draw(_vertex, 4, sf::Quads, states);
  }
}

void			Sprite::update(sf::Clock &)
{
  sf::IntRect		*frame;

  if (_current != "" && (*_anim)[_current] && _playing && !(*_anim)[_current]->isEnded())
    {
      (*_anim)[_current]->update(_clock); /* NOT WORKING */
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
  else
    _current = "";
  _clock.restart();
}

bool			Sprite::isClicked(float const x, float const y) const
{
  if (_visible && x >= getPosition().x && x <= getPosition().x + getCurrentBound()->width && y >= getPosition().y
      && y <= getPosition().y + getCurrentBound()->height)
    return true;
  return false;
}

void			Sprite::onClick(QMouseEvent *)
{
  std::cout << _current << " CLICKED" << std::endl;
}

void			Sprite::setTexture(sf::Texture *text)
{
  _texture = text;
}

void			Sprite::loadFromFile(std::string const)
{
  
}

void			Sprite::addAnim(std::string const &name)
{
  _anim->insert(std::pair<std::string, Animation*>(name, new Animation()));
  // std::cout << name << std::endl;
}

void			Sprite::play(std::string const &name)
{
  if (_current == "" || (*_anim)[_current]->isEnded())
    {
      _clock.restart();
      _playCount++;
    }
  _current = name;
  _playing = true;
  if (_current != "")
    (*_anim)[_current]->play(true);
}

void			Sprite::play()
{
  if (_current != "")
    {
      _playing = true;
      (*_anim)[_current]->play(true);
    }
}

void			Sprite::pause()
{
  _playing = false;
}

void			Sprite::stop()
{
  _playing = false;
  if (_current != "")
    (*_anim)[_current]->play(false);
  _current = "";
}

void			Sprite::print()
{
  for (auto it = _anim->begin(); it != _anim->end(); it++)
    {
      std::cout << "{" << it->first << "}" << std::endl;
    }
}

void			Sprite::setName(std::string const &name)
{
  _name = name;
}

std::string const &	Sprite::getName() const
{
  return _name;
}

void			Sprite::setVisible(bool val)
{
  _visible = val;
}

std::string		Sprite::getLastPlayed()
{
  return _current;
}

sf::IntRect		*Sprite::getCurrentBound() const
{
  if (_current != "" && (*_anim)[_current] && _playing)
    return ((*_anim)[_current]->getCurrentCoord());
  return NULL;
}

bool			Sprite::isAnimFinished() const
{
  if (!(*_anim)[_current])
    return true;
  if ((*_anim)[_current] && (*_anim)[_current]->isEnded())
    return true;
  return false;
}

sf::Vector2f		*Sprite::getCurrentOffset() const
{
  if (_current != "" && (*_anim)[_current])
    return _anim->at(_current)->getFrameOffset();
  return NULL;
}

unsigned int		Sprite::getPlayCount() const
{
  return _playCount;
}
