//
// Talent.cpp for Talent in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Fri Jan 31 14:51:25 2014 alexis mestag
// Last update Fri Mar  7 16:32:54 2014 alexis mestag
//

#include			"Stats/Talent.hh"
#ifndef			CLIENT_COMPILATION
# include		"Stats/Talent-odb.hxx"
# include		"Database/Database.hpp"
#endif

Talent::Talent() :
  Persistent(), _model(NULL), _currentPoints(0)
{

}

Talent::Talent(Talent const &rhs) :
  Persistent()
{
  *this = rhs;
}

Talent::~Talent()
{
#ifndef			CLIENT_COMPILATION
  Repository<Talent>	*rt = &Database::getRepository<Talent>();
  rt->removeFromCache(*this);
#endif
}

Talent				&Talent::operator=(Talent const &rhs)
{
  if (this != &rhs)
    {
      this->setModel(rhs.getModel());
      this->setCurrentPoints(rhs.getCurrentPoints());
    }
  return (*this);
}

TalentModel const		&Talent::getModel() const
{
  return (*_model);
}

void				Talent::setModel(TalentModel const &model)
{
  _model = &model;
}

int				Talent::getCurrentPoints() const
{
  return (_currentPoints);
}

void				Talent::setCurrentPoints(int const currentPoints)
{
  _currentPoints = currentPoints;
}

bool				Talent::serialization(Trame &trame) const
{
  bool				ret = true;

  trame[this->_model->getName()]["PTS"] = this->_currentPoints;
  this->_model->serialization(trame(trame[this->_model->getName()]));
  return (ret);
}

Talent				*Talent::deserialization(Trame const &trame)
{
  Talent			*talent = new Talent;
  TalentModel			*model;
  auto				members = trame["TALENT"].getMemberNames();

  for (auto it = members.begin() ; it != members.end() ; ++it)
    {
      model = NULL;
      if ((*it) == "PTS")
	talent->setCurrentPoints(trame["TALENT"][*it]["PTS"].asInt());
      else
	{
	  model = TalentModel::deserialization(trame(trame["TALENT"][*it]));
	  model->setName(*it);
	  talent->setModel(*model);
	}
    }
  return (talent);
}
