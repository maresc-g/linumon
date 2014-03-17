//
// RessourceSprite.hh for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Wed Feb 26 14:50:34 2014 cyril jourdain
// Last update Sun Mar 16 18:28:06 2014 cyril jourdain
//

#ifndef 		__RESSOURCESPRITE_HH__
# define 		__RESSOURCESPRITE_HH__

#include		"Entities/Ressource.hh"
#include		"SFML/Sprite/Sprite.hh"

class			RessourceSprite : public Sprite
{
private:
  Ressource		*_resPtr;

public:
  RessourceSprite(Ressource *);
  virtual ~RessourceSprite();

public:
  virtual void		draw(sf::RenderTarget &, sf::RenderStates) const;
  virtual void		onClick(QMouseEvent *);
  virtual bool		isVisible();
  bool			isGather();

};

#endif
