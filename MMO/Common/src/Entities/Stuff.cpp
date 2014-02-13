//
// Stuff.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Feb  6 15:41:23 2014 laurent ansel
// Last update Tue Feb 11 16:03:45 2014 alexis mestag
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
  trame["STUFF"]["TYPE"] = this->getItemType();
  trame["STUFF"]["NAME"] = this->getName();
  trame["STUFF"]["ID"] = static_cast<unsigned int>(this->getId());
  trame["STUFF"]["TYPE"] = this->getStuffType();
  return (false);
}

Stuff				*Stuff::deserialization(Trame const &trame)
{
  Stuff				*stuff = NULL;

  if (trame.isMember("STUFF"))
    {
      stuff = new Stuff(trame["STUFF"]["NAME"].asString(), static_cast<eStuff>(trame["STUFF"]["TYPE"].asInt()));
      stuff->setId(trame["STUFF"]["ID"].asUInt());
      stuff->setItemType(static_cast<AItem::eItem>(trame["STUFF"]["TYPE"].asInt()));
    }
  return (stuff);
}
