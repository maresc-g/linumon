//
// PlayerSprite.hh for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Sun Feb 16 03:12:14 2014 cyril jourdain
// Last update Tue Mar 25 16:59:41 2014 cyril jourdain
//

#ifndef 		__PLAYERSPRITE_HH__
# define 		__PLAYERSPRITE_HH__

#include		"SFML/Sprite/Sprite.hh"
#include		"SFML/Clickable.hh"
#include		"Entities/Player.hh"

class			PlayerSprite : public Sprite
{
protected:
  enum	eDir
    {
      LEFT,
      DOWN,
      RIGHT,
      UP,
      NONE,
      WAITING,
      END_MOVE
    };

private:
  sf::Text		*_name;
  sf::Font		*_textFont;
  sf::Vector2f		_nameOffset;
  unsigned int		_speed;
  std::string		_playerZone;
  bool			_isInputable;
  bool			_receivedInput;
  sf::Clock		_timerBlock;

protected:
  sf::Vector2f		_deltaPos;
  eDir			_dir;
  unsigned int		_playerId;

public:
  PlayerSprite();
  PlayerSprite(sf::String const &, sf::Font *);
  virtual ~PlayerSprite();

public:
  void			setText(sf::String const &);
  void			setFont(sf::Font *);
  void			generateOffset();
  void			moveFromServer(sf::View *v = NULL);
  void			updateMoves(sf::Clock *, sf::View *);
  void			updateMoves2(sf::Clock *, sf::View *);
  bool			isMoving() const;
  void			setSpeed(unsigned int);
  void			setPlayerId(unsigned int, bool setPos = true);
  unsigned int		getPlayerId() const;
  void			setPlayerZone(std::string const &zone);
  void			setWaitingState();
  bool			isUserInputable();
  void			receivedInput();

public:
  virtual void		draw(sf::RenderTarget &, sf::RenderStates) const;
  virtual void		onClick(QMouseEvent *);

private:
  virtual void			moveUp(float, sf::View *);
  virtual void			moveDown(float, sf::View *);
  virtual void			moveLeft(float, sf::View *);
  virtual void			moveRight(float, sf::View *);
};

#endif
