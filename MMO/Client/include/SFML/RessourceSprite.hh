//
// RessourceSprite.hh for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Wed Feb 26 14:50:34 2014 cyril jourdain
// Last update Mon Mar 24 13:04:24 2014 cyril jourdain
//

#ifndef 		__RESSOURCESPRITE_HH__
# define 		__RESSOURCESPRITE_HH__

#include		"Entities/Ressource.hh"
#include		"SFML/Sprite/Sprite.hh"
#include		"Qt/WindowManager.hh"

class			RessourceSprite : public Sprite
{
private:
  Ressource		*_resPtr;
  WindowManager		*_wMan;
  unsigned int		_id;

public:
  RessourceSprite(Ressource *, WindowManager *);
  virtual ~RessourceSprite();

public:
  virtual void		draw(sf::RenderTarget &, sf::RenderStates) const;
  virtual void		onClick(QMouseEvent *);
  virtual bool		isVisible();

};

#endif
