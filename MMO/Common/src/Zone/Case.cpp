//
// Case.cpp for Case in /home/maitre_c/work/linumon/MMO/Common/include/Zone
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Fri Jan 24 13:44:31 2014 antoine maitre
// Last update Tue Jan 28 14:50:25 2014 antoine maitre
//

#include		"Zone/Case.hh"

Case::Case(int x, int y, bool const safe) :
  _coord(x, y), _safe(safe)
{
  
}

Case::~Case()
{
  
}

bool			Case::getSafe() const
{
  return (this->_safe);
}

const Coordinate<int>	Case::getCoord() const
{
  return (this->_coord);
}

void			Case::addAEntity(AEntity *entity)
{
  this->_entities.push_back(entity);
}

void			Case::delAEntity(AEntity *entity)
{
  this->_entities.remove(entity);
}

