//
// Stuff.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Feb  6 15:41:23 2014 laurent ansel
// Last update Fri Mar  7 13:11:43 2014 laurent ansel
//

#include			"Entities/Stuff.hh"

Stuff::Stuff() :
  Persistent(),
  AItem("", AItem::eItem::STUFF),
  _stuffType(eStuff::NONE),
  _stats(new Stats)
{
}

Stuff::Stuff(std::string const &name, eStuff const type) :
  Persistent(),
  AItem(name, AItem::eItem::STUFF),
  _stuffType(type),
  _stats(new Stats)
{

}

Stuff::Stuff(Stuff const &rhs) :
  Persistent(rhs),
  AItem(rhs.getName(), AItem::eItem::STUFF),
  _stats(new Stats)
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
      *this->_stats = rhs.getStats();
    }
  return (*this);
}

Stats const			&Stuff::getStats() const
{
  return (*_stats);
}

void				Stuff::setStats(Stats const &stats)
{
  *_stats = stats;
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
  trame["ID"] = static_cast<unsigned int>(this->getId());
  trame["ST"] = this->getStuffType();
  this->getStats().serialization(trame(trame["STATS"]));
  return (true);
}

Stuff				*Stuff::deserialization(Trame const &trame, bool const client)
{
  Stuff				*stuff = NULL;

  if (trame["TYPE"].asInt() == AItem::eItem::STUFF)
    {
      stuff = new Stuff(trame["NAME"].asString(), static_cast<eStuff>(trame["ST"].asInt()));
      if (client)
	stuff->setId(trame["ID"].asUInt());
      stuff->setItemType(static_cast<AItem::eItem>(trame["TYPE"].asInt()));
      stuff->setStats(*Stats::deserialization(trame(trame)));
    }
  return (stuff);
}
