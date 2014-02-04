//
// Animation.hh for  in /home/jourda_c/Documents/PFA/Sources
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Tue Jan 28 14:08:20 2014 cyril jourdain
// Last update Tue Feb  4 12:49:15 2014 cyril jourdain
//

#ifndef 		__ANIMATION_HH__
# define 		__ANIMATION_HH__

#include		<vector>
#include		<SFML/Graphics.hpp>
#include		<SFML/System.hpp>

class			Animation
{
private /* attributs */ :
  std::vector<sf::IntRect *>	*_spriteList;
  unsigned int		_currentId;
  unsigned int		_frameCount;
  unsigned int		_frameLenght;
  unsigned int		_cFrameTime;
  bool			_playing;
  bool			_loopPlay;

public /* class specific */ :
  Animation();
  Animation(Animation const &);
  virtual ~Animation();

public /* methods */ :
  void			update(sf::Clock &);
  sf::IntRect		*getCurrentCoord() const;
  void			addSprite(sf::IntRect const &coord);
};

#endif
