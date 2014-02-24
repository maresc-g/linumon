//
// Stuff.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Feb  6 15:41:23 2014 laurent ansel
// Last update Mon Feb 24 13:06:55 2014 laurent ansel
//

#include			"Entities/Stuff.hh"

Stuff::Stuff() :
  Persistent(),
  AItem("", AItem::eItem::STUFF),
  _stuffType(eStuff::NONE)
{

}

Stuff::Stuff(std::string const &name, eStuff const type) :
  Persistent(),
  AItem(name, AItem::eItem::STUFF),
  _stuffType(type)
{

}

Stuff::Stuff(Stuff const &rhs) :
  Persistent(rhs),
  AItem(rhs.getName(), AItem::eItem::STUFF)
{
  *this = rhs;
}

Stuff::~Stuff()
{

}

Stuff				&Stuff::operator=(Stuff const &rhs)
{
  if (this != &rhs)
    {
      this->setStuffType(rhs.getStuffType());
    }
  return (*this);
}

Stuff::eStuff			Stuff::getStuffType() const
{
  return (_stuffType);
}

void				Stuff::setStuffType(Stuff::eStuff const stuffType)
{
  _stuffType = stuffType;
}

bool				Stuff::serialization(Trame &trame) const
{
  trame["TYPE"] = this->getItemType();
  trame["NAME"] = this->getName();
  // trame["ID"] = static_cast<unsigned int>(this->getId());
  trame["STUFFTYPE"] = this->getStuffType();
  return (true);
}

Stuff				*Stuff::deserialization(Trame const &trame)
{
  Stuff				*stuff = NULL;

  stuff = new Stuff(trame["NAME"].asString(), static_cast<eStuff>(trame["STUFFTYPE"].asInt()));
  // stuff->setId(trame["ID"].asUInt());
  stuff->setItemType(static_cast<AItem::eItem>(trame["TYPE"].asInt()));
  return (stuff);
}
