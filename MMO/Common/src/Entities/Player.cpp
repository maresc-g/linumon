//
// Player.cpp for Player in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Dec  3 13:45:16 2013 alexis mestag
// Last update Tue Dec  3 13:53:21 2013 alexis mestag
//

#include			"Entities/Player.hh"

Player::Player() :
  Persistent(), ACharacter("", eCharacter::PLAYER)
{

}

Player::Player(std::string const &name) :
  Persistent(), ACharacter(name, eCharacter::PLAYER)
{

}

Player::Player(Player const &rhs) :
  Persistent(rhs), ACharacter(rhs)
{
  *this = rhs;
}

Player::~Player()
{

}

Player				&Player::operator=(Player const &rhs)
{
  if (this != &rhs)
    {

    }
  return (*this);
}
