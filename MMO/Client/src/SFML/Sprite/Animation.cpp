//
// Animation.cpp for  in /home/jourda_c/Documents/PFA/Sources
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Tue Jan 28 14:08:26 2014 cyril jourdain
// Last update Sun Mar  9 01:00:27 2014 cyril jourdain
//

#include		"SFML/Sprite/Animation.hh"
#include		<iostream>

Animation::Animation() :
  _spriteList(new std::vector<sf::IntRect*>), _currentId(0), _frameCount(0),
  _frameLenght(120000), _cFrameTime(0), _playing(false), _loopPlay(true)
{
  //_spriteList->push_back(new sf::IntRect(0,0,100,100));
  // _spriteList->push_back(new sf::IntRect(20,0,100,100));
  // _spriteList->push_back(new sf::IntRect(40,0,100,100));
  // _spriteList->push_back(new sf::IntRect(60,0,100,100));

}

Animation::Animation(Animation const &other) :
  _spriteList(new std::vector<sf::IntRect*>)
{
  for (auto it = other._spriteList->begin(); it != other._spriteList->end(); it++)
    _spriteList->push_back(new sf::IntRect(**it));
  _currentId = 0;
  _frameCount = other._frameCount;
  _frameLenght = other._frameLenght;
  _cFrameTime = 0;
  _playing = false;
  _loopPlay = other._loopPlay;
}

Animation::~Animation()
{
  delete _spriteList;
}

void			Animation::update(sf::Clock &clock)
{
  // Update frame
  if (_frameCount == 1 && !_playing)
    _playing = true;
  if (_playing){
    float time = clock.getElapsedTime().asMicroseconds();
    _cFrameTime += time;
    if (_cFrameTime >= _frameLenght)
      {
	// Frame over
	_currentId++;
	_currentId %= _frameCount;
	if (!_loopPlay && _currentId == 0 && _frameCount > 1)
	  _playing = false;
	_cFrameTime = 0;
      }
  }
}

sf::IntRect		*Animation::getCurrentCoord() const
{
  return ((*_spriteList)[_currentId]);
}

void			Animation::addSprite(sf::IntRect const &coord)
{
  _spriteList->push_back(new sf::IntRect(coord));
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
