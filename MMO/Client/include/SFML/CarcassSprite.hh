//
// CarcassSprite.hh for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Mon Mar 24 16:51:55 2014 cyril jourdain
// Last update Mon Mar 24 17:49:27 2014 cyril jourdain
//

#ifndef 		__CARCASSSPRITE_HH__
# define 		__CARCASSSPRITE_HH__

#include		"Entities/Carcass.hh"
#include		"SFML/Sprite/Sprite.hh"
#include		"Qt/WindowManager.hh"

class			CarcassSprite : public Sprite
{
private:
  Carcass		*_resPtr;
  WindowManager		*_wMan;
  unsigned int		_id;

public:
  CarcassSprite(Carcass *, WindowManager *);
  virtual ~CarcassSprite();

public:
  virtual void		draw(sf::RenderTarget &, sf::RenderStates) const;
  virtual void		onClick(QMouseEvent *);
  unsigned int		getCarcassId() const;
};

#endif
