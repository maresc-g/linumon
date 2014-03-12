//
// Animation.hh for  in /home/jourda_c/Documents/PFA/Sources
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Tue Jan 28 14:08:20 2014 cyril jourdain
// Last update Tue Mar 11 23:45:22 2014 cyril jourdain
//

#ifndef 		__ANIMATION_HH__
# define 		__ANIMATION_HH__

#include		<vector>
#include		<SFML/Graphics.hpp>
#include		<SFML/System.hpp>
#include		"SFML/Sprite/Frame.hh"

#define			PX_PER_SECOND 100

class			Animation
{
private /* attributs */ :
  std::vector<Frame *>	*_spriteList;
  sf::Vector2f		*_initialPos;
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
  sf::Vector2f		*getFrameOffset() const;
void			addSprite(sf::IntRect const &coord, sf::Vector2f const &offset);
  void			play(bool);
  void			setFrameLength(int len); // µs
  bool			isEnded() const;
  void			setLoopPlay(bool);

  void			printFrameId();
};

#endif
