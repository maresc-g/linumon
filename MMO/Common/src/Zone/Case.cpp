//
// Case.cpp for Case in /home/maitre_c/work/linumon/MMO/Common/include/Zone
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Fri Jan 24 13:44:31 2014 antoine maitre
// Last update Tue Feb 11 16:42:19 2014 antoine maitre
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
      serialList(trame, *(this->_entities));
      return (true);
    }
  return (false);
}

void			Case::deserialization(Trame const &trame)
{
  (*this->_entities) = unserialList<AEntity>(trame);
}
