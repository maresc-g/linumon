//
// Mob.cpp for Mob in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Dec  5 20:42:03 2013 alexis mestag
// Last update Wed Mar 26 14:18:05 2014 antoine maitre
//

#include			<random>
#include			<algorithm>
#include			"Entities/Mob.hh"
#ifndef		CLIENT_COMPILATION
# include			"Database/Repositories/MobRepository.hpp"
# include			"Database/Repositories/AuthorizedStatKeysRepository.hpp"
#endif
#include			"Loader/LoaderManager.hh"

Mob::Mob() :
  Persistent(), ACharacter("", eCharacter::MOB),
  _player(NULL), _model(NULL), _currentStats(new Stats)
{

}

Mob::Mob(Mob const &rhs) :
  Persistent(rhs), ACharacter(rhs), _currentStats(new Stats)
{
  *this = rhs;
}

Mob::Mob(MobModel const &model, Levelable::type const level, Player const *player) :
  Persistent(), ACharacter(model.getName(), eCharacter::MOB),
  _player(player), _model(NULL), _currentStats(new Stats)
{
  this->setModel(model);
  this->setLevel(level);

#ifndef		CLIENT_COMPILATION
  Repository<AuthorizedStatKeys>	*rask = &Database::getRepository<AuthorizedStatKeys>();
  this->setAuthorizedStatKeys(*rask->getByName("MobKeys"));
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
      // this->setAuthorizedStatKeys(rhs.getAuthorizedStatKeys());
      this->setPlayer(rhs.getPlayer());
      this->setModel(rhs.getModel());
      this->setCurrentStats(rhs.getCurrentStats());
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
  StatKey const			*sk = this->getKey(key);
  Player const			*player = this->getPlayer();
  Stat::value_type		ret = Stat::value_type();

  if (sk) {
    double			tmp;

    tmp = this->getModel().getStat(key) * 2.0 + 31.0 + 25.0; // (25 = 100 EV / 4)
    tmp *= this->getLevel() / 100.0;
    tmp += (sk->isShortLived() ? 5.0 : (this->getLevel() + 10.0));
    tmp += this->getStat(key);
    if (player)
      tmp += player->getStat(key);
    ret = tmp;
  }
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

bool				Mob::incCurrentStat(std::string const &key, Stat::value_type const inc)
{
  return (this->setCurrentStat(key, this->getCurrentStat(key) + inc));
}

bool				Mob::decCurrentStat(std::string const &key, Stat::value_type const dec)
{
  Stat::value_type		oldValue = this->getCurrentStat(key);
  Stat::value_type		newValue = dec >= oldValue ? 0 : oldValue - dec;

  return (this->setCurrentStat(key, newValue));
}

/*
** Mob's Carcass
*/
Carcass				*Mob::getNewCarcass() const
{
  Carcass			*ret = this->getModel().getNewCarcass();

  /* Do some stuff here */
  return (ret);
}

/*
** Mob's drop
*/

Drop				*Mob::getNewDrop() const
{
  static unsigned int		seed = std::chrono::system_clock::now().time_since_epoch().count();
  static std::default_random_engine	gen(seed);
  Drop const				&modelDrop = this->getModel().getDrop();
  Drop::value_type const		*stack;
  Drop					*ret = new Drop;

  for (auto it = modelDrop.begin() ; it != modelDrop.end() ; ++it) {
    stack = &*it;
    std::uniform_int_distribution<unsigned int>	dist(0, stack->getNb());
    unsigned int				rNb = dist(gen);

    if (rNb) {
      ret->addItem(stack->getItem(), rNb);
    }
  }
  return (ret);
}

/*
** Mobs'ExperienceCurve
*/

#ifndef			CLIENT_COMPILATION
ExperienceCurve const		&Mob::getExperienceCurve() const
{
  return (this->getModel().getExperienceCurve());
}
#endif

unsigned int			Mob::getExpSeed() const
{
  return (this->getModel().getExpSeed());
}

Levelable::type			Mob::getGivenExp() const
{
  return (this->getExpSeed() * this->getLevel() / 7.0);
}

unsigned int			Mob::getCatchRate() const
{
  return (this->getModel().getCatchRate());
}

/*
** Battle state management
*/

void				Mob::enterBattle()
{
  ACharacter::enterBattle();
  _currentStats->resetShortLivedStats(this->getMaxStats());
}

void				Mob::leaveBattle()
{
  ACharacter::leaveBattle();
  _currentStats->removeShortLivedStats();
}

Stats const			&Mob::getRawCurrentStats() const
{
  return (*_currentStats);
}

Stats				Mob::getCurrentStats() const
{
  Stats				ret(this->getRawCurrentStats());

  ret.resetShortLivedStats(this->getMaxStats());
  return (ret);
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
    std::cout << it->getKey().getName() << " : " << it->getValue() << std::endl;
  }
}

void				Mob::displayCurrentStats() const
{
  Stats const			&stats = this->getCurrentStats();

  for (auto it = stats.begin() ; it != stats.end() ; ++it) {
    std::cout << it->getKey().getName() << " : " << it->getValue() << std::endl;
  }
}

bool				Mob::serialization(Trame &trame) const
{
  bool				ret = true;

  this->getCurrentStats().serialization(trame(trame["STATS"]));
  trame["NAME"] = this->getName();
  trame["CEXP"] = this->getCurrentExp();
  trame["LVL"] = this->getLevel();
  trame["EXP"] = this->getExp();
  trame["OLDEXP"] = this->getOldExp();
  trame["ID"] = static_cast<unsigned int>(this->getId());
  // this->getLevelObject().serialization(trame);
  trame["MOD"] = this->getModel().getName();
  // this->getModel().serialization(trame(trame["MOD"]));
  this->getEquipment().serialization(trame);
  trame["KEY"] = this->getAuthorizedStatKeys().getName();
  return (ret);
}

Mob				*Mob::deserialization(Trame const &trame)
{
  Mob				*mob = new Mob;

  // std::cout << "TRAMe =" << trame.toString() << std::endl;
  if (trame.isMember("KEY"))
    mob->setAuthorizedStatKeys(*(**LoaderManager::getInstance()->getAuthorizedStatKeyLoader())->getValue(trame["KEY"].asString()));
  mob->setCurrentStats(*Stats::deserialization(trame(trame["STATS"])));
  // mob->setCurrentStats(*Stats::deserialization(trame(trame["TMP"])));
  // mob->setLevelObject(*Level::deserialization(trame));
  mob->setCurrentExp(trame["CEXP"].asUInt(), false);
  mob->setLevel(trame["LVL"].asUInt());
  mob->setExp(trame["EXP"].asUInt());
  mob->setOldExp(trame["OLDEXP"].asUInt());
  mob->setName(trame["NAME"].asString());
  mob->setId(trame["ID"].asUInt());
  if (trame.isMember("MOD"))
    //   mob->setModel(*MobModel::deserialization(trame(trame["MOD"])));
    mob->setModel(*(**LoaderManager::getInstance()->getMobModelLoader())->getValue(trame["MOD"].asString()));
  mob->setCurrentExp(trame["CEXP"].asUInt(), false);

  Equipment			*equipment = Equipment::deserialization(trame);
  if (equipment)
    mob->setEquipment(equipment);
  return (mob);
}
