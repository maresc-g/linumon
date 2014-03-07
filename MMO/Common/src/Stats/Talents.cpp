//
// Talents.cpp for Talents in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Mar  4 00:06:53 2014 alexis mestag
// Last update Fri Mar  7 16:39:44 2014 laurent ansel
//

#include				<sstream>
#include				<functional>
#include				"Stats/Talents.hh"

Talents::Talents() :
  ContainerWrapper<container_type>()
{

}

Talents::Talents(Talents const &rhs) :
  ContainerWrapper<container_type>()
{
  *this = rhs;
}

Talents::~Talents()
{
  this->deleteTalents();
}

Talents					&Talents::operator=(Talents const &rhs)
{
  if (this != &rhs)
    {
      this->setTalents(rhs.getTalents());
    }
  return (*this);
}

Talents::container_type const		&Talents::getTalents() const
{
  return (this->getContainer());
}

void					Talents::setTalents(container_type const &talents)
{
  this->setContainer(talents);
}

void					Talents::deleteTalents()
{
  static std::function<bool(Talent *)>	talentDeleter = [](Talent *t) -> bool {
    delete t;
    return (true);
  };

  this->getContainer().remove_if(talentDeleter);
}

bool				Talents::serialization(Trame &trame) const
{
  bool				ret = true;
  std::ostringstream		str;
  unsigned int			nb = 0;

  for (auto it = this->begin() ; it != this->end() ; ++it)
    {
      str << nb;
      (*it)->serialization(trame(trame["TALENTS"][str.str()]));
      str.str("");
      nb++;
    }
  return (ret);
}

Talents				*Talents::deserialization(Trame const &trame)
{
  Talents			*talents = new Talents;
  auto				members = trame["TALENTS"].getMemberNames();
  Talent			*tmp;

  for (auto it = members.begin() ; it != members.end() ; ++it)
    {
      tmp = Talent::deserialization(trame(trame["TALENTS"][*it]));
      if (tmp)
	talents->getContainer().push_back(tmp);
    }
  return (talents);
}
