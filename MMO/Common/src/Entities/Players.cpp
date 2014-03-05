//
// Players.cpp for Players in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Dec  3 15:55:08 2013 alexis mestag
// Last update Mon Mar  3 16:37:25 2014 alexis mestag
//

#include			<functional>
#include			<sstream>
#include			"Entities/Players.hh"

Players::Players() :
  ContainerWrapper<container_type>()
{

}

Players::Players(Players const &rhs) :
  ContainerWrapper<container_type>()
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

  this->getContainer().remove_if(f);
}

void				Players::addPlayer(Player &player)
{
  this->getContainer().push_back(&player);
}
