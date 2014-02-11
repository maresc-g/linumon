//
// Stuff.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Feb  6 15:41:23 2014 laurent ansel
// Last update Tue Feb 11 14:13:03 2014 laurent ansel
//

#include			"Entities/Ressource.hh"

Ressource::Ressource() :
  AItem("", AItem::eItem::RESSOURCE)
{

}

Ressource::Ressource(std::string const &name) :
  AItem(name, AItem::eItem::RESSOURCE)
{

}

Ressource::Ressource(Ressource const &rhs) :
  AItem(rhs.getName(), AItem::eItem::STUFF)
{
  *this = rhs;
}

Ressource::~Ressource()
{

}

Ressource			&Ressource::operator=(Ressource const &rhs)
{
  if (this != &rhs)
    {

    }
  return (*this);
}

bool				Ressource::serialization(Trame &trame) const
{
  trame["RESSOURCE"]["TYPE"] = this->getItemType();
  trame["RESSOURCE"]["NAME"] = this->getName();
  trame["RESSOURCE"]["ID"] = static_cast<unsigned int>(this->getId());
  return (true);
}

Ressource			*Ressource::deserialization(Trame const &trame)
{
  Ressource			*ressource = NULL;

  if (trame.isMember("RESSOURCE"))
    {
      ressource = new Ressource(trame["RESSOURCE"]["NAME"].asString());
      ressource->setId(trame["RESSOURCE"]["ID"].asUInt());
      ressource->setItemType(static_cast<AItem::eItem>(trame["RESSOURCE"]["TYPE"].asInt()));
    }
  return (ressource);
}
