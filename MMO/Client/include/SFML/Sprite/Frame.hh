//
// Frame.hh for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Tue Mar 11 16:21:02 2014 cyril jourdain
// Last update Tue Mar 11 21:32:39 2014 cyril jourdain
//

#ifndef 		__FRAME_HH__
# define 		__FRAME_HH__

#include		<SFML/Graphics.hpp>

class			Frame
{
private:
  sf::IntRect		*_sprite;
  sf::Vector2f		*_offset;

public:
  Frame(sf::IntRect const &sprite, sf::Vector2f const &offset);
  Frame(Frame const &);
  virtual ~Frame();

public:
  sf::IntRect		*getSpriteRect() const;
  sf::Vector2f		*getOffset() const;
};

#endif
