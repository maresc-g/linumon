//
// Players.cpp for Players in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Dec  3 15:55:08 2013 alexis mestag
// Last update Tue Dec  3 16:06:34 2013 alexis mestag
//

#include			<functional>
#include			"Entities/Players.hh"

Players::Players() :
  _players(new std::list<Player *>)
{

}

Players::~Players()
{
  this->deletePlayers();
}

void				Players::deletePlayers()
{
  static std::function<bool(Player *)>	f = [](Player *p) -> bool {
    delete p;
    return (true);
  };

  _players->remove_if(f);
  delete _players;
  _players = NULL;
}
