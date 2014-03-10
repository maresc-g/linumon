//
// Heal.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb 21 13:05:16 2014 laurent ansel
// Last update Sun Mar  9 22:03:08 2014 alexis mestag
//

#include			"Entities/Heal.hh"
#ifndef CLIENT_COMPILATION
#include			"Database/Repositories/StatKeyRepository.hpp"
#endif
#include			"Entities/Digitaliser.hh"

Heal::Heal() :
  PNJ("HEAL")
{

}

Heal::Heal(Heal const &rhs) :
  PNJ(rhs)
{
  *this = rhs;
}

Heal::~Heal()
{

}

Heal				&Heal::operator=(Heal const &rhs)
{
  if (this != &rhs)
    {
      this->setCoord(rhs.getCoord());
    }
  return (*this);
}

bool				Heal::action(Player *player)
{
  return (this->heal(player->getDigitaliser()));
}


bool				Heal::heal(Digitaliser const &digitaliser) const
{
#ifndef CLIENT_COMPILATION
  Digitaliser::Mobs const	*mobs = &digitaliser.getBattleMobs();

  // for (auto it = mobs->begin() ; it !=mobs->end() ; ++it)
  //   (*it)->setBattleStat("HP", (*it)->getStat("HP"), true);
  return (true);
#else
(void)digitaliser;
return (false);
#endif
}

bool				Heal::serialization(Trame &trame) const
{
  trame["HEAL"]["TYPE"] = this->getEntityType();
  trame["HEAL"]["PNJTYPE"] = this->getPNJType();
  trame["HEAL"]["NAME"] = this->getName();
  trame["HEAL"]["ID"] = static_cast<unsigned int>(this->getId());
  this->getCoord().serialization(trame(trame["HEAL"]));
  return (true);
}

Heal				*Heal::deserialization(Trame const &trame, bool const client)
{
  Heal				*heal = NULL;

  if (trame.isMember("HEAL"))
    {
      heal = new Heal();
      heal->setName(trame["HEAL"]["NAME"].asString());
      if (client)
	heal->setId(trame["HEAL"]["ID"].asUInt());
      heal->setEntityType(static_cast<AEntity::eEntity>(trame["HEAL"]["TYPE"].asInt()));
      heal->setPNJType(static_cast<PNJ::ePnj>(trame["HEAL"]["PNJTYPE"].asInt()));
      heal->setCoord(*PNJCoordinate::deserialization(trame(trame["HEAL"])));
    }
  return (heal);
}
