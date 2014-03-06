//
// AStatEntity.cpp for AStatEntity in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 21:33:57 2013 alexis mestag
// Last update Thu Mar  6 14:16:04 2014 antoine maitre
//

#include			"Entities/AStatEntity.hh"

#ifndef		CLIENT_COMPILATION
# include			"Database/Repositories/StatKeyRepository.hpp"
#endif

AStatEntity::AStatEntity() :
  AEntity("", eEntity::STATENTITY), _statEntityType(eStatEntity::NONE),
  _authKeys(NULL), _stats(new Stats), _tmpStats(new Stats), _inBattle(false)
{

}

AStatEntity::AStatEntity(std::string const &name, AStatEntity::eStatEntity const statEntityType) :
  AEntity(name, eEntity::STATENTITY), _statEntityType(statEntityType),
  _authKeys(NULL), _stats(new Stats), _tmpStats(new Stats), _inBattle(false)
{

}

AStatEntity::AStatEntity(AStatEntity const &rhs) :
  AEntity(rhs), _stats(new Stats), _tmpStats(new Stats)
{
  *this = rhs;
}

AStatEntity::~AStatEntity()
{
  delete _stats;
  delete _tmpStats;
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
  return (*_stats);
}

void				AStatEntity::setStats(Stats const &stats)
{
  if (!_stats)
    _stats = new Stats(stats);
  else
    *_stats = stats;
}

Stats const			&AStatEntity::getTmpStats() const
{
  return (*_tmpStats);
}

void				AStatEntity::setTmpStats(Stats const &stats)
{
  if (!_tmpStats)
    _tmpStats = new Stats(stats);
  else
    *_tmpStats = stats;
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
  return (_stats->getStat(key));
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
    _stats->setStat(key, value, add);
  else
    ret = false;
  return (ret);
}

bool				AStatEntity::setStat(std::string const &key,
						     Stat::value_type const value,
						     bool const add)
{
  StatKey const			*sk = this->getKey(key);

  return (sk ? this->setStat(*sk, value, add) : false);
}

bool				AStatEntity::setTmpStat(std::string const &key,
							Stat::value_type const value,
							bool const add)
{
  StatKey const			*sk = this->getKey(key);

  return (sk ? this->setTmpStat(*sk, value, add) : false);
}


Stat::value_type		AStatEntity::getTmpStat(StatKey const &key) const
{
  return (_tmpStats->getStat(key));
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
    _tmpStats->setStat(key, value, add);
  else
    ret = false;
  return (ret);
}

void				AStatEntity::initTmpStats()
{
  _tmpStats->smartAssign(this->getStats());
}

void				AStatEntity::endTmpStats()
{
  _tmpStats->removeShortLivedStats();
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
  for (auto it = this->getTmpStats().begin() ; it != this->getTmpStats().end() ; ++it)
    {
      Stat			*s = *it;

      std::cout << "\t" << s->getKey().getName() << " : " << s->getValue() << std::endl;
    }
}
