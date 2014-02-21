//
// PlayerSprite.cpp for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Sun Feb 16 04:20:51 2014 cyril jourdain

//

#include		"SFML/PlayerSprite.hh"
#include		"Client.hh"
#include		"Map/Map.hh"


PlayerSprite::PlayerSprite() :
  Sprite(), _name(new sf::Text()), _textFont(NULL), _nameOffset(sf::Vector2f(0,0)),
  _pos(sf::Vector2f(WIN_W / 2,WIN_H / 2)), _deltaPos(sf::Vector2f(0,0))
{
  _name->setString("!_uninitialized");
  _name->setCharacterSize(14);
  _name->setColor(sf::Color(15,15,240));
  _name->setStyle(sf::Text::Bold);
  _dir = NONE;
  _speed = PX_PER_SECOND;
}

PlayerSprite::PlayerSprite(sf::String const &name, sf::Font *font) : 
  Sprite(), _name(new sf::Text()), _textFont(font), _nameOffset(sf::Vector2f(0,0)),
  _pos(sf::Vector2f(0,0)), _deltaPos(sf::Vector2f(0,0))
{
  _name->setString(name);
  _name->setFont(*_textFont);
  _name->setCharacterSize(14);
  _name->setColor(sf::Color(15,15,240));
  _name->setStyle(sf::Text::Bold);
  _dir = NONE;
}

PlayerSprite::~PlayerSprite()
{
  delete _name;
}

void			PlayerSprite::setText(sf::String const &name)
{
  _name->setString(name);
  _name->setCharacterSize(14);
  _name->setColor(sf::Color(15,15,240));
  _name->setStyle(sf::Text::Bold);
}

void			PlayerSprite::setFont(sf::Font *font)
{
  _textFont = font;
  _name->setFont(*_textFont);
}

void			PlayerSprite::generateOffset()
{
  if (getCurrentBound())
    {
      _nameOffset.x = getCurrentBound()->width / 2 - _name->getLocalBounds().width / 2;
      _nameOffset.y = -15;
      _name->setPosition(sf::Vector2f(_nameOffset.x, _nameOffset.y));
    }
  else
    {
      std::cout << "Warning: generateOffset in PlayerSprite - Cannot get bounds. play() might not have been called yet" << std::endl;
    }
}

void			PlayerSprite::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  if (_texture && _vertex) {
    states.texture = _texture;
    states.transform *= getTransform();
    target.draw(_vertex, 4, sf::Quads, states);
    states.texture = NULL;
    target.draw(*_name, states);
  }
}

void			PlayerSprite::moveUp()
{
  std::cout << "move up" << std::endl;
  // while (_pos.y == _playerPtr->getY())
  //   {
  // _pos.y -= (_pos.y - _playerPtr->getY()) * CASE_SIZE;
    //   std::cout << _playerPtr->getY() << std::endl;
    //   usleep(50000);
    // }
  // std::cout << _playerPtr->getY() << std::endl;

  // Player pos is not updated. Y U DID DAT ?!
  _deltaPos.y = -CASE_SIZE;
  _dir = UP;
  play("up");
}

void			PlayerSprite::moveDown()
{
  // _pos.y += (_pos.y - _playerPtr->getY()) * CASE_SIZE;
  _deltaPos.y = CASE_SIZE;
  _dir = DOWN;
  play("down");
}

void			PlayerSprite::moveLeft()
{
  _pos.x -= CASE_SIZE;
  _deltaPos.x = -CASE_SIZE;
  _dir = LEFT;
  play("left");
}

void			PlayerSprite::moveRight()
{
  _pos.x += CASE_SIZE;
  _deltaPos.x = CASE_SIZE;
  _dir = RIGHT;
  play("right");
}

void			PlayerSprite::updateMoves(sf::Clock *clock, sf::View *view)
{
  float elapsedTime = clock->getElapsedTime().asMicroseconds();
  float px = elapsedTime * _speed / 1000000;

  if (_dir == eDir::DOWN)
    {
      view->move(0, px);
      move(0, px);
      _deltaPos.y -= px;
      if (_deltaPos.y < 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
	  if (Client::getInstance()->move(CLIENT::DOWN))
	    _deltaPos.y += CASE_SIZE;
	  else
	    _dir = eDir::NONE;
	}
      if (_deltaPos.y <= 0)
	{
	  view->move(0, _deltaPos.y);
	  move(0, _deltaPos.y);
	  _deltaPos.y = 0;
	  _dir = eDir::NONE;
	  play("default_down");
	}
    }
  else if (_dir == eDir::UP)
    {
      view->move(0, -px);
      move(0, -px);
      _deltaPos.y += px;
      if (_deltaPos.y > 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
	  if (Client::getInstance()->move(CLIENT::UP))
	    _deltaPos.y -= CASE_SIZE;
	  else
	    _dir = eDir::NONE;
	}
       if (_deltaPos.y >= 0)
	{
	  view->move(0, _deltaPos.y);
	  move(0, _deltaPos.y);
	  _deltaPos.y = 0;
	  _dir = eDir::NONE;
	  play("default_up");
	}
    }
  else if (_deltaPos.x > 0)
    {
      view->move(px, 0);
      move(px, 0);
      _deltaPos.x -= px;
      if (_deltaPos.x < 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
	  if (Client::getInstance()->move(CLIENT::RIGHT))
	    _deltaPos.x += CASE_SIZE;
	  else
	    _dir = eDir::NONE;
	}
      if (_deltaPos.x <= 0)
	{
	  view->move(_deltaPos.x, 0);
	  move(_deltaPos.x, 0);
	  _deltaPos.x = 0;
	  _dir = eDir::NONE;
	  play("default_right");
	}
    }
  else if (_deltaPos.x < 0)
    {
      view->move(-px, 0);
      move(-px, 0);
      _deltaPos.x += px;
      if (_deltaPos.x > 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
	  if (Client::getInstance()->move(CLIENT::LEFT))
	    _deltaPos.x -= CASE_SIZE;
	  else
	    _dir = eDir::NONE;
	}
      if (_deltaPos.x >= 0)
	{
	  view->move(_deltaPos.x, 0);
	  move(_deltaPos.x, 0);
	  _deltaPos.x = 0;
	  _dir = eDir::NONE;
	  play("default_left");
	}
    }
}

bool			PlayerSprite::isMoving() const
{
  if (_dir == NONE)
    return false;
  return true;
}

void			PlayerSprite::setSpeed(unsigned int speed)
{
  _speed = speed;
}

void			PlayerSprite::setPlayerId(unsigned int id)
{
  _playerId = id;
  Player *player = Map::getInstance()->getPlayerById(_playerId);

  _pos.x = player->getX();
  _pos.y = player->getY();
}

void			PlayerSprite::setPlayerZone(std::string const &zone)
{
  _playerZone = zone;
}
