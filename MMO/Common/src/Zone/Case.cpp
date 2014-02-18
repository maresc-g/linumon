//
// Case.cpp for Case in /home/maitre_c/work/linumon/MMO/Common/include/Zone
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Fri Jan 24 13:44:31 2014 antoine maitre
// Last update Tue Feb 18 16:18:22 2014 antoine maitre
//

#include		"Zone/Case.hh"

Case::Case(int const x, int const y, bool const safe) :
  _entities(new std::list<AEntity *>),
  _coord(x, y),
  _safe(safe)
{

}

Case::~Case()
{
  delete _entities;
}

bool			Case::getSafe() const
{
  return (this->_safe);
}

const Coordinate<int>	&Case::getCoord() const
{
  return (this->_coord);
}

std::list<AEntity *>	*Case::getEntities() const
{
  return (this->_entities);
}

void			Case::addAEntity(AEntity *entity)
{
  this->_entities->push_back(entity);
}

void			Case::delAEntity(AEntity *entity)
{
  this->_entities->remove(entity);
}

bool			Case::serialization(Trame &trame) const
{
  if (!this->_entities->empty())
    {
      trame["X"] = this->_coord.getX();
      trame["Y"] = this->_coord.getY();
      int i = 0;
      for (auto it = this->_entities->begin(); it != this->_entities->end(); it++)
  	{
	  if ((*it)->getEntityType() == AEntity::STATENTITY)
	    {
	      auto tmp = static_cast<Player *>(*it); 
	      trame[std::to_string(i)]["PLAYER"]["ID"] = static_cast<int>(tmp->getId());
	      trame[std::to_string(i)]["PLAYER"]["NAME"] = tmp->getName();
	      trame[std::to_string(i)]["PLAYER"]["TYPE"] = tmp->getStatEntityType();
	      tmp->getCoord().serialization(trame(trame[std::to_string(i)]["PLAYER"]));
	      tmp->getFaction().serialization(trame(trame[std::to_string(i)]["PLAYER"]));
	      tmp->getDigitaliser().serialization(trame(trame[std::to_string(i)]["PLAYER"]));
	    }
	  else
	    {
	      auto tmp = static_cast<Ressource *>(*it); 
	      tmp->serialization(trame(trame[std::to_string(i)]));
	    }
	  i++;
  	}
      return (true);
    }
  return (false);
}

void			Case::deserialization(Trame const &trame)
{
  for (int i = 0; trame.isMember(std::to_string(i)); i++)
    {
      std::cout << "BEGINNING" << std::endl;
      if (trame[std::to_string(i)].isMember("PLAYER"))
	{
	  std::cout << "0" << std::endl;
	  Player *player = new Player(trame[std::to_string(i)]["PLAYER"]["NAME"].asString());
	  std::cout << "1" << std::endl;
	  player->setId(trame[std::to_string(i)]["PLAYER"]["ID"].asUInt());
	  std::cout << "2" << std::endl;
	  //	  player->setStatEntityType(static_cast<AStatEntity::eStatEntity>(trame[std::to_string(i)]["PLAYER"]["TYPE"].asInt()));
	  player->setCoord(*Player::PlayerCoordinate::deserialization(trame(trame[std::to_string(i)]["PLAYER"])));
	  std::cout << "3" << std::endl;
	  player->setFaction(*Faction::deserialization(trame(trame[std::to_string(i)]["PLAYER"])));
	  std::cout << "4" << std::endl;
	  this->_entities->push_back(player);
	}
      else
	this->_entities->push_back(Ressource::deserialization(trame(trame[std::to_string(i)])));
    }
}
