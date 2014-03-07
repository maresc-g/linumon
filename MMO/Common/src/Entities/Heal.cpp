//
// Heal.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb 21 13:05:16 2014 laurent ansel
// Last update Fri Mar  7 15:29:10 2014 laurent ansel
//

#include			"Entities/Heal.hh"
#ifndef CLIENT_COMPILATION
#include			"Database/Repositories/StatKeyRepository.hpp"
#endif
#include			"Entities/Digitaliser.hh"

Heal::Heal() :
  Persistent(),
  PNJ("HEAL")
{

}

Heal::Heal(Heal const &rhs) :
   Persistent(rhs),
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
  // Repository<StatKey>		*rsk = &Database::getRepository<StatKey>();
  // StatKey			*sk = rsk->getByName("HP");
  Digitaliser::Mobs const	*mobs = &digitaliser.getBattleMobs();

  for (auto it = mobs->begin() ; it !=mobs->end() ; ++it)
    (*it)->setTmpStat("HP", (*it)->getStat("HP"), true);
  return (true);
#else
(void)digitaliser;
return (false);
#endif
}

bool				Heal::serialization(Trame &trame) const
{
  trame["TYPE"] = this->getEntityType();
  trame["PNJ"] = this->getPNJType();
  trame["NAME"] = this->getName();
  trame["ZONE"] = this->getZone();
  trame["ID"] = static_cast<unsigned int>(this->getId());
  this->getCoord().serialization(trame(trame));
  return (true);
}

Heal				*Heal::deserialization(Trame const &trame, bool const client)
{
  Heal				*heal = NULL;

  if (trame.isMember("TYPE") && static_cast<AEntity::eEntity>(trame["TYPE"].asUInt()) == AEntity::eEntity::PNJ)
    {
      heal = new Heal();
      heal->setName(trame["NAME"].asString());
      heal->setZone(trame["ZONE"].asString());
      if (client)
	heal->setId(trame["ID"].asUInt());
      heal->setEntityType(static_cast<AEntity::eEntity>(trame["TYPE"].asInt()));
      heal->setPNJType(static_cast<PNJ::ePnj>(trame["PNJ"].asInt()));
      heal->setCoord(*PNJCoordinate::deserialization(trame(trame)));
    }
  return (heal);
}
