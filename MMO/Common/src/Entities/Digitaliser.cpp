//
// Digitaliser.cpp for Digitaliser in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Dec 10 15:19:56 2013 alexis mestag
// Last update Mon Mar 24 16:01:26 2014 guillaume marescaux
//

#include			<sstream>
#include			<functional>
#include			"Entities/Digitaliser.hh"

Digitaliser::Digitaliser(Player const *player) :
  ContainerWrapper<container_type>(),
  _player(player),
  _efficiency(1)
{

}

Digitaliser::Digitaliser(Digitaliser const &rhs) :
  ContainerWrapper<container_type>()
{
  *this = rhs;
}

Digitaliser::~Digitaliser()
{
  this->deleteMobs(this->getContainer());
  this->deleteMobs(this->_battleMobs);
}

Digitaliser			&Digitaliser::operator=(Digitaliser const &rhs)
{
  if (this != &rhs)
    {
      // Je tuerai celui qui a fait ça (mestag_a)
      // for (auto it = rhs.begin() ; it != rhs.end(); ++it)
      // 	this->getContainer().push_back(new Mob(**it));
      // for (auto it = rhs.getBattleMobs().begin() ; it != rhs.getBattleMobs().end(); ++it)
      // 	this->_battleMobs.push_back(new Mob(**it));
      this->setContainer(rhs.getContainer());
      this->_battleMobs = rhs.getBattleMobs();
      this->setPlayer(rhs.getPlayer());
      this->setEfficiency(rhs.getEfficiency());
    }
  return (*this);
}

void				Digitaliser::setPlayer(Player const *player)
{
  _player = player;
}

Player const			*Digitaliser::getPlayer() const
{
  return (_player);
}

double				Digitaliser::getEfficiency() const
{
  return (_efficiency);
}

void				Digitaliser::setEfficiency(double const efficiency)
{
  _efficiency = efficiency;
}

Digitaliser::container_type const	&Digitaliser::getMobs() const
{
  return (this->getContainer());
}

unsigned int			Digitaliser::getLimit() const
{
  if (_player)
    return (_player->getStat("Limit mob"));
  return (0);
}

void				Digitaliser::setMobs(Digitaliser::container_type const &mobs)
{
  this->setContainer(mobs);
}

Digitaliser::container_type const	&Digitaliser::getBattleMobs() const
{
  return (_battleMobs);
}

Digitaliser::container_type		&Digitaliser::getBattleMobs()
{
  return (_battleMobs);
}

void				Digitaliser::setBattleMobs(Mobs const &mobs)
{
  this->_battleMobs = mobs;
}

void				Digitaliser::addMob(Mob &mob)
{
  this->getContainer().push_back(&mob);
}

Mob				*Digitaliser::getAndDeleteMob(unsigned int const id)
{
  Mob				*mob;

  for (auto it = this->_battleMobs.begin() ; it != this->_battleMobs.end() ; ++it)
    {
      if ((*it)->getId() == id)
	{
	  mob = *it;
	  this->getContainer().erase(it);
	  return (mob);
	}
    }
  for (auto it = this->begin() ; it != this->end() ; ++it)
    {
      if ((*it)->getId() == id)
	{
	  mob = *it;
	  this->getContainer().erase(it);
	  return (mob);
	}
    }
  return (NULL);
}

void				Digitaliser::addBattleMob(Mob &mob)
{
  _battleMobs.push_back(&mob);
}

bool				Digitaliser::battleMobtoMob(unsigned int const id)
{
  if (_battleMobs.size() > 1)
    {
      for (auto it = _battleMobs.begin() ; it != _battleMobs.end() ; ++it)
	{
	  if ((*it)->getId() == id)
	    {
	      this->addMob(**it);
	      _battleMobs.erase(it);
	      return (true);
	    }
	}
    }
  return (false);
}

bool				Digitaliser::mobtoBattleMob(unsigned int const id)
{
  if (_battleMobs.size() < this->getLimit())
    {
      for (auto it = this->begin() ; it != this->end() ; ++it)
	{
	  if ((*it)->getId() == id)
	    {
	      this->addBattleMob(**it);
	      this->getContainer().erase(it);
	      return (true);
	    }
	}
    }
  return (false);
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

void				Digitaliser::deleteMobs(container_type &c)
{
  static std::function<bool(Mob *)>	mobDeleter = [](Mob *m) -> bool {
    delete m;
    return (true);
  };

  c.remove_if(mobDeleter);
}

#include			<algorithm>

bool				Digitaliser::switchMobs(unsigned int const id1, unsigned int const id2)
{
  auto				mob1 = this->begin();
  bool				setMob1 = false;
  auto				mob2 = this->begin();
  bool				setMob2 = false;
  Mob				*tmp;

  for (auto it = this->begin() ; it != this->end() && (!setMob1 || !setMob2); ++it)
    {
      if ((*it)->getId() == id1)
  	{
  	  setMob1 = true;
  	  mob1 = it;
  	}
      if ((*it)->getId() == id2)
  	{
  	  setMob2 = true;
  	  mob2 = it;
  	}
    }
  for (auto it = this->_battleMobs.begin() ; it != this->_battleMobs.end() && (!setMob1 || !setMob2) ; ++it)
    {
      if ((*it)->getId() == id1)
  	{
  	  setMob1 = true;
  	  mob1 = it;
  	}
      if ((*it)->getId() == id2)
  	{
  	  setMob2 = true;
  	  mob2 = it;
  	}
    }
  if (setMob1 && setMob2)
    {
      tmp = *mob1;
      *mob1 = *mob2;
      *mob2 = tmp;
    }
  return (false);
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
      digit = new Digitaliser(NULL);
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
		battle->push_back(tmp);
	    }
	}
      digit->setMobs(*mobs);
      digit->setBattleMobs(*battle);
    }
  return (digit);
}
