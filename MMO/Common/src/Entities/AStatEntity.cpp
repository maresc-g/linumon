//
// AStatEntity.cpp for AStatEntity in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 21:33:57 2013 alexis mestag
// Last update Wed Mar 26 13:21:34 2014 alexis mestag
//

#include			"Entities/AStatEntity.hh"

#ifndef		CLIENT_COMPILATION
# include			"Database/Repositories/StatKeyRepository.hpp"
#endif

AStatEntity::AStatEntity() :
  AEntity("", eEntity::STATENTITY), _statEntityType(eStatEntity::NONE),
  _authKeys(NULL), _stats(new Stats)
{

}

AStatEntity::AStatEntity(std::string const &name, AStatEntity::eStatEntity const statEntityType) :
  AEntity(name, eEntity::STATENTITY), _statEntityType(statEntityType),
  _authKeys(NULL), _stats(new Stats)
{

}

AStatEntity::AStatEntity(AStatEntity const &rhs) :
  AEntity(rhs), _stats(new Stats)
{
  *this = rhs;
}

AStatEntity::~AStatEntity()
{
  delete _stats;
}

AStatEntity			&AStatEntity::operator=(AStatEntity const &rhs)
{
  if (this != &rhs)
    {
      this->setStatEntityType(rhs.getStatEntityType());
      this->setAuthorizedStatKeys(rhs.getAuthorizedStatKeys());
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

/*
** Authorized keys management
*/
AuthorizedStatKeys const	&AStatEntity::getAuthorizedStatKeys() const
{
  return (*_authKeys);
}

void				AStatEntity::setAuthorizedStatKeys(AuthorizedStatKeys const &keys)
{
  _authKeys = &keys;
}

StatKey const			*AStatEntity::getKey(std::string const &key) const
{
  if (!_authKeys)
    std::cerr << "Warning : AStatEntity::_authKeys should not be NULL, fix that !" << std::endl;
  return (_authKeys ? _authKeys->getKey(key) : NULL);
}

/*
** Simple stats management
*/
Stats const			&AStatEntity::getStats() const
{
  return (*_stats);
}

void				AStatEntity::setStats(Stats const &stats)
{
  *_stats = stats;
}

void				AStatEntity::addToStats(Stats const &stats)
{
  *_stats += stats;
}

/*
** Stat values getter and setter
*/

Stat::value_type		AStatEntity::getStat(std::string const &key) const
{
  StatKey const			*sk = this->getKey(key);

  return (sk ? _stats->getStat(*sk) : Stat::value_type());
}

bool				AStatEntity::setStat(std::string const &key, Stat::value_type const value)
{
  StatKey const			*sk = this->getKey(key);
  bool				ret = false;

  if (sk) {
    _stats->setStat(*sk, value);
    ret = true;
  }
  return (ret);
}

bool				AStatEntity::incStat(std::string const &key, Stat::value_type const inc)
{
  return (this->setStat(key, this->getStat(key) + inc));
}

bool				AStatEntity::decStat(std::string const &key, Stat::value_type const dec)
{
  StatKey const			*sk = this->getKey(key);
  bool				ret = false;

  if (sk) {
    Stat::value_type		oldValue = this->getStats().getStat(key);
    Stat::value_type		newValue = dec >= oldValue ? 0 : oldValue - dec;

    _stats->setStat(*sk, newValue);
    ret = true;
  }
  return (ret);
}

Stat::bonus_type		AStatEntity::getBonus(std::string const &key) const
{
  StatKey const			*sk = this->getKey(key);

  return (sk ? _stats->getBonus(*sk) : Stat::bonus_type());
}

bool				AStatEntity::setBonus(std::string const &key,
						      Stat::bonus_type const value)
{
  StatKey const			*sk = this->getKey(key);
  bool				ret = false;

  if (sk) {
    _stats->setBonus(*sk, value);
    ret = true;
  }
  return (ret);
}

bool				AStatEntity::incBonus(std::string const &key,
						      Stat::bonus_type const inc)
{
  return (this->setBonus(key, this->getBonus(key) + inc));
}

bool				AStatEntity::decBonus(std::string const &key,
						      Stat::bonus_type const dec)
{
  return (this->setBonus(key, this->getBonus(key) - dec));
}
