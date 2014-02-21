//
// MobModel.cpp for MobModel in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Fri Jan 24 18:39:45 2014 alexis mestag
// Last update Fri Feb 21 13:56:21 2014 laurent ansel
//

#include			"Entities/MobModel.hh"

MobModel::MobModel() :
  Persistent(), AStatEntity("", eStatEntity::MOBMODEL)
{

}

MobModel::MobModel(MobModel const &rhs) :
  Persistent(rhs), AStatEntity(rhs)
{
  *this = rhs;
}

MobModel::~MobModel()
{

}

MobModel			&MobModel::operator=(MobModel const &rhs)
{
  if (this != &rhs)
    {
      this->setType(rhs.getType());
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

Spells const			&MobModel::getSpells() const
{
  return (_spells);
}

void				MobModel::setSpells(Spells const &spells)
{
  this->_spells = spells;
}

bool				MobModel::serialization(Trame &trame) const
{
  bool				ret = true;

  this->getType().serialization(trame(trame["MOBMODEL"]));
  this->getStats().serialization(trame(trame["MOBMODEL"]));
  this->getSpells().serialization(trame(trame["MOBMODEL"]));
  return (ret);
}

MobModel			*MobModel::deserialization(Trame const &trame)
{
  MobModel			*model = NULL;

  if (trame.isMember("MOBMODEL"))
    {
      model = new MobModel;
      model->setType(*Type::deserialization(trame(trame["MOBMODEL"])));
      model->setSpells(*Spells::deserialization(trame(trame["MOBMODEL"])));
      model->setStats(*Stats::deserialization(trame(trame["MOBMODEL"])));
    }
  return (model);
}
