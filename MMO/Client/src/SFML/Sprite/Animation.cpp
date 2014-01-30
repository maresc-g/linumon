//
// Animation.cpp for  in /home/jourda_c/Documents/PFA/Sources
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Tue Jan 28 14:08:26 2014 cyril jourdain
// Last update Thu Jan 30 11:07:03 2014 cyril jourdain
//

#include		"SFML/Sprite/Animation.hh"
#include		<iostream>

Animation::Animation() :
  _spriteList(new std::vector<sf::IntRect*>), _currentId(0), _frameCount(1),
  _frameLenght(200000), _cFrameTime(0), _playing(true), _loopPlay(false)
{
  _spriteList->push_back(new sf::IntRect(0,0,100,100));
  // _spriteList->push_back(new sf::IntRect(20,0,100,100));
  // _spriteList->push_back(new sf::IntRect(40,0,100,100));
  // _spriteList->push_back(new sf::IntRect(60,0,100,100));

}

Animation::~Animation()
{
  delete _spriteList;
}

void			Animation::update(sf::Clock &clock)
{
  // Update frame
  if (_playing){
    float time = clock.getElapsedTime().asMicroseconds();

    _cFrameTime += time;
    if (_cFrameTime >= _frameLenght)
      {
	// Frame over
	std::cout << _currentId << std::endl;
	_currentId++;
	_currentId %= _frameCount;
	if (!_loopPlay && _currentId == 0)
	    _playing = false;
	_cFrameTime = 0;
      }
  }
}

sf::IntRect		*Animation::getCurrentCoord() const
{
  return ((*_spriteList)[_currentId]);
}
