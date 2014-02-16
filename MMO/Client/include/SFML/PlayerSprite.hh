//
// PlayerSprite.hh for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Sun Feb 16 03:12:14 2014 cyril jourdain
// Last update Sun Feb 16 03:30:27 2014 cyril jourdain
//

#ifndef 		__PLAYERSPRITE_HH__
# define 		__PLAYERSPRITE_HH__

#include		"SFML/Sprite/Sprite.hh"

class			PlayerSprite : public Sprite
{
private:
  sf::Text		*_name;
  sf::Font		*_textFont;
  sf::Vector2f		_nameOffset;

public:
  PlayerSprite();
  PlayerSprite(sf::String const &, sf::Font *);
  virtual ~PlayerSprite();

public:
  void			setText(sf::String const &);
  void			setFont(sf::Font *);
  void			generateOffset();

public:
  virtual void		draw(sf::RenderTarget &, sf::RenderStates) const;
};

#endif
