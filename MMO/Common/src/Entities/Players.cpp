//
// Players.cpp for Players in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Dec  3 15:55:08 2013 alexis mestag
// Last update Thu Jan 30 15:23:52 2014 alexis mestag
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

bool				Players::serialization(Trame &trame) const
{
  bool				ret = true;
  int				i = 0;
  std::ostringstream		str("PLAYER");

  trame[CONTENT]["PLAYERSLIST"];
  for (auto it = this->_players.begin() ; it != this->_players.end() ; ++it)
    {
      str << i;
      trame[CONTENT]["PLAYERSLIST"][str.str()]["IDPLAYER"] = static_cast<unsigned int>((*it)->getId());
      trame[CONTENT]["PLAYERSLIST"][str.str()]["NAME"] = (*it)->getName();
      trame[CONTENT]["PLAYERSLIST"][str.str()]["LEVEL"] = (*it)->getLevel().getLevel();
      trame[CONTENT]["PLAYERSLIST"][str.str()]["Faction"] = (*it)->getFaction().getName();
      str.str("PLAYER");
      i++;
    }
  return (ret);
}

void				Players::addPlayer(Player &player)
{
  _players.push_back(&player);
}
