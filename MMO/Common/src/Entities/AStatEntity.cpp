//
// AStatEntity.cpp for AStatEntity in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 21:33:57 2013 alexis mestag
// Last update Wed Feb 26 11:26:45 2014 alexis mestag
//

#include			"Entities/AStatEntity.hh"

AStatEntity::AStatEntity() :
  AEntity("", eEntity::STATENTITY), _statEntityType(eStatEntity::NONE),
  _authKeys(NULL), _inBattle(false)
{

}

AStatEntity::AStatEntity(std::string const &name, AStatEntity::eStatEntity const statEntityType) :
  AEntity(name, eEntity::STATENTITY), _statEntityType(statEntityType),
  _authKeys(NULL), _inBattle(false)
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
      this->setStatKeys(rhs.getStatKeys());
      this->setStats(rhs.getStats());
      this->setTmpStats(rhs.getTmpStats());
      this->setInBattle(rhs.isInBattle());
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
#include			<iostream>
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

void				AStatEntity::initTmpStats()
{
  _tmpStats.smartAssign(_stats);
}

void				AStatEntity::endTmpStats()
{
  _tmpStats.removeShortLivedStats();
}

AuthorizedStatKeys const	&AStatEntity::getStatKeys() const
{
  return (*_authKeys);
}

void				AStatEntity::setStatKeys(AuthorizedStatKeys const &keys)
{
  _authKeys = &keys;
}

Stat::value_type		AStatEntity::getStat(StatKey const &key) const
{
  return (_stats.getStat(key));
}

void				AStatEntity::setStat(StatKey const &key, Stat::value_type const value,
						     bool const add)
{
  _stats.setStat(key, value, add);
}

Stat::value_type		AStatEntity::getTmpStat(StatKey const &key) const
{
  return (_tmpStats.getStat(key));
}

void				AStatEntity::setTmpStat(StatKey const &key, Stat::value_type const value,
							bool const add)
{
  _tmpStats.setStat(key, value, add);
}


void				AStatEntity::enterBattle()
{
  this->initTmpStats();
}

void				AStatEntity::leaveBattle()
{
  this->endTmpStats();
}

bool				AStatEntity::isInBattle() const
{
  return (_inBattle);
}

void				AStatEntity::setInBattle(bool const inBattle)
{
  _inBattle = inBattle;
}
