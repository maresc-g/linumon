//
// MobModel.cpp for MobModel in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Fri Jan 24 18:39:45 2014 alexis mestag
// Last update Wed Mar  5 14:58:01 2014 laurent ansel
//

#include			"Entities/MobModel.hh"

MobModel::MobModel() :
  Persistent(), AStatEntity("", eStatEntity::MOBMODEL),
  _spells(new Spells)
{

}

MobModel::MobModel(MobModel const &rhs) :
  Persistent(rhs), AStatEntity(rhs),
  _spells(new Spells)
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
  return (*_spells);
}

void				MobModel::setSpells(Spells const &spells)
{
  *this->_spells = spells;
}

bool				MobModel::serialization(Trame &trame) const
{
  bool				ret = true;

  this->getType().serialization(trame(trame));
  this->getStats().serialization(trame(trame["STATS"]));
  this->getSpells().serialization(trame(trame));
  return (ret);
}

MobModel			*MobModel::deserialization(Trame const &trame)
{
  MobModel			*model = NULL;

  model = new MobModel;
  model->setType(*Type::deserialization(trame(trame)));
  model->setSpells(*Spells::deserialization(trame(trame)));
  model->setStats(*Stats::deserialization(trame(trame)));
  return (model);
}
