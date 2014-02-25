//
// AStatEntity.cpp for AStatEntity in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 21:33:57 2013 alexis mestag
// Last update Tue Feb 25 16:25:22 2014 alexis mestag
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
      this->setTmpStats(rhs.getTmpStats());
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

Stats const			&AStatEntity::getTmpStats() const
{
  return (_tmpStats);
}

void				AStatEntity::setTmpStats(Stats const &stats)
{
  _tmpStats = stats;
}

void				AStatEntity::reinitTmpStats()
{
  _tmpStats.smartAssign(_stats);
}

AuthorizedStatKeys const	&AStatEntity::getStatKeys() const
{
  return (_stats.getKeys());
}

void				AStatEntity::setStatKeys(AuthorizedStatKeys const &keys)
{
  _stats.setKeys(keys);
  _tmpStats.setKeys(keys);
}
