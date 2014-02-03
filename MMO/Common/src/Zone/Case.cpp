//
// Case.cpp for Case in /home/maitre_c/work/linumon/MMO/Common/include/Zone
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Fri Jan 24 13:44:31 2014 antoine maitre
// Last update Fri Jan 31 15:54:12 2014 antoine maitre
//

#include		"Zone/Case.hh"

Case::Case(int const x, int const y, bool const safe) :
  _entities(new std::list<AEntity *>),
  _coord(new Coordinate<int>(x, y)),
  _safe(safe)
{

}

Case::~Case()
{

}

bool			Case::getSafe() const
{
  return (this->_safe);
}

const Coordinate<int>	&Case::getCoord() const
{
  return (*this->_coord);
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
  std::ostringstream	oss;

  oss << "CASE" << this->_coord->getX() << this->_coord->getY();
  if (this->_coord->serialization(trame(trame[oss.str()])))
    {
      int i = 0;
      std::ostringstream	ossb;
      for (auto it = this->_entities->begin(); it != this->_entities->end(); it++)
      	{
      	  ossb << "ENTITIES" << i;
	  (*it)->serialization(trame(trame[oss.str()][ossb.str()]));
	  // trame[oss.str()][ossb.str()]["TYPE"] = (*it)->getEntityType();
      	  ossb.str("");
	  i++;
      	}
      trame[oss.str()]["SAFE"] = this->_safe;
      return (true);
    }
  return (false);
}

Case			*Case::deserialization(Trame const &trame)
{
  Case			*ret = NULL;
  std::ostringstream	oss;

  if (trame.isMember("SAFE"))
    {
      if(trame.isMember("COORDINATE"))
	{
	  ret = new Case(trame["COORDINATE"]["X"].asInt(), trame["COORDINATE"]["Y"].asInt(), trame["SAFE"].asBool());
	  oss << "ENTITIES" << 0;
	  for (int i = 0; trame.isMember(oss.str()); i++)
	    {
	      if (trame[oss.str()].isMember("PLAYER"))
	       	ret->addAEntity(Player::deserialization(trame(trame[oss.str()])));
	      // if (trame[oss.str()].isMember("RESSOURCE"))
	      // 	ret->addAEntity(Ressource::deserialization(trame(trame[oss.str()])));
	    }
	}
    }
  return (ret);
}
