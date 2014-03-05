//
// Digitaliser.cpp for Digitaliser in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Dec 10 15:19:56 2013 alexis mestag
// Last update Wed Mar  5 12:14:27 2014 laurent ansel
//

#include			<sstream>
#include			"Entities/Digitaliser.hh"

Digitaliser::Digitaliser() :
  ContainerWrapper<container_type>()
{

}

Digitaliser::Digitaliser(Digitaliser const &rhs) :
  ContainerWrapper<container_type>()
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
      // Je tuerai celui qui a fait ça (mestag_a)
      for (auto it = rhs.begin() ; it != rhs.end(); ++it)
      	this->getContainer().push_back(new Mob(**it));
      for (auto it = rhs.getBattleMobs().begin() ; it != rhs.getBattleMobs().end(); ++it)
      	this->_battleMobs.push_back(new Mob(**it));
    }
  return (*this);
}

Digitaliser::container_type const	&Digitaliser::getMobs() const
{
  return (this->getContainer());
}

void				Digitaliser::setMobs(Digitaliser::container_type const &mobs)
{
  this->setContainer(mobs);
}

Digitaliser::container_type const	&Digitaliser::getBattleMobs() const
{
  return (_battleMobs);
}

void				Digitaliser::setBattleMobs(Mobs const &mobs)
{
  this->_battleMobs = mobs;
}

void				Digitaliser::addMob(Mob const &mob)
{
  this->getContainer().push_back(new Mob(mob));
}

void				Digitaliser::addBattleMob(Mob const &mob)
{
  _battleMobs.push_back(new Mob(mob));
}

void				Digitaliser::battleMobtoMob(unsigned int const id)
{
  for (auto it = _battleMobs.begin() ; it != _battleMobs.end() ; ++it)
    {
      if ((*it)->getId() == id)
	{
	  _battleMobs.erase(it);
	  this->addMob(**it);
	  break;
	}
    }
}

void				Digitaliser::mobtoBattleMob(unsigned int const id)
{
  for (auto it = this->begin() ; it != this->end() ; ++it)
    {
      if ((*it)->getId() == id)
	{
	  this->getContainer().erase(it);
	  this->addBattleMob(**it);
	  break;
	}
    }
}

Mob				*Digitaliser::getMob(unsigned int const id) const
{
  for (auto it = _battleMobs.begin() ; it != _battleMobs.end() ; ++it)
    {
      if ((*it)->getId() == id)
	return (*it);
    }
  for (auto it = this->begin() ; it != this->end() ; ++it)
    {
      if ((*it)->getId() == id)
	return (*it);
    }
  return (NULL);
}

bool				Digitaliser::serialization(Trame &trame) const
{
  bool				ret = true;
  int				nb = 0;
  std::ostringstream		str;

  trame["DIGITALISER"];
  for (auto it = this->begin() ; it != this->end() && ret; ++it)
    {
      str << nb;
      ret = (*it)->serialization(trame(trame["DIGITALISER"]["LIST"][str.str()]));
      str.str("");
      nb++;
    }
  nb = 0;
  for (auto it = this->_battleMobs.begin() ; it != this->_battleMobs.end() && ret; ++it)
    {
      str << nb;
      ret = (*it)->serialization(trame(trame["DIGITALISER"]["BATTLE"][str.str()]));
      str.str("");
      nb++;
    }
  return (ret);
}

Digitaliser			*Digitaliser::deserialization(Trame const &trame)
{
  Digitaliser			*digit = NULL;
  Mobs				*mobs;
  Mobs				*battle;
  Mob				*tmp;

  if (trame.isMember("DIGITALISER"))
    {
      digit = new Digitaliser;
      mobs = new Mobs;
      battle = new Mobs;
      if (trame["DIGITALISER"].isMember("LIST"))
	{
	  auto			membersList = trame["DIGITALISER"]["LIST"].getMemberNames();

	  for (auto it = membersList.begin() ; it != membersList.end() ; ++it)
	    {
	      tmp = Mob::deserialization(trame(trame["DIGITALISER"]["LIST"][*it]));
	      if (tmp)
		mobs->push_back(tmp);
	    }
	}
      if (trame["DIGITALISER"].isMember("BATTLE"))
	{
	  auto			membersBattle = trame["DIGITALISER"]["BATTLE"].getMemberNames();

	  for (auto it = membersBattle.begin() ; it != membersBattle.end() ; ++it)
	    {
	      tmp = Mob::deserialization(trame(trame["DIGITALISER"]["BATTLE"][*it]));
	      if (tmp)
		mobs->push_back(tmp);
	    }
	}
      digit->setMobs(*mobs);
      digit->setBattleMobs(*battle);
    }
  return (digit);
}
