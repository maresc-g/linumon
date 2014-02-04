//
// Players.cpp for Players in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Dec  3 15:55:08 2013 alexis mestag
// Last update Tue Feb  4 12:58:37 2014 laurent ansel
//

#include			<functional>
#include			<sstream>
#include			"Entities/Players.hh"

Players::Players()
{

}

Players::Players(Players const &rhs)
{
  *this = rhs;
}

Players::~Players()
{
  this->deletePlayers();
}

Players				&Players::operator=(Players const &rhs)
{
  if (this != &rhs)
    {

    }
  return (*this);
}

void				Players::deletePlayers()
{
  static std::function<bool(Player *)>	f = [](Player *p) -> bool {
    delete p;
    return (true);
  };

  _players.remove_if(f);
}

void				Players::addPlayer(Player &player)
{
  _players.push_back(&player);
}
