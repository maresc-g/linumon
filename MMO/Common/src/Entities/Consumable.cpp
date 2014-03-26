//
// Stuff.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Feb  6 15:41:23 2014 laurent ansel
// Last update Wed Mar 26 09:17:38 2014 alexis mestag
//

#include			"Entities/Consumable.hh"
#include			"Effects/MobEffect.hh"
#include			"Effects/PlayerEffect.hh"

Consumable::Consumable() :
  Persistent(),
  AItem("", AItem::eItem::CONSUMABLE),
  _consumableType(eConsumable::NONE),
  _forMob(false)
{

}

Consumable::Consumable(std::string const &name, eConsumable const type, bool const forMob) :
  Persistent(),
  AItem(name, AItem::eItem::CONSUMABLE),
  _consumableType(type),
  _forMob(forMob)
{

}

Consumable::Consumable(Consumable const &rhs) :
  Persistent(rhs),
  AItem(rhs.getName(), AItem::eItem::CONSUMABLE)
{
  *this = rhs;
}

Consumable::~Consumable()
{

}

Consumable			&Consumable::operator=(Consumable const &rhs)
{
  if (this != &rhs)
    {
      this->setConsumableType(rhs.getConsumableType());
#ifndef				CLIENT_COMPILATION
      this->setEffectLib(rhs.getEffectLib());
#endif
      this->setForMob(rhs.isForMob());
    }
  return (*this);
}

#ifndef				CLIENT_COMPILATION
EffectLib const			&Consumable::getEffectLib() const
{
  return (*_effectLib);
}

void				Consumable::setEffectLib(EffectLib const &effectLib)
{
  _effectLib = &effectLib;
}

void				Consumable::applyEffect(Mob &mob) const
{
  MobEffect			*effect = dynamic_cast<MobEffect *>(_effectLib->getEffect());

  if (effect) {
    effect->apply(mob);
  }
  else
    std::cerr << "Bad cast in Consumable::applyEffect()" << std::endl;
  delete effect;
}

void				Consumable::applyEffect(Player &player) const
{
  PlayerEffect		*effect = dynamic_cast<PlayerEffect *>(this->getEffectLib().getEffect());

  if (effect) {
    effect->apply(player);
  }
  else
    std::cerr << "Bad cast in Consumable::applyEffect()" << std::endl;
}
#endif

Consumable::eConsumable		Consumable::getConsumableType() const
{
  return (_consumableType);
}

void				Consumable::setConsumableType(Consumable::eConsumable const consumableType)
{
  _consumableType = consumableType;
}

bool				Consumable::isForMob() const
{
  return (_forMob);
}

void				Consumable::setForMob(bool const forMob)
{
  _forMob = forMob;
}

bool				Consumable::serialization(Trame &trame) const
{
  trame["TYPE"] = this->getItemType();
  trame["NAME"] = this->getName();
  trame["ID"] = static_cast<unsigned int>(this->getId());
  trame["CONS"] = this->getConsumableType();
  trame["FORMOB"] = this->isForMob();
  return (true);
}

Consumable			*Consumable::deserialization(Trame const &trame, bool const client)
{
  Consumable			*consumable = NULL;

  if (trame["TYPE"].asInt() == AItem::eItem::CONSUMABLE)
    {
      consumable = new Consumable(trame["NAME"].asString(), static_cast<eConsumable>(trame["CONS"].asInt()));
      if (client)
	consumable->setId(trame["ID"].asUInt());
      consumable->setItemType(static_cast<AItem::eItem>(trame["TYPE"].asInt()));
      consumable->setForMob(trame["FORMOB"].asBool());
    }
  return (consumable);
}
