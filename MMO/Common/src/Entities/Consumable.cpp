//
// Stuff.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Feb  6 15:41:23 2014 laurent ansel
// Last update Mon Feb 24 19:50:27 2014 laurent ansel
//

#include			"Entities/Consumable.hh"

Consumable::Consumable() :
  Persistent(),
  AItem("", AItem::eItem::CONSUMABLE),
  _consumableType(eConsumable::NONE)
{

}

Consumable::Consumable(std::string const &name, eConsumable const type) :
  Persistent(),
  AItem(name, AItem::eItem::CONSUMABLE),
  _consumableType(type)
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
    }
  return (*this);
}

Consumable::eConsumable		Consumable::getConsumableType() const
{
  return (_consumableType);
}

void				Consumable::setConsumableType(Consumable::eConsumable const consumableType)
{
  _consumableType = consumableType;
}

bool				Consumable::serialization(Trame &trame) const
{
  trame["TYPE"] = this->getItemType();
  trame["NAME"] = this->getName();
  trame["ID"] = static_cast<unsigned int>(this->getId());
  trame["CONSUTYPE"] = this->getConsumableType();
  return (true);
}

Consumable			*Consumable::deserialization(Trame const &trame, bool const client)
{
  Consumable			*consumable = NULL;

  consumable = new Consumable(trame["NAME"].asString(), static_cast<eConsumable>(trame["CONSUTYPE"].asInt()));
  if (client)
    consumable->setId(trame["ID"].asUInt());
  consumable->setItemType(static_cast<AItem::eItem>(trame["TYPE"].asInt()));
  return (consumable);
}
