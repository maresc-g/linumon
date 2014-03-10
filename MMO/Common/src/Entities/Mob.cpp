//
// Mob.cpp for Mob in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Dec  5 20:42:03 2013 alexis mestag
// Last update Mon Mar 10 14:58:15 2014 laurent ansel
//

#include			<algorithm>
#include			"Entities/Mob.hh"
#ifndef		CLIENT_COMPILATION
# include			"Stats/AuthorizedStatKeys-odb.hxx"
# include			"Entities/Mob-odb.hxx"
# include			"Database/Repositories/Repository.hpp"
#endif
#include			"Loader/LoaderManager.hh"

Mob::Mob() :
  Persistent(), ACharacter("", eCharacter::MOB),
  _player(NULL), _model(NULL), _currentStats(new Stats),
  _inBattle(false)
{

}

Mob::Mob(Mob const &rhs) :
  Persistent(rhs), ACharacter(rhs), _currentStats(new Stats)
{
  *this = rhs;
}

Mob::Mob(MobModel const &model, Level::type const level) :
  Persistent(), ACharacter(model.getName(), eCharacter::MOB),
  _player(NULL), _model(NULL), _currentStats(new Stats),
  _inBattle(false)
{
  this->setModel(model);
  this->setLevel(level);

#ifndef		CLIENT_COMPILATION
  Repository<AuthorizedStatKeys>	*rask = &Database::getRepository<AuthorizedStatKeys>();
  this->setAuthorizedStatKeys(*rask->getById(2));
#endif
}

Mob::~Mob()
{
  delete _currentStats;
#ifndef			CLIENT_COMPILATION
  Repository<Mob>	*rm = &Database::getRepository<Mob>();
  rm->removeFromCache(*this);
#endif
}

Mob				&Mob::operator=(Mob const &rhs)
{
  if (this != &rhs)
    {
      this->setAuthorizedStatKeys(rhs.getAuthorizedStatKeys());
      this->setPlayer(rhs.getPlayer());
      this->setModel(rhs.getModel());
      this->setCurrentStats(rhs.getCurrentStats());
      this->setInBattle(rhs.isInBattle());
      this->setId(rhs.getId());
    }
  return (*this);
}

Player const			*Mob::getPlayer() const
{
  return (_player);
}

void				Mob::setPlayer(Player const *player)
{
  _player = player;
}

MobModel const			&Mob::getModel() const
{
  return (*_model);
}

void				Mob::setModel(MobModel const &model)
{
  _model = &model;
}

Type const			&Mob::getType() const
{
  return (this->getModel().getType());
}

/*
** Mob special stats management
*/

Stats				Mob::getMaxStats() const
{
  Stats					maxStats;
  std::function<void(StatKey const *)>	maxStatCalculator = [&](StatKey const *sk) -> void {
    maxStats.setStat(*sk, this->getMaxStat(sk->getName()));
  };

  std::for_each(this->getAuthorizedStatKeys().begin(),
		this->getAuthorizedStatKeys().end(),
		maxStatCalculator);
  return (maxStats);
}

Stat::value_type		Mob::getMaxStat(std::string const &key) const
{
  Stat::value_type		ret = this->getModel().getStat(key) + this->getStat(key);
  Player const			*player = this->getPlayer();

  if (player)
    ret += player->getStat(key);
  return (ret);
}

Stat::value_type		Mob::getCurrentStat(std::string const &key) const
{
  StatKey const			*sk = this->getKey(key);
  Stat::value_type		ret = Stat::value_type();

  if (sk) {
    Stat const			*stat = reinterpret_cast<Stats const *>(_currentStats)->get(*sk);

    ret = stat ? stat->getValue() : this->getMaxStat(key);
  }
  return (ret);
}

bool				Mob::setCurrentStat(std::string const &key, Stat::value_type const v)
{
  StatKey const			*sk = this->getKey(key);
  bool				ret = false;

  if (sk) {
    Stat::value_type		newValue = v;

    if (!sk->isShortLived()) {
      Stat::value_type		maxValue = this->getMaxStat(key);

      newValue = v > maxValue ? maxValue : v;
    }
    _currentStats->setStat(*sk, newValue);
    ret = true;
  }
  return (ret);
}

/*
** Battle state management
*/

void				Mob::enterBattle()
{
  _currentStats->resetShortLivedStats(this->getMaxStats());
}

void				Mob::leaveBattle()
{
  _currentStats->removeShortLivedStats();
}

bool				Mob::isInBattle() const
{
  return (_inBattle);
}

void				Mob::setInBattle(bool const inBattle)
{
  _inBattle = inBattle;
}

Stats const			&Mob::getCurrentStats() const
{
  return (*_currentStats);
}

void				Mob::setCurrentStats(Stats const &stats)
{
  *_currentStats = stats;
}

/*
** Tests methods
*/

void				Mob::displayMaxStats() const
{
  Stats const			stats = this->getMaxStats();

  for (auto it = stats.begin() ; it != stats.end() ; ++it) {
    std::cout << (*it)->getKey().getName() << " : " << (*it)->getValue() << std::endl;
  }
}

void				Mob::displayCurrentStats() const
{
  Stats const			&stats = this->getCurrentStats();

  for (auto it = stats.begin() ; it != stats.end() ; ++it) {
    std::cout << (*it)->getKey().getName() << " : " << (*it)->getValue() << std::endl;
  }
}

bool				Mob::serialization(Trame &trame) const
{
  bool				ret = true;

  this->getCurrentStats().serialization(trame(trame["STATS"]));
  trame["NAME"] = this->getName();
  trame["CEXP"] = this->getCurrentExp();
  trame["ID"] = static_cast<unsigned int>(this->getId());
  this->getLevelObject().serialization(trame);
  trame["MOD"] = this->getModel().getName();
  // this->getModel().serialization(trame(trame["MOD"]));
  this->getEquipment().serialization(trame);
  trame["KEY"] = this->getAuthorizedStatKeys().getName();
  return (ret);
}

Mob				*Mob::deserialization(Trame const &trame)
{
  Mob				*mob = new Mob;

  if (trame.isMember("KEY"))
    mob->setAuthorizedStatKeys(*(**LoaderManager::getInstance()->getAuthorizedStatKeyLoader())->getValue(trame["KEY"].asString()));
  mob->setCurrentStats(*Stats::deserialization(trame(trame["STATS"])));
  // mob->setCurrentStats(*Stats::deserialization(trame(trame["TMP"])));
  mob->setLevelObject(*Level::deserialization(trame));
  mob->setName(trame["NAME"].asString());
  mob->setId(trame["ID"].asUInt());
  if (trame.isMember("MOD"))
    //   mob->setModel(*MobModel::deserialization(trame(trame["MOD"])));
    mob->setModel(*(**LoaderManager::getInstance()->getMobModelLoader())->getValue(trame["MOD"].asString()));
  mob->setCurrentExp(trame["CEXP"].asUInt());

  Equipment			*equipment = Equipment::deserialization(trame);
  if (equipment)
    mob->setEquipment(equipment);
  return (mob);
}
