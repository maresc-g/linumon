//
// Stuff.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Feb  6 15:41:23 2014 laurent ansel
// Last update Tue Feb 11 15:55:16 2014 alexis mestag
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
  trame["CONSUMABLE"]["TYPE"] = this->getItemType();
  trame["CONSUMABLE"]["NAME"] = this->getName();
  trame["CONSUMABLE"]["ID"] = static_cast<unsigned int>(this->getId());
  trame["CONSUMABLE"]["TYPE"] = this->getConsumableType();
  return (false);
}

Consumable			*Consumable::deserialization(Trame const &trame)
{
  Consumable			*consumable = NULL;

  if (trame.isMember("CONSUMABLE"))
    {
      consumable = new Consumable(trame["CONSUMABLE"]["NAME"].asString(), static_cast<eConsumable>(trame["CONSUMABLE"]["TYPE"].asInt()));
      consumable->setId(trame["CONSUMABLE"]["ID"].asUInt());
      consumable->setItemType(static_cast<AItem::eItem>(trame["CONSUMABLE"]["TYPE"].asInt()));
    }
  return (consumable);
}
