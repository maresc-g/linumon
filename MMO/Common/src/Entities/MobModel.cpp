//
// MobModel.cpp for MobModel in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Fri Jan 24 18:39:45 2014 alexis mestag
// Last update Tue Jan 28 11:11:23 2014 laurent ansel
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

bool				MobModel::serialization(Trame &) const
{
  bool				ret = false;
  return (ret);
}

MobModel			*MobModel::deserialization(Trame const &)
{
  MobModel			*model = NULL;
  return (model);
}
