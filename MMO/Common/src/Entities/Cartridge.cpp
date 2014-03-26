//
// Cartridge.cpp for Cartridge in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Mar 26 01:33:46 2014 alexis mestag
// Last update Wed Mar 26 02:36:37 2014 alexis mestag
//

#include				"Entities/Cartridge.hh"

Cartridge::Cartridge(double const efficiency) :
  _efficiency(efficiency)
{

}

Cartridge::~Cartridge()
{

}

Cartridge::Cartridge(Cartridge const &rhs)
{
  *this = rhs;
}

Cartridge				&Cartridge::operator=(Cartridge const &rhs)
{
  if (this != &rhs) {
    this->setEfficiency(rhs.getEfficiency());
  }
  return (*this);
}

bool					Cartridge::operator==(Cartridge const &rhs) const
{
  return (this->getEfficiency() == rhs.getEfficiency());
}

bool					Cartridge::operator!=(Cartridge const &rhs) const
{
  return (!(*this == rhs));
}

bool					Cartridge::operator<(Cartridge const &rhs) const
{
  return (this->getEfficiency() < rhs.getEfficiency());
}

bool					Cartridge::operator>=(Cartridge const &rhs) const
{
  return (!(*this < rhs));
}

bool					Cartridge::operator>(Cartridge const &rhs) const
{
  return (this->getEfficiency() > rhs.getEfficiency());
}

bool					Cartridge::operator<=(Cartridge const &rhs) const
{
  return (!(*this > rhs));
}

Cartridge::efficiency_type		Cartridge::getEfficiency() const
{
  return (_efficiency);
}

void					Cartridge::setEfficiency(efficiency_type const eff)
{
  _efficiency = eff;
}
