//
// Mob.cpp for Mob in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Dec  5 20:42:03 2013 alexis mestag
// Last update Mon Mar  3 20:43:58 2014 alexis mestag
//

#include			"Entities/Mob.hh"

Mob::Mob() :
  Persistent(), ACharacter("", eCharacter::MOB)
{

}

Mob::Mob(Mob const &rhs) :
  Persistent(rhs), ACharacter(rhs)
{
  *this = rhs;
}

Mob::Mob(MobModel const &model, Level::type const level) :
  Persistent(), ACharacter(model.getName(), eCharacter::MOB)
{
  this->setModel(model);
  this->setLevel(level);
}

Mob::~Mob()
{

}

Mob				&Mob::operator=(Mob const &rhs)
{
  if (this != &rhs)
    {
      this->setModel(rhs.getModel());
      this->setId(rhs.getId());
      // this->setStats(rhs.getStats());
    }
  return (*this);
}

MobModel const			&Mob::getModel() const
{
  return (*_model);
}

void				Mob::setModel(MobModel const &model)
{
  _model = &model;
}

Type const			&Mob::getType() const
{
  return (this->getModel().getType());
}

bool				Mob::serialization(Trame &trame) const
{
  bool				ret = true;

  this->getStats().serialization(trame(trame["STATS"]));
  this->getTmpStats().serialization(trame(trame["TMP"]));
  trame["NAME"] = this->getName();
  trame["ID"] = static_cast<unsigned int>(this->getId());
  this->getLevelObject().serialization(trame(trame["LEVEL"]));
  this->getModel().serialization(trame);
  return (ret);
}

Mob				*Mob::deserialization(Trame const &trame)
{
  Mob				*mob = new Mob;

  mob->setStats(*Stats::deserialization(trame));
  mob->setTmpStats(*Stats::deserialization(trame));
  mob->setLevelObject(*Level::deserialization(trame(trame["LEVEL"])));
  mob->setName(trame["NAME"].asString());
  mob->setId(trame["ID"].asUInt());
  mob->setModel(*MobModel::deserialization(trame));
  return (mob);
}
