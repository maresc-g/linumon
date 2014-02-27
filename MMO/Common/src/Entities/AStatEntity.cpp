//
// AStatEntity.cpp for AStatEntity in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 21:33:57 2013 alexis mestag
// Last update Thu Feb 27 20:17:05 2014 alexis mestag
//

#include			"Entities/AStatEntity.hh"

#ifndef		CLIENT_COMPILATION
# include			"Database/Repositories/StatKeyRepository.hpp"
#endif

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

bool				AStatEntity::isKeyAuthorized(StatKey const &key) const
{
  return (_authKeys->isAuthorized(key));
}

StatKey const			*AStatEntity::getKey(std::string const &key) const
{
  return (_authKeys->getKey(key));
}

Stat::value_type		AStatEntity::getStat(StatKey const &key) const
{
  return (_stats.getStat(key));
}

Stat::value_type		AStatEntity::getStat(std::string const &key) const
{
  StatKey const			*sk = this->getKey(key);

  return (sk ? this->getStat(*sk) : Stat::value_type());
}

bool				AStatEntity::setStat(StatKey const &key, Stat::value_type const value,
						     bool const add)
{
  bool				ret = true;

  if (this->isKeyAuthorized(key))
    _stats.setStat(key, value, add);
  else
    ret = false;
  return (ret);
}

#ifndef		CLIENT_COMPILATION
bool				AStatEntity::setStat(std::string const &key,
						     Stat::value_type const value,
						     bool const add)
{
  Repository<StatKey>		*rsk = &Database::getRepository<StatKey>();
  StatKey const			*sk = rsk->getByName(key);

  return (sk ? this->setStat(*sk, value, add) : false);
}

bool				AStatEntity::setTmpStat(std::string const &key,
							Stat::value_type const value,
							bool const add)
{
  Repository<StatKey>		*rsk = &Database::getRepository<StatKey>();
  StatKey const			*sk = rsk->getByName(key);

  return (sk ? this->setTmpStat(*sk, value, add) : false);
}
#endif


Stat::value_type		AStatEntity::getTmpStat(StatKey const &key) const
{
  return (_tmpStats.getStat(key));
}

Stat::value_type		AStatEntity::getTmpStat(std::string const &key) const
{
  StatKey const			*sk = this->getKey(key);

  return (sk ? this->getTmpStat(*sk) : Stat::value_type());
}

bool				AStatEntity::setTmpStat(StatKey const &key,
							Stat::value_type const value,
							bool const add)
{
  bool				ret = true;

  if (this->isKeyAuthorized(key))
    _tmpStats.setStat(key, value, add);
  else
    ret = false;
  return (ret);
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

#include			<iostream>

void				AStatEntity::displayTmpStats() const
{
  std::cout << "Mob : " << this->getName() << std::endl;
  for (auto it = this->getTmpStats().getStats().begin() ; it != this->getTmpStats().getStats().end() ;
       ++it)
    {
      Stat			*s = *it;

      std::cout << "\t" << s->getKey().getName() << " : " << s->getValue() << std::endl;
    }
}
