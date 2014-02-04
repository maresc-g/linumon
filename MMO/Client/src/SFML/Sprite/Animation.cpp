//
// Animation.cpp for  in /home/jourda_c/Documents/PFA/Sources
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Tue Jan 28 14:08:26 2014 cyril jourdain
// Last update Tue Feb  4 13:13:53 2014 cyril jourdain
//

#include		"SFML/Sprite/Animation.hh"
#include		<iostream>

Animation::Animation() :
  _spriteList(new std::vector<sf::IntRect*>), _currentId(0), _frameCount(0),
  _frameLenght(100000), _cFrameTime(0), _playing(false), _loopPlay(false)
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
  // if (_playing){
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
  // }
}

sf::IntRect		*Animation::getCurrentCoord() const
{
  return ((*_spriteList)[_currentId]);
}

void			Animation::addSprite(sf::IntRect const &coord)
{
  _spriteList->push_back(new sf::IntRect(coord));
  // std::cout << "pushed " << coord.left << " " << coord.top << " " << coord.width << " " << coord.height << std::endl;
  _frameCount++;
}
