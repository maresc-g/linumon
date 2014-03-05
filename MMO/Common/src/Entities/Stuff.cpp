//
// Stuff.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Feb  6 15:41:23 2014 laurent ansel
// Last update Wed Mar  5 17:15:28 2014 laurent ansel
//

#include			"Entities/Stuff.hh"

Stuff::Stuff() :
  Persistent(),
  AItem("", AItem::eItem::STUFF),
  _stuffType(eStuff::NONE),
  _effect(new std::map<StatKey const *, Stat::value_type>)
{
}

Stuff::Stuff(std::string const &name, eStuff const type) :
  Persistent(),
  AItem(name, AItem::eItem::STUFF),
  _stuffType(type),
  _effect(new std::map<StatKey const *, Stat::value_type>)
{

}

Stuff::Stuff(Stuff const &rhs) :
  Persistent(rhs),
  AItem(rhs.getName(), AItem::eItem::STUFF),
  _effect(new std::map<StatKey const *, Stat::value_type>)
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
#ifndef				CLIENT_COMPILATION
      this->setEffectLib(rhs.getEffectLib());
#endif
      for (auto it = rhs.getEffect().begin() ; it != rhs.getEffect().end() ; ++it)
	(*this->_effect)[it->first] = it->second;
    }
  return (*this);
}

#ifndef				CLIENT_COMPILATION
EffectLib const			&Stuff::getEffectLib() const
{
  return (*_effectLib);
}

void				Stuff::setEffectLib(EffectLib const &effectLib)
{
  _effectLib = &effectLib;
}

void				Stuff::applyEffect(AStatEntity &StatEntity) const
{
  StatEntityEffect		*effect = static_cast<StatEntityEffect *>(_effectLib->getEffect());

  effect->apply(StatEntity);
  delete effect;
}
#endif

std::map<StatKey const *, Stat::value_type> const	&Stuff::getEffect() const
{
  return (*_effect);
}

void			Stuff::setEffect(std::map<StatKey const *, Stat::value_type> const &effect)
{
  *_effect = effect;
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
    }
  return (stuff);
}
