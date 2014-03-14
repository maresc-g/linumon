//
// MobModel.cpp for MobModel in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Fri Jan 24 18:39:45 2014 alexis mestag
// Last update Fri Mar 14 21:04:37 2014 laurent ansel
//

#include			"Entities/MobModel.hh"
#include			"Loader/LoaderManager.hh"

MobModel::MobModel() :
  Persistent(), AStatEntity("", eStatEntity::MOBMODEL),
  _spells(new Spells), _expCurve(NULL), _carcass(NULL)
{

}

MobModel::MobModel(MobModel const &rhs) :
  Persistent(rhs), AStatEntity(rhs),
  _spells(new Spells), _expCurve(NULL), _carcass(NULL)
{
  *this = rhs;
}

MobModel::~MobModel()
{
  delete _spells;
}

MobModel			&MobModel::operator=(MobModel const &rhs)
{
  if (this != &rhs)
    {
      this->setType(rhs.getType());
      this->setSpells(rhs.getSpells());
      this->setExperienceCurve(rhs.getExperienceCurve());
      this->setCarcass(rhs.getCarcass());
    }
  return (*this);
}

Type const			&MobModel::getType() const
{
  return (*_type);
}

void				MobModel::setType(Type const &type)
{
  _type = &type;
}

Carcass const			&MobModel::getCarcass() const
{
  return (*_carcass);
}

void				MobModel::setCarcass(Carcass const &carcass)
{
  _carcass = &carcass;
}

Spells const			&MobModel::getSpells() const
{
  return (*_spells);
}

void				MobModel::setSpells(Spells const &spells)
{
  *this->_spells = spells;
}

ExperienceCurve const		&MobModel::getExperienceCurve() const
{
  return (*_expCurve);
}

void				MobModel::setExperienceCurve(ExperienceCurve const &expCurve)
{
  _expCurve = &expCurve;
}

bool				MobModel::serialization(Trame &trame) const
{
  bool				ret = true;

  this->getType().serialization(trame(trame));
  this->getStats().serialization(trame(trame["STATS"]));
  this->getSpells().serialization(trame(trame));
  trame["KEY"] = this->getAuthorizedStatKeys().getName();
  trame["CAR"] = this->_carcass->getName();
  return (ret);
}

MobModel			*MobModel::deserialization(Trame const &trame)
{
  MobModel			*model = NULL;

  model = new MobModel;
  if (trame.isMember("KEY"))
    model->setAuthorizedStatKeys(*(**LoaderManager::getInstance()->getAuthorizedStatKeyLoader())->getValue(trame["KEY"].asString()));

  if (trame.isMember("CAR"))
    model->setCarcass(*(**LoaderManager::getInstance()->getCarcassLoader())->getValue(trame["CAR"].asString()));
  model->setType(*Type::deserialization(trame(trame)));
  model->setSpells(*Spells::deserialization(trame(trame)));
  model->setStats(*Stats::deserialization(trame(trame["STATS"])));
  return (model);
}
