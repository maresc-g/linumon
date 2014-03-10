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
  _deltaPos(sf::Vector2f(0,0))
{
  _name->setString("!_uninitialized");
  _name->setCharacterSize(14);
  _name->setColor(sf::Color(27,1,155));
  _name->setStyle(sf::Text::Bold);
  _dir = NONE;
  _speed = PX_PER_SECOND;
  _isInputable = true;
  _receivedInput = false;
}

PlayerSprite::PlayerSprite(sf::String const &name, sf::Font *font) : 
  Sprite(),  _name(new sf::Text()), _textFont(font), _nameOffset(sf::Vector2f(0,0)), _deltaPos(sf::Vector2f(0,0))
{
  _name->setString(name);
  _name->setFont(*_textFont);
  _name->setCharacterSize(14);
  _name->setColor(sf::Color(27,1,155));
  _name->setStyle(sf::Text::Bold);
  _dir = NONE;
  _speed = PX_PER_SECOND;
  _isInputable = true;
  _receivedInput = false;
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

void			PlayerSprite::onClick()
{
  std::cout << "PLAYER CLICKED" << std::endl;
}

void			PlayerSprite::moveUp(float px, sf::View *view)
{
  play("up");
  if (view) view->move(0, -px);
  move(0,-px);
  _deltaPos.y += px;
  if (_deltaPos.y <= CASE_SIZE - 10 && !_receivedInput)
    _isInputable = false;
  if (_deltaPos.y >= CASE_SIZE - 10 && !_receivedInput)
    _isInputable = true;
  else if (_deltaPos.y >= CASE_SIZE - 10 && _receivedInput)
    _isInputable = false;
  if (_deltaPos.y >= CASE_SIZE)
    {
      _pos.y -= 1;
      _deltaPos.y -= CASE_SIZE;
      if (!_receivedInput)
	{
	  _dir = END_MOVE;
	  move(0, _deltaPos.y);
	  view->move(0, _deltaPos.y);
	  _deltaPos.y = 0;
	  play("default_up");
	}
      _receivedInput = false;
      _isInputable = true;
    }
}

void			PlayerSprite::moveDown(float px, sf::View *view)
{
  play("down");
  if (view) view->move(0, px);
  move(0,px);
  _deltaPos.y += px;
  if (_deltaPos.y <= CASE_SIZE - 10 && !_receivedInput)
    _isInputable = false;
  if (_deltaPos.y >= CASE_SIZE - 10 && !_receivedInput)
    _isInputable = true;
  else if (_deltaPos.y >= CASE_SIZE - 10 && _receivedInput)
    _isInputable = false;
  if (_deltaPos.y >= CASE_SIZE)
    {
      _pos.y += 1;
      _deltaPos.y -= CASE_SIZE;
      if (!_receivedInput)
	{
	  _dir = END_MOVE;
	  move(0, -_deltaPos.y);
	  view->move(0, -_deltaPos.y);
	  _deltaPos.y = 0;
	  play("default_down");
	}
      _receivedInput = false;
      _isInputable = true;
    }
}

void			PlayerSprite::moveLeft(float px, sf::View *view)
{
  play("left");
  // if (view && _pos.x > 15)
  view->move(-px, 0);
  move(-px,0);
  _deltaPos.y += px;
  if (_deltaPos.y <= CASE_SIZE - 10 && !_receivedInput)
    _isInputable = false;
  if (_deltaPos.y >= CASE_SIZE - 10 && !_receivedInput)
    _isInputable = true;
  else if (_deltaPos.y >= CASE_SIZE - 10 && _receivedInput)
    _isInputable = false;
  if (_deltaPos.y >= CASE_SIZE)
    {
      std::cout << "View center : "  << view->getCenter().x << std::endl;
      _pos.x -= 1;
      _deltaPos.y -= CASE_SIZE;
      if (!_receivedInput)
	{
	  _dir = END_MOVE;
	  move(_deltaPos.y, 0);
	  // if (_pos.x >= 15)
	    view->move(_deltaPos.y,0);
	  _deltaPos.y = 0;
	  play("default_left");
	  std::cout << "View center at stop : "  << view->getCenter().x << std::endl;
	}
      _receivedInput = false;
      _isInputable = true;
    }
}

void			PlayerSprite::moveRight(float px, sf::View *view)
{
  play("right");
  if (view // && _pos.x >= 15
      )
    view->move(px, 0);
  move(px,0);
  _deltaPos.y += px;
  if (_deltaPos.y <= CASE_SIZE - 10 && !_receivedInput)
    _isInputable = false;
  if (_deltaPos.y >= CASE_SIZE - 10 && !_receivedInput)
    _isInputable = true;
  else if (_deltaPos.y >= CASE_SIZE - 10 && _receivedInput)
    _isInputable = false;
  if (_deltaPos.y >= CASE_SIZE)
    {

      // NEED TO FIX DECAL


      std::cout << _deltaPos.y << std::endl;
      std::cout << "View center : "  << view->getCenter().x << std::endl;
      _pos.x += 1;
      _deltaPos.y -= CASE_SIZE;
      if (!_receivedInput)
	{
	  _dir = END_MOVE;
	  move(-_deltaPos.y, 0);
	  // if (_pos.x > 15)
	    view->move(-_deltaPos.y,0);
	  _deltaPos.y = 0;
	  play("default_right");
	  std::cout << "View center at stop : "  << view->getCenter().x << std::endl;
	}
      _receivedInput = false;
      _isInputable = true;
    }
}

void			PlayerSprite::moveFromServer(sf::View *v)
{
  if (_dir == END_MOVE)
    {
      if (_pos.x != Map::getInstance()->getPlayerById(_playerId)->getX() || _pos.y != Map::getInstance()->getPlayerById(_playerId)->getY())
	{
	  setPosition(Map::getInstance()->getPlayerById(_playerId)->getX() * CASE_SIZE,
		      Map::getInstance()->getPlayerById(_playerId)->getY() * CASE_SIZE - getCurrentBound()->height / 2 + 4);
	  if (v) {
	    v->reset(sf::FloatRect(0,0, WIN_W, WIN_H));
	    v->move(Map::getInstance()->getPlayerById(_playerId)->getX() * CASE_SIZE - WIN_W / 2,
		    Map::getInstance()->getPlayerById(_playerId)->getY() * CASE_SIZE - WIN_H / 2);
	    _pos.x = Map::getInstance()->getPlayerById(_playerId)->getX();
	    _pos.y = Map::getInstance()->getPlayerById(_playerId)->getY();
	    // if (_pos.x <= 15)
	    //   v->move((15 - _pos.x * CASE_SIZE),
	    // 	       0);
	    std::cout << "NEW POS X AFTER MAGIC TP : "  << _pos.x << std::endl;
	    std::cout << "WADAFAK WITH POS ?" << std::endl;
	  }
	}
      _dir = NONE;
    }
  if (_dir == NONE || _dir == WAITING)
    {
      // std::cout << "Server player pos : " << Map::getInstance()->getPlayerById(_playerId)->getY() << std::endl;
      _deltaPos.x = (_pos.x - Map::getInstance()->getPlayerById(_playerId)->getX()) * -CASE_SIZE;
      _deltaPos.y = (_pos.y - Map::getInstance()->getPlayerById(_playerId)->getY()) * -CASE_SIZE;
      if (_deltaPos.y != 0)
	_dir = (_deltaPos.y < 0 ? UP : DOWN);
      else if (_deltaPos.x != 0)
	_dir = (_deltaPos.x < 0 ? LEFT : RIGHT);
      _deltaPos.x = 0;
      _deltaPos.y = 0;
      // std::cout << (_dir == DOWN ? "dir = DOWN" : _dir == WAITING ? "dir = WAITING" : "NONE") << std::endl;
    }
}

void			PlayerSprite::updateMoves(sf::Clock *clock, sf::View *view)
{
  float elapsedTime = clock->getElapsedTime().asMicroseconds();
  float px = elapsedTime * _speed / 1000000;

  if (_dir == eDir::DOWN)
    moveDown(px, view);
  else if (_dir == eDir::UP)
    moveUp(px, view);
  else if (_dir == eDir::LEFT)
    moveLeft(px, view);
  else if (_dir == eDir::RIGHT)
    moveRight(px, view);
}


void			PlayerSprite::updateMoves2(sf::Clock *clock, sf::View *view)
{
  // float elapsedTime = clock->getElapsedTime().asMicroseconds();
  // float px = elapsedTime * _speed / 1000000;

  // //this need to be fixed

  // if (_dir == eDir::DOWN)
  //   {
  //     play("down");
  //     if (view) view->move(0, px);
  //     move(0, px);
  //     _deltaPos.y -= px;
  //     if (_deltaPos.y < 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
  // 	{
  // 	  if (view && Client::getInstance()->move(CLIENT::DOWN)){
  // 	    _deltaPos.y += CASE_SIZE;
  // 	    _pos.y += 1;
  // 	  }
  // 	  // else if (!view)
  // 	  //   moveFromServer();
  // 	  else
  // 	    _dir = eDir::NONE;
  // 	}
  //     if (_deltaPos.y <= 0)
  // 	{
  // 	  if (view) view->move(0, _deltaPos.y);
  // 	  move(0, _deltaPos.y);
  // 	  _deltaPos.y = 0;
  // 	  _dir = eDir::NONE;
  // 	  play("default_down");
  // 	  _pos.y = Map::getInstance()->getPlayerById(_playerId)->getY();
  // 	}
  //   }
  // else if (_dir == eDir::UP)
  //   {
  //     play("up");
  //     if (view) view->move(0, -px);
  //     move(0, -px);
  //     _deltaPos.y += px;
  //     if (_deltaPos.y > 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
  // 	{
  // 	  if (Client::getInstance()->move(CLIENT::UP))
  // 	    {
  // 	      _deltaPos.y -= CASE_SIZE;
  // 	      _pos.y -= 1;
  // 	    }
  // 	  // else if (!view)
  // 	  //   moveFromServer();
  // 	  else
  // 	    _dir = eDir::NONE;
  // 	}
  //      if (_deltaPos.y >= 0)
  // 	{
  // 	  if (view) view->move(0, _deltaPos.y);
  // 	  move(0, _deltaPos.y);
  // 	  _deltaPos.y = 0;
  // 	  _pos.y = Map::getInstance()->getPlayerById(_playerId)->getY();
  // 	  _dir = eDir::NONE;
  // 	  play("default_up");
  // 	}
  //   }
  // else if (_dir == eDir::RIGHT)
  //   {
  //     play("right");
  //     if (view) view->move(px, 0);
  //     move(px, 0);
  //     _deltaPos.x -= px;
  //     if (_deltaPos.x < 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
  // 	{
  // 	  if (Client::getInstance()->move(CLIENT::RIGHT))
  // 	    {
  // 	      _deltaPos.x += CASE_SIZE;
  // 	      _pos.x += 1;
  // 	    }
  // 	  // else if (!view)
  // 	  //   moveFromServer();
  // 	  else
  // 	    _dir = eDir::NONE;
  // 	}
  //     if (_deltaPos.x <= 0)
  // 	{
  // 	  if (view) view->move(_deltaPos.x, 0);
  // 	  move(_deltaPos.x, 0);
  // 	  _deltaPos.x = 0;
  // 	  _pos.x = Map::getInstance()->getPlayerById(_playerId)->getX();
  // 	  _dir = eDir::NONE;
  // 	  play("default_right");
  // 	}
  //   }
  // else if (_dir == eDir::LEFT)
  //   {
  //     play("left");
  //     if (view) view->move(-px, 0);
  //     move(-px, 0);
  //     _deltaPos.x += px;
  //     if (_deltaPos.x > 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
  // 	{
  // 	  if (Client::getInstance()->move(CLIENT::LEFT))
  // 	    {
  // 	      _deltaPos.x -= CASE_SIZE;
  // 	      _pos.x -= 1;
  // 	    }
  // 	  // else if (!view)
  // 	  //   moveFromServer();
  // 	  else
  // 	    _dir = eDir::NONE;
  // 	}
  //     if (_deltaPos.x >= 0)
  // 	{
  // 	  if (view) view->move(_deltaPos.x, 0);
  // 	  move(_deltaPos.x, 0);
  // 	  _deltaPos.x = 0;
  // 	  _pos.x = Map::getInstance()->getPlayerById(_playerId)->getX();
  // 	  _dir = eDir::NONE;
  // 	  play("default_left");
  // 	}
  //   }
  // Remember :
  // The end player pos is suppose to be the same as the _pos.
  // No check are made actually
  // The lag at input is because i wait until the server answered the new pos. Might be fixed later
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

void			PlayerSprite::setPlayerId(unsigned int id, bool setPos)
{
  _playerId = id;
  if (setPos){
    Player *player = Map::getInstance()->getPlayerById(_playerId);
    
    _pos.x = player->getX();
    _pos.y = player->getY();
  }
}

unsigned int		PlayerSprite::getPlayerId() const
{
  return _playerId;
}

void			PlayerSprite::setPlayerZone(std::string const &zone)
{
  _playerZone = zone;
}

void			PlayerSprite::setWaitingState()
{
  _dir = WAITING;
}

bool			PlayerSprite::isUserInputable()
{
  return _isInputable;
}

void			PlayerSprite::receivedInput()
{
  _isInputable = false;
  _receivedInput = true;
}
