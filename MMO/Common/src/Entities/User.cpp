//
// User.cpp for User in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 19:34:50 2013 alexis mestag
// Last update Mon Feb  3 16:23:29 2014 alexis mestag
//

#include			<functional>
#include			"Entities/User.hh"

User::User() :
  Persistent(), _pseudo(""), _password("")
{

}

User::User(std::string const &pseudo, std::string const &password) :
  Persistent(), _pseudo(pseudo), _password(password)
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
      // It's shouldn't be possible to copy _players
    }
  return (*this);
}

User::~User()
{

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

Players const			&User::getPlayers() const
{
  return (_players);
}

bool				User::addPlayer(Player &player)
{
  _players.addPlayer(player);
  return (true);
}

/*
** Code to get a list of PlayerView with the user's persistent id
**
*/

// #include			"Database/Repositories/UserViewRepository.hpp"
// #include			"Database/Repositories/PlayerViewRepository.hpp"

// Repository<UserView>		*ru = &Database::getRepository<UserView>();
// Repository<PlayerView>	*rp = &Database::getRepository<PlayerView>();
// UserView			*uv = NULL;
// std::list<PlayerView>		*pvs = NULL;

// uv = ru->getByPseudo("Laurent");
// std::cout << uv->persistentId << ": " << uv->pseudo << " => " << uv->password << std::endl;
// pvs = rp->getByUserId(uv->persistentId);
// if (pvs) {
//   for (auto it = pvs->begin() ; it != pvs->end() ; ++it) {
//     std::cout << "\t" << it->name << ", level : " << it->level << std::endl;
//   }
//   delete pvs;
//  }
// delete uv;

// uv = ru->getByPseudo("Cyril");
// std::cout << uv->persistentId << ": " << uv->pseudo << " => " << uv->password << std::endl;
// pvs = rp->getByUserId(uv->persistentId);
// if (pvs) {
//   for (auto it = pvs->begin() ; it != pvs->end() ; ++it) {
//     std::cout << "\t" << it->name << ", level : " << it->level << std::endl;
//     }
//   delete pvs;
//  }
// delete uv;

// Repository<PlayerView>::deleteInstance();
// Repository<UserView>::deleteInstance();
// Database::deleteInstance();
