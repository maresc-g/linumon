//
// PNJ.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Tue Feb 25 13:43:06 2014 laurent ansel
// Last update Tue Feb 25 14:26:00 2014 laurent ansel
//


#include			"Entities/PNJ.hh"
#include			"Entities/Heal.hh"

PNJ::PNJ(std::string const &name) :
  AEntity(name, AEntity::eEntity::PNJ),
  _pnjType(ePnj::HEAL),
  _coord(NULL)
{

}

PNJ::PNJ(PNJ const &rhs) :
  AEntity(rhs),
  _pnjType(ePnj::HEAL),
  _coord(NULL)
{
  *this = rhs;
}

PNJ::~PNJ()
{

}

PNJ				&PNJ::operator=(PNJ const &rhs)
{
  if (this != &rhs)
    {
      this->setCoord(rhs.getCoord());
    }
  return (*this);
}

PNJ::PNJCoordinate const	&PNJ::getCoord() const
{
  return (*this->_coord);
}

void				PNJ::setCoord(PNJ::PNJCoordinate const &coord)
{
  *this->_coord = coord;
}

PNJ::PNJCoordinate::type const	&PNJ::getX() const
{
  return (this->_coord->getX());
}

PNJ::PNJCoordinate::type const	&PNJ::getY() const
{
  return (this->_coord->getY());
}

void				PNJ::setX(PNJ::PNJCoordinate::type const &x)
{
  this->_coord->setX(x);
}

void				PNJ::setY(PNJ::PNJCoordinate::type const &y)
{
  this->_coord->setY(y);
}

PNJ::ePnj			PNJ::getPNJType() const
{
  return (_pnjType);
}

void				PNJ::setPNJType(PNJ::ePnj const pnjType)
{
  _pnjType = pnjType;
}

PNJ				*PNJ::deserialization(Trame const &trame, bool const client)
{
  PNJ				*pnj = NULL;

  pnj = Heal::deserialization(trame, client);
  return (pnj);
}
