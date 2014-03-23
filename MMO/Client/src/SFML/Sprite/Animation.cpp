//
// Animation.cpp for  in /home/jourda_c/Documents/PFA/Sources
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Tue Jan 28 14:08:26 2014 cyril jourdain
// Last update Sun Mar 23 16:19:32 2014 cyril jourdain
//

#include		"SFML/Sprite/Animation.hh"
#include		<iostream>

Animation::Animation() :
  _spriteList(new std::vector<Frame*>), _initialPos(new sf::Vector2f()), _currentId(0), _frameCount(0),
  _frameLenght(160000), _cFrameTime(0), _playing(false), _loopPlay(true)
{
}

Animation::Animation(Animation const &other) :
  _spriteList(new std::vector<Frame*>)
{
  for (auto it = other._spriteList->begin(); it != other._spriteList->end(); it++)
    _spriteList->push_back(new Frame(**it));
  _currentId = 0;
  _frameCount = other._frameCount;
  _frameLenght = other._frameLenght;
  _cFrameTime = 0;
  _playing = false;
  _loopPlay = other._loopPlay;
}

Animation::~Animation()
{
  for (auto it = _spriteList->begin(); it != _spriteList->end(); ++it)
    delete *it;
  delete _spriteList;
}

void			Animation::update(sf::Clock &clock)
{
  // Update frame
  if (_loopPlay && !_playing)
    _playing = true;
  if (_playing){
    float time = clock.getElapsedTime().asMicroseconds();
    _cFrameTime += time;
    if (_cFrameTime >= _frameLenght)
      {
	// Frame over
	_currentId++;
	_currentId %= _frameCount;
	if (!_loopPlay && _currentId == 0)
	  _playing = false;
	_cFrameTime = 0;
      }
  }
}

sf::Vector2f		*Animation::getFrameOffset() const
{
  return ((*_spriteList)[_currentId]->getOffset());
}

sf::IntRect		*Animation::getCurrentCoord() const
{
  return ((*_spriteList)[_currentId]->getSpriteRect());
}

void			Animation::addSprite(sf::IntRect const &coord, sf::Vector2f const &offset)
{
  _spriteList->push_back(new Frame(coord, offset));
  _frameCount++;
}

void			Animation::play(bool p)
{
  _playing = p;
}

void			Animation::setFrameLength(int len)
{
  _frameLenght = len;
}

bool			Animation::isEnded() const
{
  if (_playing)
    return false;
  return true;
}

void			Animation::setLoopPlay(bool loop)
{
  _loopPlay = loop;
}

void	Animation::printFrameId()
{
  // std::cout << _currentId << std::endl;
  // if (_over)
  //   std::cout << "Frame [" << _currentId << "] is over" << std::endl;
}
