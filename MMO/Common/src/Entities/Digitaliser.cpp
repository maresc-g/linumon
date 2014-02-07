//
// Digitaliser.cpp for Digitaliser in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Dec 10 15:19:56 2013 alexis mestag
// Last update Fri Feb  7 11:35:55 2014 laurent ansel
//

#include			<sstream>
#include			"Entities/Digitaliser.hh"

Digitaliser::Digitaliser()
{

}

Digitaliser::Digitaliser(Digitaliser const &rhs)
{
  *this = rhs;
}

Digitaliser::~Digitaliser()
{

}

Digitaliser			&Digitaliser::operator=(Digitaliser const &rhs)
{
  if (this != &rhs)
    {
      // I'm not going to copy the mobs'list :)
    }
  return (*this);
}

Digitaliser::Mobs const		&Digitaliser::getMobs() const
{
  return (_mobs);
}

void				Digitaliser::setMobs(Mobs const &mobs)
{
  this->_mobs = mobs;
}

void				Digitaliser::addMob(Mob const &mob)
{
  _mobs.push_back(new Mob(mob));
}

bool				Digitaliser::serialization(Trame &trame) const
{
  bool				ret = true;
  int				nb = 0;
  std::ostringstream		str;

  trame["DIGITALISER"];
  for (auto it = this->_mobs.begin() ; it != this->_mobs.end() && ret; ++it)
    {
      str << "MOB" << nb;
      ret = (*it)->serialization(trame(trame["DIGITALISER"][str.str()]));
      str.str("");
      nb++;
    }
  return (ret);
}

Digitaliser			*Digitaliser::deserialization(Trame const &trame)
{
  Digitaliser			*digit = NULL;
  int				nb = 0;
  std::ostringstream		str;
  Mobs				*mobs;

  if (trame.isMember("DIGITALISER"))
    {
      digit = new Digitaliser;
      mobs = new Mobs;
      str << "MOB" << nb;
      for (; !trame["DIGITALISER"].isMember(str.str()) ; ++nb)
	{
	  mobs->push_back(Mob::deserialization(trame(trame["DIGITALISER"][str.str()])));
	  str.str("");
	  str << "MOB" << nb + 1;
	}
      digit->setMobs(*mobs);
    }
  return (digit);
}
