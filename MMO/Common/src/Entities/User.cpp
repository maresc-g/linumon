//
// User.cpp for User in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 19:34:50 2013 alexis mestag
// Last update Tue Dec  3 15:57:20 2013 alexis mestag
//

#include			<functional>
#include			"Entities/User.hh"

User::User() :
  Persistent(), _pseudo(""), _password(""), _players(new Players)
{

}

User::User(std::string const &pseudo, std::string const &password) :
  Persistent(), _pseudo(pseudo), _password(password), _players(new Players)
{

}

User::User(User const &rhs) :
  Persistent(rhs)
{
  *this = rhs;
}

User				&User::operator=(User const &rhs)
{
  if (this != &rhs)
    {
      this->setPseudo(rhs.getPseudo());
      this->setPassword(rhs.getPassword());
    }
  return (*this);
}

User::~User()
{
  delete _players;
}

std::string const		&User::getPseudo() const
{
  return (_pseudo);
}

void				User::setPseudo(std::string const &pseudo)
{
  _pseudo = pseudo;
}

std::string const		&User::getPassword() const
{
  return (_password);
}

void				User::setPassword(std::string const &password)
{
  _password = password;
}
