//
// AStatEntity.cpp for AStatEntity in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 21:33:57 2013 alexis mestag
// Last update Thu Feb 20 22:28:47 2014 alexis mestag
//

#include			"Entities/AStatEntity.hh"

AStatEntity::AStatEntity() :
  AEntity("", eEntity::STATENTITY), _statEntityType(eStatEntity::NONE)
{

}

AStatEntity::AStatEntity(std::string const &name, AStatEntity::eStatEntity const statEntityType) :
  AEntity(name, eEntity::STATENTITY), _statEntityType(statEntityType)
{

}

AStatEntity::AStatEntity(AStatEntity const &rhs) :
  AEntity(rhs)
{
  *this = rhs;
}

AStatEntity::~AStatEntity()
{

}

AStatEntity			&AStatEntity::operator=(AStatEntity const &rhs)
{
  if (this != &rhs)
    {
      this->setStatEntityType(rhs.getStatEntityType());
      this->setStats(rhs.getStats());
    }
  return (*this);
}

AStatEntity::eStatEntity	AStatEntity::getStatEntityType() const
{
  return (_statEntityType);
}

void				AStatEntity::setStatEntityType(AStatEntity::eStatEntity const statEntityType)
{
  _statEntityType = statEntityType;
}

Stats const			&AStatEntity::getStats() const
{
  return (_stats);
}

void				AStatEntity::setStats(Stats const &stats)
{
  _stats = stats;
}

AuthorizedStatKeys const	&AStatEntity::getStatKeys() const
{
  return (_stats.getKeys());
}
