//
// Equipment.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Feb  6 16:28:56 2014 laurent ansel
// Last update Wed Mar 26 13:40:35 2014 alexis mestag
//

#include			<sstream>
#include			"Entities/Equipment.hh"
#include			"Loader/LoaderManager.hh"

Equipment::Equipment() :
  ContainerWrapper<container_type>()
{
}

Equipment::Equipment(Equipment const &rhs) :
  ContainerWrapper<container_type>()
{
  *this = rhs;
}

Equipment::~Equipment()
{
}

Equipment			&Equipment::operator=(Equipment const &rhs)
{
  if (this != &rhs)
    {
      this->setStuffs(rhs.getStuffs());
    }
  return (*this);
}

Equipment::container_type const	&Equipment::getStuffs() const
{
  return (this->getContainer());
}

void				Equipment::setStuffs(container_type const &list)
{
  this->setContainer(list);
}

bool				Equipment::addStuff(Stuff *newStuff, Stuff *&oldStuff)
{
  bool				ret = false;
  auto				it = this->begin();

  if ((it = this->getContainer().find(newStuff->getStuffType())) != this->end())
    {
      ret = true;
      oldStuff = it->second;
      it->second = newStuff;
    }
  else
    {
      ret = true;
      oldStuff = NULL;
      this->getContainer()[newStuff->getStuffType()] = newStuff;
    }
  return (ret);
}

bool				Equipment::addStuff(Stuff::eStuff const type, Stuff *&oldStuff)
{
  bool				ret = false;
  auto				it = this->begin();

  if ((it = this->getContainer().find(type)) != this->end())
    {
      ret = true;
      oldStuff = it->second;
      it->second = NULL;
    }
  else
    ret = false;
  return (ret);
}

bool				Equipment::getStuff(Stuff *&oldStuff, unsigned int const idItem)
{
  bool				ret = false;

  oldStuff = NULL;
  std::cout << "Equipment::getStuff size = " << this->size() << std::endl;
  for (auto it = this->begin() ; it != this->end() && !ret ; ++it)
    {
      if (it->second)
	std::cout << "ID ITEM = " << idItem << " ID = " << it->second->getId() << std::endl;
      else
	std::cout << "IT SECOND IS NULL" << std::endl;
      if (it->second && it->second->getId() == idItem)
	{
	  ret = true;
	  oldStuff = it->second;
	  it->second = NULL;
	}
    }
  return (ret);
}

bool				Equipment::stuffExists(Stuff::eStuff const type) const
{
  auto				it = this->begin();

  if ((it = this->getContainer().find(type)) != this->end() && it->second)
    return (true);
  return (false);
}

Stuff const			&Equipment::getStuff(Stuff::eStuff const type) const
{
  return (*(this->getContainer().find(type)->second));
}

bool				Equipment::serialization(Trame &trame) const
{
  bool				ret = true;
  int				nb = 0;
  std::ostringstream		str;

  trame["EQUIP"];
  for (auto it = this->begin() ; it != this->end() && ret; ++it)
    {
      if (it->second)
	{
	  str << it->first;
	  //      ret = it->second->serialization(trame(trame["EQUIP"][str.str()]));
	  trame["EQUIP"][str.str()] = it->second->getName();
	  str.str("");
	  nb++;
	}
    }
  return (ret);
}

Equipment			*Equipment::deserialization(Trame const &trame)
{
  Equipment			*equipment = NULL;
  container_type		*stuffs;
  Stuff				*tmp;

  if (trame.isMember("EQUIP"))
    {
      equipment = new Equipment;
      stuffs = new container_type;
      auto			members = trame["EQUIP"].getMemberNames();

      for (auto it = members.begin() ; it != members.end() ; ++it)
	{
	  //Stuff::deserialization(trame(trame["EQUIP"][*it]));
	  tmp = (**LoaderManager::getInstance()->getStuffLoader())->getValue(trame["EQUIP"][*it].asString());
	  if (tmp)
	    (*stuffs)[tmp->getStuffType()] = tmp;
	}
      equipment->setStuffs(*stuffs);
    }
  return (equipment);
}
