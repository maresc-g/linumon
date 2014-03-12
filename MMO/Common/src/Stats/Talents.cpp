//
// Talents.cpp for Talents in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Mar  4 00:06:53 2014 alexis mestag
// Last update Wed Mar 12 13:22:30 2014 laurent ansel
//

#include				<sstream>
#include				<functional>
#include				"Stats/Talents.hh"

Talents::Talents() :
  ContainerWrapper<container_type>(),
  _currentPts(0)
{

}

Talents::Talents(Talents const &rhs) :
  ContainerWrapper<container_type>(),
  _currentPts(0)
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
      this->setCurrentPts(rhs.getCurrentPts());
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

unsigned int				Talents::getCurrentPts() const
{
  return (_currentPts);
}

void					Talents::setCurrentPts(unsigned int const pts)
{
  _currentPts = pts;
}

bool					Talents::modifyTalent(unsigned int const pts, TalentModel const &talent)
{
  bool					ret = false;
  auto					it = this->begin();
  Talent				*tmp = NULL;

  for ( ; it != this->end() && &(*it)->getModel() != &talent; ++it);
  if (it == this->end())
    {
      tmp = new Talent(talent, 0);
      this->getContainer().push_back(tmp);
    }
  else
    tmp = *it;
  ret = tmp->addPts(pts);
  return (ret);
}

void					Talents::apply(Player &)
{

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
