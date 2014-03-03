//
// Positionable.hh for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Fri Feb 28 13:22:29 2014 cyril jourdain
// Last update Fri Feb 28 19:02:22 2014 cyril jourdain
//

#ifndef 		__POSITIONABLE_HH__
# define 		__POSITIONABLE_HH__

#include		<SFML/System.hpp>

class			Clickable
{
protected:
  sf::Vector2f		_pos;

public:
  Clickable();
  virtual ~Clickable();

public:
  sf::Vector2f	const	*getPos() const;
  void			setPos(float x, float y);
  virtual bool		isClicked(float const x, float const y) const = 0;
  virtual void		onClick() = 0;
};

#endif


// ALL SPRITE HAVE TO BE CLICKABLE
