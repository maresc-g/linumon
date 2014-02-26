//
// Mob.cpp for Mob in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Dec  5 20:42:03 2013 alexis mestag
// Last update Wed Feb 26 11:15:26 2014 laurent ansel
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

Mob::Mob(MobModel const &model, unsigned int const level) :
  Persistent(), ACharacter(model.getName(), eCharacter::MOB)
{
  this->setModel(model);
  this->setLevel(Level(level));
}

Mob::~Mob()
{

}

Mob				&Mob::operator=(Mob const &rhs)
{
  if (this != &rhs)
    {
      this->setModel(rhs.getModel());
      this->setLevel(rhs.getLevel());
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

bool				Mob::serialization(Trame &trame) const
{
  bool				ret = true;

  this->getStats().serialization(trame(trame["STATS"]));
  this->getTmpStats().serialization(trame(trame["TMPSTATS"]));
  trame["NAME"] = this->getName();
  trame["ID"] = static_cast<unsigned int>(this->getId());
  this->getLevel().serialization(trame(trame["LEVEL"]));
  this->getModel().serialization(trame);
  return (ret);
}

Mob				*Mob::deserialization(Trame const &trame)
{
  Mob				*mob = new Mob;

  mob->setStats(*Stats::deserialization(trame));
  mob->setTmpStats(*Stats::deserialization(trame));
  mob->setLevel(*Level::deserialization(trame(trame["LEVEL"])));
  mob->setName(trame["NAME"].asString());
  mob->setId(trame["ID"].asUInt());
  mob->setModel(*MobModel::deserialization(trame));
  return (mob);
}
