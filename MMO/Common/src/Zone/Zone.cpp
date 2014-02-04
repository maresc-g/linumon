//
// Zone.cpp for Zone in /home/maitre_c/work/linumon/MMO
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Fri Jan 24 14:01:10 2014 antoine maitre
// Last update Tue Feb  4 14:16:58 2014 antoine maitre
//

#include			<iostream>
#include			"Zone/Zone.hh"

Zone::Zone(Json::Value const topography):
  _sizeX(topography["X"].asInt()),
  _sizeY(topography["Y"].asInt()),
  _players(new std::list<AEntity *>),
  _type(static_cast<const ZONE::eZone>(topography["Type"].asInt())),
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

Zone::Zone(int const x, int const y, ZONE::eZone const type)
  : _sizeX(x), _sizeY(y), _type(type)
{
  
}

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

Case				*Zone::getCase(int const x, int const y)
{
  Case				*tmp;

  tmp = NULL;
  for (std::list<Case *>::iterator it = this->_cases->begin(); it != this->_cases->end(); it++)
    if ((*it)->getCoord().getX() == x && (*it)->getCoord().getY() == y)
      tmp = (*it);
  return (tmp);
}

std::list<Case *>		&Zone::getCases() const
{
  return (*this->_cases);
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
  std::ostringstream		oss;
  std::ostringstream		ossb;

  oss << "ZONE" << this->_type;
  trame[CONTENT][oss.str()]["TYPE"] = this->_type;
  trame[CONTENT][oss.str()]["SIZEX"] = this->_sizeX;
  trame[CONTENT][oss.str()]["SIZEY"] = this->_sizeY;
  int i = 0;
  for (auto it = this->_players->begin(); it != this->_players->end(); it++)
    {
      ossb << "PLAYER" << i;
      (*it)->serialization(trame(trame[CONTENT][oss.str()][ossb.str()]));
      ossb.str("");
      i++;
    }
  for (auto it = this->_cases->begin(); it != this->_cases->end(); it++)
    (*it)->serialization(trame(trame[CONTENT][oss.str()]));
  return (true);
}

Zone				*Zone::deserialization(Trame const &trame)
{
  Zone				*ret = NULL;
  std::ostringstream		oss;

  if (trame[CONTENT].isMember("ZONE"))
    if (trame[CONTENT]["ZONE"].isMember("TYPE"))
      if (trame[CONTENT]["ZONE"].isMember("SIZEX"))
	if (trame[CONTENT]["ZONE"].isMember("SIZEY"))
	  {
	    ret = new Zone(trame[CONTENT]["ZONE"]["SIZEX"].asInt(), 
			   trame[CONTENT]["ZONE"]["SIZEY"].asInt(), 
			   static_cast<ZONE::eZone const>(trame[CONTENT]["ZONE"]["TYPE"].asInt()));
	      for (int i = 0; i == 0 || trame[CONTENT]["ZONE"].isMember(oss.str()); i++)
		{
		  oss.str("");
		  oss << "ENTITIES" << i;
		  if (trame[CONTENT]["ZONE"].isMember(oss.str()))
		    ret->addCase(Case::deserialization(trame(trame[CONTENT]["ZONE"][oss.str()])));
		}
	  }
      return (ret);
}
