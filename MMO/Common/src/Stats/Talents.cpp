//
// Talents.cpp for Talents in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Mar  4 00:06:53 2014 alexis mestag
// Last update Thu Mar 20 23:34:24 2014 guillaume marescaux
//

#include				<sstream>
#include				<algorithm>
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

void					Talents::incCurrentPts(unsigned int const pts)
{
  _currentPts += pts;
}

void					Talents::decCurrentPts(unsigned int const pts)
{
  _currentPts -= pts >= _currentPts ? _currentPts : pts;
}

Talent const				*Talents::getTalentFromModel(TalentModel const &model) const
{
  std::function<bool(Talent *)>		talentSeeker = [&](Talent *t) -> bool {
    return (t->getModel() == model);
  };
  auto					it = std::find_if(this->begin(), this->end(), talentSeeker);
  Talent const				*ret = NULL;

  if (it != this->end())
    ret = *it;
  return (ret);
}

Talent					*Talents::getTalentFromModel(TalentModel const &model)
{
  std::function<bool(Talent *)>		talentSeeker = [&](Talent *t) -> bool {
    return (t->getModel() == model);
  };
  auto					it = std::find_if(this->begin(), this->end(), talentSeeker);
  Talent				*ret = NULL;

  if (it != this->end())
    ret = *it;
  return (ret);
}

bool					Talents::incTalent(TalentModel const &model)
{
  Talent				*talent = this->getTalentFromModel(model);
  bool					ret = false;

  if (this->getCurrentPts()) {
    if (!talent)
      {
	talent = new Talent(model, 1);
	this->getContainer().push_back(talent);
      }
    else
      talent->addPts(1);
    this->decCurrentPts(1);
    ret = true;
  }
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

  trame["TALENTS"]["PTS"] = this->getCurrentPts();
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
      if (*it != "PTS")
	{
	  tmp = Talent::deserialization(trame(trame["TALENTS"][*it]));
	  if (tmp)
	    talents->getContainer().push_back(tmp);
	}
    }
  talents->setCurrentPts(trame["TALENTS"]["PTS"].asUInt());
  return (talents);
}
