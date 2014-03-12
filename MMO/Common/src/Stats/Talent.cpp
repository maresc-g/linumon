//
// Talent.cpp for Talent in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Fri Jan 31 14:51:25 2014 alexis mestag
// Last update Wed Mar 12 13:29:52 2014 laurent ansel
//

#include			"Stats/Talent.hh"
#ifndef			CLIENT_COMPILATION
# include		"Stats/Talent-odb.hxx"
# include		"Database/Database.hpp"
#endif
#include			"Loader/LoaderManager.hh"

Talent::Talent() :
  Persistent(), _model(NULL), _currentPoints(0)
{

}

Talent::Talent(TalentModel const &model, int const currentPoints) :
  Persistent(), _model(&model), _currentPoints(currentPoints)
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

bool				Talent::addPts(unsigned int const pts)
{
  bool				ret = false;

  if (pts + _currentPoints <= static_cast<unsigned int>(_model->getMaxPoints()))
    {
      _currentPoints += pts;
      ret = true;
    }
  return (ret);
}

bool				Talent::serialization(Trame &trame) const
{
  bool				ret = true;

  trame["PTS"] = this->_currentPoints;
  trame["NAME"] = this->_model->getName();
  //  this->_model->serialization(trame(trame[this->_model->getName()]));
  return (ret);
}

Talent				*Talent::deserialization(Trame const &trame)
{
  Talent			*talent = new Talent;
  TalentModel			*model;

  talent->setCurrentPoints(trame["PTS"].asUInt());
  //  model = TalentModel::deserialization(trame(trame["TALENT"][*it]));
  //  model->setName(*it);
  model = (**LoaderManager::getInstance()->getTalentModelLoader())->getValue(trame["NAME"].asString());
  if (model)
    talent->setModel(*model);
  return (talent);
}
