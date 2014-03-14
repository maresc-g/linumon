//
// OPlayerSprite.hh for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Tue Feb 25 14:10:55 2014 cyril jourdain
// Last update Fri Mar 14 15:29:27 2014 cyril jourdain
//

#ifndef 		__OPLAYERSPRITE_HH__
# define 		__OPLAYERSPRITE_HH__

#include		"SFML/PlayerSprite.hh"

class			OPlayerSprite : public PlayerSprite
{
public:
  OPlayerSprite(sf::String const &, sf::Font *);
  virtual ~OPlayerSprite();

private:
  virtual void			moveUp(float, sf::View *v = NULL);
  virtual void			moveDown(float, sf::View *v = NULL);
  virtual void			moveLeft(float, sf::View *v = NULL);
  virtual void			moveRight(float, sf::View *v = NULL);
public:
  virtual void			onClick(QMouseEvent *);
};

#endif
