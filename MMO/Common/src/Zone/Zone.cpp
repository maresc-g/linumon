//
// Zone.cpp for Zone in /home/maitre_c/work/linumon/MMO
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Fri Jan 24 14:01:10 2014 antoine maitre
// Last update Tue Jan 28 15:02:02 2014 antoine maitre
//

#include			<iostream>
#include			"Zone/Zone.hh"

Zone::Zone(Json::Value const topography)
  : _sizeX(topography["X"].asInt()), _sizeY(topography["Y"].asInt()), _name(topography["Name"].asString()),
    _type(static_cast<const eZone>(topography["Type"].asInt()))
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
		this->_cases.push_back(new Case(j, k, topography[zone.str()]["Safe"].asBool()));
	      }
	}
      else
	break;
      zone.str("");
    }
  this->_cases.sort(compareValue);
  this->_cases.unique(sameValue);
}

Zone::~Zone()
{
  
}

void				Zone::addPlayer(AEntity *player)
{
  this->_players.push_back(player);
}

void				Zone::delPlayer(AEntity *player)
{
  this->_players.remove(player);
}

std::list<AEntity *>		Zone::getPlayers() const
{
  return (this->_players);
}

void				Zone::addCase(Case *cas)
{
  this->_cases.push_back(cas);
}

void				Zone::delCase(Case *cas)
{
  this->_cases.remove(cas);
}

Case				*Zone::getCase(int x, int y)
{
  Case				*tmp;

  tmp = NULL;
  for (std::list<Case *>::iterator it = this->_cases.begin(); it != this->_cases.end(); it++)
    if ((*it)->getCoord().getX() == x && (*it)->getCoord().getY() == y)
      tmp = (*it);
  return (tmp);
}

std::list<Case *>		Zone::getCases() const
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
