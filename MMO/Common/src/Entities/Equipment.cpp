//
// Equipment.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Feb  6 16:28:56 2014 laurent ansel
// Last update Mon Feb 24 14:25:37 2014 alexis mestag
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
      this->setStuffs(rhs.getStuffs());
    }
  return (*this);
}

std::map<Stuff::eStuff, Stuff *> const	&Equipment::getStuffs() const
{
  return (this->_stuffs);
}

void				Equipment::setStuffs(std::map<Stuff::eStuff, Stuff *> const &list)
{
  this->_stuffs = list;
}

bool				Equipment::addStuff(Stuff *newStuff, Stuff *&oldStuff)
{
  bool				ret = false;
  auto				it = this->_stuffs.begin();

  if ((it = this->_stuffs.find(newStuff->getStuffType())) != this->_stuffs.end())
    {
      if (it->second)
	{
	  ret = true;
	  oldStuff = it->second;
	  it->second = newStuff;
	}
      else
	ret = false;
    }
  else
    ret = false;
  return (ret);
}

bool				Equipment::addStuff(Stuff::eStuff const type, Stuff *&oldStuff)
{
  bool				ret = false;
  auto				it = this->_stuffs.begin();

  if ((it = this->_stuffs.find(type)) != this->_stuffs.end())
    {
      if (it->second)
	{
	  ret = true;
	  oldStuff = it->second;
	  it->second = NULL;
	}
      else
	ret = false;
    }
  else
    ret = false;
  return (ret);
}

bool				Equipment::getStuff(Stuff *&oldStuff, unsigned int const idItem)
{
  bool				ret = false;

  for (auto it = this->_stuffs.begin() ; it != this->_stuffs.end() && !ret ; ++it)
    {
      if (it->second && it->second->getId() == idItem)
	{
	  ret = true;
	  oldStuff = it->second;
	  it->second = NULL;
	}
    }
  return (ret);
}

bool				Equipment::serialization(Trame &trame) const
{
  bool				ret = true;
  int				nb = 0;
  std::ostringstream		str;

  trame["EQUIPMENT"];
  for (auto it = this->_stuffs.begin() ; it != this->_stuffs.end() && ret; ++it)
    {
      str << it->first;
      ret = it->second->serialization(trame(trame["EQUIPMENT"][str.str()]));
      str.str("");
      nb++;
    }
  return (ret);
}

Equipment			*Equipment::deserialization(Trame const &trame)
{
  Equipment			*equipment = NULL;
  std::map<Stuff::eStuff, Stuff *>	*stuffs;
  Stuff				*tmp;

  if (trame.isMember("EQUIPMENT"))
    {
      equipment = new Equipment;
      stuffs = new std::map<Stuff::eStuff, Stuff *>;
      auto			members = trame["EQUIPMENT"].getMemberNames();

      for (auto it = members.begin() ; it != members.end() ; ++it)
	{
	  tmp = Stuff::deserialization(trame(trame["EQUIPMENT"][*it]));
	  if (tmp)
	    (*stuffs)[tmp->getStuffType()] = tmp;
	}
      equipment->setStuffs(*stuffs);
    }
  return (equipment);
}
