//
// Zone.cpp for Zone in /home/maitre_c/work/linumon/MMO
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Fri Jan 24 14:01:10 2014 antoine maitre
// Last update Mon Feb 10 16:25:16 2014 antoine maitre
//

#include			<iostream>
#include			"Zone/Zone.hh"

Zone::Zone(Json::Value const topography):
  Nameable(topography["Type"].asString()),
  _sizeX(topography["X"].asInt()),
  _sizeY(topography["Y"].asInt()),
  _players(new std::list<AEntity *>),
  _cases(new std::list<Case *>)
{
  std::ostringstream		zone;

  for (int i = 1; i; i++)
    {
      zone << "Zone" << i;
      if (topography.isMember(zone.str()))
	{
	  for (int j = topography[zone.str()]["X1"].asInt(); j < topography[zone.str()]["X2"].asInt(); j++)
	    for (int k = topography[zone.str()]["Y1"].asInt(); k < topography[zone.str()]["Y2"].asInt(); k++)
	      {
		this->_cases->push_back(new Case(j, k, topography[zone.str()]["Safe"].asBool()));
	      }
	}
      else
	break;
      zone.str("");
    }
  this->_cases->sort(compareValue);
  this->_cases->unique(sameValue);
}

// Zone::Zone(int const x, int const y, std::string const type)
//   : _sizeX(x), _sizeY(y), _type(type), _cases(new std::list<Case*>)
// {
  
// }

Zone::~Zone()
{
  for (auto it = this->_players->begin() ; it != this->_players->end() ; ++it)
    delete (*it);
  delete _players;
  for (auto it = this->_cases->begin() ; it != this->_cases->end() ; ++it)
    delete (*it);
  delete _cases;
}

void				Zone::addPlayer(AEntity *player)
{
  this->_players->push_back(player);
}

void				Zone::delPlayer(AEntity *player)
{
  this->_players->remove(player);
}

std::list<AEntity *>		&Zone::getPlayers() const
{
  return (*this->_players);
}

void				Zone::addCase(Case *cas)
{
  this->_cases->push_back(cas);
}

void				Zone::delCase(Case *cas)
{
  this->_cases->remove(cas);
}

Case				*Zone::getCase(int const x, int const y) const
{
  Case				*tmp;

  tmp = NULL;
  for (std::list<Case *>::iterator it = this->_cases->begin(); it != this->_cases->end(); it++)
    if ((*it)->getCoord().getX() == x && (*it)->getCoord().getY() == y)
      tmp = (*it);
  return (tmp);
}

std::list<Case *>		*Zone::getCases() const
{
  return (this->_cases);
}

bool				sameValue(Case *case1, Case *case2)
{
  if (case1->getCoord().getX() == case2->getCoord().getX() &&
      case1->getCoord().getY() == case2->getCoord().getY())
    return (true);
  return (false);
}

bool				compareValue(Case *case1, Case *case2)
{
  if (case1->getCoord().getX() < case2->getCoord().getX())
    return (true);
  if (case1->getCoord().getX() == case2->getCoord().getX() &&
      case1->getCoord().getY() < case2->getCoord().getY())
    return (true);
  else
    return (false);
}

bool				Zone::serialization(Trame &trame) const
{
  int				i = 1;

  for (auto it = this->_cases->begin(); it != this->_cases->end(); it++)
    if ((*it)->serialization(trame(trame[CONTENT]["ZONE"][std::to_string(i)])))
      i++;
  return (true);
}

void				Zone::deserialization(Trame const &trame)
{
  for (int i = 1; trame[CONTENT]["ZONE"].isMember(std::to_string(i)); i++)
    {
      this->getCase(trame[CONTENT]["ZONE"][i]["X"].asInt(), trame[CONTENT]["ZONE"][i]["Y"].asInt())->deserialization(trame);
    }
}

void				Zone::move(Player::PlayerCoordinate const &source, Player::PlayerCoordinate const &dest, AEntity *entity)
{
  Case				*cas = this->getCase(source.getX(), source.getY());

  cas->delAEntity(entity);
  cas = this->getCase(dest.getX(), dest.getY());
  cas->addAEntity(entity);
}

int				Zone::getSizeX() const { return (_sizeX); }
int				Zone::getSizeY() const { return (_sizeY); }
