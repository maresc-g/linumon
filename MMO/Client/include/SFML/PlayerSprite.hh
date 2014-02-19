//
// PlayerSprite.hh for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Sun Feb 16 03:12:14 2014 cyril jourdain
// Last update Mon Feb 17 14:11:05 2014 cyril jourdain
//

#ifndef 		__PLAYERSPRITE_HH__
# define 		__PLAYERSPRITE_HH__

#include		"SFML/Sprite/Sprite.hh"

class			PlayerSprite : public Sprite
{
private:
  enum	eDir
    {
      LEFT,
      DOWN,
      RIGHT,
      UP,
      NONE
    };

private:
  sf::Text		*_name;
  sf::Font		*_textFont;
  sf::Vector2f		_nameOffset;
  sf::Vector2f		_pos;
  sf::Vector2f		_deltaPos;
  eDir			_dir;

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
  void			moveUp();
  void			moveDown();
  void			moveLeft();
  void			moveRight();
  void			updateMoves(sf::Clock *, sf::View *);
  bool			isMoving() const;
};

#endif
