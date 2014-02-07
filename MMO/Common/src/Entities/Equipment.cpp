//
// Equipment.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Feb  6 16:28:56 2014 laurent ansel
// Last update Fri Feb  7 13:41:13 2014 laurent ansel
//

#include			<sstream>
#include			"Entities/Equipment.hh"

Equipment::Equipment()
{
}

Equipment::~Equipment()
{
}

Equipment::Equipment(Equipment const &rhs)
{
  *this = rhs;
}

Equipment			&Equipment::operator=(Equipment const &rhs)
{
  if (this != &rhs)
    {
      // I'm not going to copy the mobs'list :)
    }
  return (*this);
}

std::list<Stuff *> const	&Equipment::getStuffs() const
{
  return (this->_stuffs);
}

void				Equipment::setStuffs(std::list<Stuff *> const &list)
{
  this->_stuffs = list;
}

bool				Equipment::serialization(Trame &trame) const
{
  bool				ret = true;
  int				nb = 0;
  std::ostringstream		str;

  trame["EQUIPMENT"];
  for (auto it = this->_stuffs.begin() ; it != this->_stuffs.end() && ret; ++it)
    {
      str << "STUFF" << nb;
      ret = (*it)->serialization(trame(trame["EQUIPMENT"][str.str()]));
      str.str("");
      nb++;
    }
  return (ret);
}

Equipment			*Equipment::deserialization(Trame const &trame)
{
  Equipment			*equipment = NULL;
  int				nb = 0;
  std::ostringstream		str;
  std::list<Stuff *>		*stuffs;

  if (trame.isMember("EQUIPMENT"))
    {
      equipment = new Equipment;
      stuffs = new std::list<Stuff *>;
      str << "STUFF" << nb;
      for (; !trame["EQUIPMENT"].isMember(str.str()) ; ++nb)
	{
	  stuffs->push_back(Stuff::deserialization(trame(trame["EQUIPMENT"][str.str()])));
	  str.str("");
	  str << "STUFF" << nb + 1;
	}
      equipment->setStuffs(*stuffs);
    }
  return (equipment);
}
