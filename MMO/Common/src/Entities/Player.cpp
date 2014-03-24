//
// Player.cpp for Player in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Dec  3 13:45:16 2013 alexis mestag
// Last update Mon Mar 24 12:55:29 2014 cyril jourdain
//

#include			<cmath>
#include			<random>
#include			<chrono>
#include			<limits>
#include			<functional>
#include			"Entities/Player.hh"
#include			"Map/Map.hh"
#ifndef			CLIENT_COMPILATION
# include			"Stats/TalentTree-odb.hxx"
# include			"Entities/DBZone-odb.hxx"
# include			"Entities/JobModel-odb.hxx"
# include			"Database/Repositories/AuthorizedStatKeysRepository.hpp"
# include			"Database/Repositories/ExperienceCurveRepository.hpp"
# include			"Database/Repositories/FactionRepository.hpp"
# include			"Database/Repositories/PlayerRepository.hpp"
# include			"Database/Repositories/MobModelRepository.hpp"
# include			"Database/Repositories/StatKeyRepository.hpp"
#endif
#include			"Entities/Consumable.hh"
#include			"Loader/LoaderManager.hh"

Player::Player() :
  Persistent(), ACharacter("", eCharacter::PLAYER), _type(PlayerType::PLAYER),
  _digitaliser(new Digitaliser(this)), _out(false), _coord(new PlayerCoordinate),
  _faction(NULL), _talentTree(NULL), _talents(new Talents), _user(NULL),
  _inventory(new Inventory), _jobs(new Jobs), _guild(NULL)
# ifndef	CLIENT_COMPILATION
  , _expCurve(NULL)
  , _dbZone(NULL)
# else
  , _zone("NONE")
# endif
{

}

Player::Player(std::string const &name, std::string const &factionName, User const *user) :
  Persistent(), ACharacter(name, eCharacter::PLAYER), _type(PlayerType::PLAYER),
  _digitaliser(new Digitaliser(this)), _coord(new PlayerCoordinate),
  _faction(NULL), _talentTree(NULL), _talents(new Talents), _user(user),
  _inventory(new Inventory), _jobs(new Jobs), _guild(NULL)
# ifndef	CLIENT_COMPILATION
  , _expCurve(NULL)
  , _dbZone(NULL)
# else
  , _zone("NONE")
# endif
{
  this->_inventory->setPath("Res/Inventories/" + this->getName() + ".json");

# ifndef	CLIENT_COMPILATION
  this->initConstPointersForNewPlayers();

  /*
  ** Capture a Pikachu
  */
  if (user) {
    Repository<MobModel>		*rm = &Database::getRepository<MobModel>();
    MobModel const			*m = rm->getByName("Pikachu");
    Mob					*pikachu = new Mob(*m, 15, this);

    pikachu->resetExp();
    this->_digitaliser->addBattleMob(*pikachu);
  }

  /*
  ** Init Faction
  */
  if (!factionName.empty()) {
    Faction			*faction = Database::getRepository<Faction>().getByName(factionName);

    if (faction) {
      this->setFaction(*faction);
      this->applyFactionEffect();
    }
  }

  /*
  ** Init Jobs
  */
  if (user) {
    Repository<JobModel>		&rjm = Database::getRepository<JobModel>();
    std::list<JobModel *>		jms = rjm.getAll();

    for (auto jmt = jms.begin() ; jmt != jms.end() ; ++jmt) {
      Job				*j = new Job(**jmt, 0);

      j->resetExp();
      this->setJob(j);
    }
  }

  /*
  ** Init Player Stats
  */
  this->setStat("Limit mob", 3);
  this->setStat("Bag capacity", 30);

# else
  (void)factionName;
# endif
}

Player::Player(Player const &rhs) :
  Persistent(rhs), ACharacter(rhs), _digitaliser(new Digitaliser(this)), _coord(new PlayerCoordinate),
  _talents(new Talents), _jobs(new Jobs)
{
  *this = rhs;
}

Player::~Player()
{
  delete _digitaliser;
  delete _coord;
  delete _talents;
  delete _inventory;
  delete _jobs;
  // delete _faction; // Causes an invalid pointer delete
#ifndef		CLIENT_COMPILATION
  Repository<Player>		*rp = &Database::getRepository<Player>();
  rp->removeFromCache(*this);
#endif
}

Player				&Player::operator=(Player const &rhs)
{
  if (this != &rhs)
    {
      this->setDigitaliser(rhs.getDigitaliser());
      this->setCoord(rhs.getCoord());
      this->setFaction(rhs.getFaction());
      this->setGuild(rhs.getGuild());
      this->setZone(rhs.getZone());
#ifndef		CLIENT_COMPILATION
      this->setExperienceCurve(rhs.getExperienceCurve());
#endif
    }
  return (*this);
}

#ifndef		CLIENT_COMPILATION
void					Player::initConstPointersForNewPlayers()
{
  Repository<TalentTree>		*rtt = &Database::getRepository<TalentTree>();
  Repository<AuthorizedStatKeys>	*rask = &Database::getRepository<AuthorizedStatKeys>();
  Repository<DBZone>			*rdbz = &Database::getRepository<DBZone>();
  Repository<ExperienceCurve>		*rec = &Database::getRepository<ExperienceCurve>();

  this->setTalentTree(*rtt->getById(1));
  this->setAuthorizedStatKeys(*rask->getByName("PlayerKeys"));
  this->setDBZone(*rdbz->getById(1));
  this->setExperienceCurve(*rec->getByName("PlayerCurve"));
}

void					Player::applyFactionEffect()
{
  _faction->applyEffect(*this);
}
#endif

void					Player::setOut(bool const looser)
{
  this->_out = looser;
}

bool					Player::getOut() const
{
  return (this->_out);
}

Player::PlayerCoordinate const		&Player::getCoord() const
{
  return (*_coord);
}

Player::PlayerCoordinate::type const	&Player::getX() const
{
  return (_coord->getX());
}

Player::PlayerCoordinate::type const	&Player::getY() const
{
  return (_coord->getY());
}

void				Player::setCoord(PlayerCoordinate const &coord)
{
  *_coord = coord;
}

void				Player::setCoord(PlayerCoordinate::type const &x,
						 PlayerCoordinate::type const &y)
{
  this->setX(x);
  this->setY(y);
}

void				Player::setX(PlayerCoordinate::type const &x)
{
  _coord->setX(x);
}

void				Player::setY(PlayerCoordinate::type const &y)
{
  _coord->setY(y);
}

Faction const			&Player::getFaction() const
{
  return (*_faction);
}

void				Player::setFaction(Faction const &faction)
{
  _faction = &faction;
}

Guild				*Player::getGuild() const
{
  return (_guild);
}

void				Player::setGuild(Guild *guild)
{
  _guild = guild;
}

void				Player::guildAddPlayer(PlayerView *playerView)
{
  _guild->addPlayer(playerView);
}

void				Player::guildRemovePlayer(std::string const &name)
{
  _guild->removePlayer(name);
}

Digitaliser const		&Player::getDigitaliser() const
{
  return (*_digitaliser);
}

void				Player::setDigitaliser(Digitaliser const &digit)
{
  *this->_digitaliser = digit;
  this->_digitaliser->setPlayer(this);
}

Inventory const			&Player::getInventory() const
{
  return (*this->_inventory);
}

void				Player::setInventory(Inventory *inventory)
{
  this->_inventory = inventory;
}

#ifndef			CLIENT_COMPILATION
ExperienceCurve const		&Player::getExperienceCurve() const
{
  return (*_expCurve);
}

void				Player::setExperienceCurve(ExperienceCurve const &expCurve)
{
  _expCurve = &expCurve;
}
#endif

void				Player::levelUp()
{
  ACharacter::levelUp();
  _talents->setCurrentPts(_talents->getCurrentPts() + 5);
}

Jobs const			&Player::getJobs() const
{
  return (*_jobs);
}

void				Player::setJobs(Jobs *jobs)
{
  *this->_jobs = *jobs;
}

void				Player::setJob(Job *job)
{
  this->_jobs->setJob(job);
}

void				Player::setJob(std::string const &name, Job *job)
{
  this->_jobs->setJob(name, job);
}

Job				*Player::getJob(std::string const &name) const
{
  for (auto it = _jobs->begin() ; it != _jobs->end() ; ++it)
    if ((*it)->getJobModel().getName() == name)
      return (*it);
  return (NULL);
}

void				Player::setType(Player::PlayerType const type)
{
  this->_type = type;
}

Player::PlayerType		Player::getType() const
{
  return (this->_type);
}

void				Player::deleteItem(unsigned int const stack)
{
  this->_inventory->deleteItem(stack);
}

void				Player::deleteItem(Stack<AItem> *stack)
{
  this->_inventory->deleteItem(stack);
}

void				Player::addItem(AItem *item)
{
  this->_inventory->addItem(item);
}

void				Player::addItem(Stack<AItem> *stack)
{
  this->_inventory->addItem(stack);
}

AItem				*Player::getAndDeleteItem(unsigned int const item) const
{
  return (this->_inventory->getAndDeleteItem(item));
}

void				Player::addMob(Mob *mob)
{
  this->_digitaliser->addMob(*mob);
}

Mob				*Player::getAndDeleteMob(unsigned int const mob) const
{
  return (this->_digitaliser->getAndDeleteMob(mob));
}


void				Player::addMoney(int const money)
{
  this->_inventory->addMoney(money);
}

Mob const			&Player::getMob(unsigned int const id)
{
  return (*this->_digitaliser->getMob(id));
}

bool				Player::isMyMob(unsigned int const id)
{
  if (this->_digitaliser->getMob(id))
    return (true);
  else
    return (false);
}

bool				Player::getPlayerEquipment(unsigned int const idItem)
{
  bool				ret = false;
  Stuff				*item;

  ret = this->getStuff(item, idItem);
  if (ret)
    this->addItem(item);
  return (ret);
}

bool				Player::getMobEquipment(unsigned int const idMod, unsigned int const idItem)
{
  bool				ret = false;
  Mob				*mob;
  Stuff				*item;

  mob = this->_digitaliser->getMob(idMod);
  if (mob)
    {
      ret = mob->getStuff(item, idItem);
      if (ret)
	this->addItem(item);
    }
  return (ret);
}

bool				Player::putPlayerEquipment(unsigned int const idStack)
{
  bool				ret = false;
  AItem				*item;
  Stuff				*old;

  /*effect item*/
  item = this->getAndDeleteItem(idStack);
  if (item && item->getItemType() == AItem::STUFF)
    {
      ret = this->addStuff(static_cast<Stuff *>(item), old);
      if (ret && old)
	this->addItem(old);
    }
  else if (item)
    this->addItem(item);
  return (ret);
}

bool				Player::putMobEquipment(unsigned int const idMod,unsigned int const idStack)
{
  bool				ret = false;
  AItem				*item;
  Stuff				*old;
  Mob				*mob;

  mob = this->_digitaliser->getMob(idMod);
  if (mob)
    {
      item = this->getAndDeleteItem(idStack);
      if (item && item->getItemType() == AItem::STUFF)
	{
	  ret = mob->addStuff(static_cast<Stuff *>(item), old);
	  if (ret && old)
	    this->addItem(old);
	}
      else if (item)
	this->addItem(item);
    }
  return (ret);
}

void				Player::useObject(unsigned int const target, unsigned int const idStack)
{
  AItem				*item;
  Mob				*mob;

  mob = this->_digitaliser->getMob(target);
  if (mob)
    {
      item = this->getAndDeleteItem(idStack);
      if (!item)
	std::cout << "ITEM IS NULL" << std::endl;
#ifndef		CLIENT_COMPILATION
      if (item && item->getItemType() == AItem::CONSUMABLE)
	static_cast<Consumable *>(item)->applyEffect(*mob);
      else if (item)
	this->addItem(item);
#else
      (void)item;
#endif
    }
  else
    std::cout << "MOB IS NULL" << std::endl;
}

bool				Player::incTalent(TalentModel const &model)
{
  return (_talents->incTalent(model));
}

Talent const			*Player::getTalentFromModel(TalentModel const &model) const
{
  return (const_cast<Talents const *>(_talents)->getTalentFromModel(model));
}

bool				Player::serialization(Trame &trame) const
{
  bool				ret = true;

  trame["PLAYER"]["ID"] = static_cast<int>(this->getId());
  trame["PLAYER"]["NAME"] = this->getName();
  trame["PLAYER"]["TYPE"] = this->getStatEntityType();
  this->_coord->serialization(trame(trame["PLAYER"]));
  if (this->_faction)
    this->_faction->serialization(trame(trame["PLAYER"]));
  if (this->_guild)
    this->_guild->serialization(trame(trame["PLAYER"]["GUILD"]));
  this->_digitaliser->serialization(trame(trame["PLAYER"]));
  this->getStats().serialization(trame(trame["PLAYER"]["STATS"]));
  // this->getLevelObject().serialization(trame(trame["PLAYER"]));
  trame["PLAYER"]["CEXP"] = this->getCurrentExp();
  trame["PLAYER"]["LVL"] = this->getLevel();
  trame["PLAYER"]["EXP"] = this->getExp();
  trame["PLAYER"]["ZONE"] = this->getZone();
  this->_inventory->serialization(trame(trame["PLAYER"]));
  // this->_talentTree->serialization(trame(trame["PLAYER"]));
  trame["PLAYER"]["TALENTTREE"] = this->getTalentTree().getName();
  this->getEquipment().serialization(trame(trame["PLAYER"]));
  this->_talents->serialization(trame(trame["PLAYER"]));
  this->_jobs->serialization(trame(trame["PLAYER"]));
  trame["PLAYER"]["KEY"] = this->getAuthorizedStatKeys().getName();
  return (ret);
}

Player				*Player::deserialization(Trame const &trame)
{
  Player			*player = NULL;

  if (trame.isMember("PLAYER"))
    {
      player = new Player(trame["PLAYER"]["NAME"].asString());
      if (trame["PLAYER"].isMember("KEY"))
	player->setAuthorizedStatKeys(*(**LoaderManager::getInstance()->getAuthorizedStatKeyLoader())->getValue(trame["PLAYER"]["KEY"].asString()));
      player->setId(trame["PLAYER"]["ID"].asUInt());
      player->setStatEntityType(static_cast<AStatEntity::eStatEntity>(trame["PLAYER"]["TYPE"].asInt()));
      player->setCoord(*PlayerCoordinate::deserialization(trame(trame["PLAYER"])));
      player->setFaction(*Faction::deserialization(trame(trame["PLAYER"])));

      Guild			*guild;
      if (trame["PLAYER"].isMember("GUILD"))
	{
	  guild = Guild::deserialization(trame(trame["PLAYER"]["GUILD"]));
	  player->setGuild(guild);
	}

      player->setZone(trame["PLAYER"]["ZONE"].asString());

      if (trame["PLAYER"].isMember("CEXP"))
	player->setCurrentExp(trame["PLAYER"]["CEXP"].asUInt(), false);
      if (trame["PLAYER"].isMember("LVL"))
	player->setLevel(trame["PLAYER"]["EXP"].asUInt());
      if (trame["PLAYER"].isMember("EXP"))
	player->setExp(trame["PLAYER"]["EXP"].asUInt());

      TalentTree		*tree = (**LoaderManager::getInstance()->getTalentTreeLoader())->getValue(trame["PLAYER"]["TALENTTREE"].asString());
      if (tree)
	player->setTalentTree(*tree);

      Inventory			*inv = Inventory::deserialization(trame(trame["PLAYER"]));
      if (inv)
	player->setInventory(inv);

      Digitaliser		*digit = Digitaliser::deserialization(trame(trame["PLAYER"]));
      if (digit)
	player->setDigitaliser(*digit);

      Equipment			*equipment = Equipment::deserialization(trame(trame["PLAYER"]));
      if (equipment)
	player->setEquipment(equipment);

      Stats			*stats = Stats::deserialization(trame(trame["PLAYER"]["STATS"]));
      if (stats)
      	player->setStats(*stats);

      Talents			*talents = Talents::deserialization(trame(trame["PLAYER"]));
      if (talents)
      	player->setTalents(*talents);

      Jobs			*jobs = Jobs::deserialization(trame(trame["PLAYER"]));
      if (jobs)
	player->setJobs(jobs);
    }
  return (player);
}

void				Player::addTalent(Talent const &talent)
{
  this->_talents->getContainer().push_back(new Talent(talent));
}

TalentTree const		&Player::getTalentTree() const
{
  return (*_talentTree);
}

void				Player::setTalentTree(TalentTree const &tree)
{
  this->_talentTree = &tree;
}

void				Player::setTalents(Talents const &list)
{
  *this->_talents = list;
}

#ifndef	CLIENT_COMPILATION
DBZone const			&Player::getDBZone() const
{
  return (*_dbZone);
}

void				Player::setDBZone(DBZone const &dbZone)
{
  _dbZone = &dbZone;
}
#endif
std::string			Player::getZone() const
{
  #ifndef	CLIENT_COMPILATION
  return (_dbZone->getName());
  #else
  return (_zone);
  #endif
}

void				Player::setZone(std::string const zone)
{
  #ifndef	CLIENT_COMPILATION
  _dbZone = &Map::getInstance()->getZone(zone)->getDBZone();
  #else
  _zone = zone;
  #endif
}

User const			&Player::getUser() const
{
  return (*this->_user);
}

void				Player::setUser(User const &user)
{
  _user = &user;
}

Talents const			&Player::getTalents() const
{
  return (*_talents);
}

bool				Player::capture(Mob &mob, bool const check)
{
  bool				done = !check;

  if (!done) {
    static unsigned int			seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::default_random_engine	rGen(seed);
    double				a = 3.0 * mob.getMaxStat("HP") - 2.0 * mob.getCurrentStat("HP");

    a *= mob.getCatchRate();
    a /= 3.0 * mob.getMaxStat("HP");
    a *= this->getDigitaliser().getEfficiency(); // Efficacité du digitaliser
    a *= 1.0 + this->getStat("Capture") / 100.0; // Multiplicateur de chances
    if (a >= 255)
      done = true;
    else
      {
	std::uniform_int_distribution<unsigned short>	dist(0, 65535);
	double						b = 65535.0 * std::pow((a / 255.0), 0.25);
	std::vector<unsigned short>			rNb = {dist(rGen), dist(rGen),
							       dist(rGen), dist(rGen)};
	std::function<bool(unsigned short)>		rChecker = [&](unsigned short nb) -> bool {
	  return (nb <= b);
	};

	done = std::all_of(rNb.begin(), rNb.end(), rChecker);
      }
  }
  if (done) {
    this->_digitaliser->addMob(mob);
    mob.setPlayer(this);
#ifndef		CLIENT_COMPILATION
    mob.resetExp();
#endif
  }
  return (done);
}

bool				Player::doCraft(std::string const &job, std::string const &craft, Stack<AItem> *&result, std::list<Stack<AItem> *> *&object)
{
  bool				ret = false;
  Job				*tmp = NULL;

  tmp = this->getJob(job);
  if (tmp)
    {
      ret = tmp->doCraft(craft, result, object);
      this->addItem(result);
      for (auto it = object->begin() ; it != object->end() ; ++it)
	this->deleteItem((*it));
    }
  return (ret);
}

bool				Player::doGather(std::string const &job, std::string const &res, Stack<AItem> *&result, unsigned int &idRessource, Carcass *carcass)
{
  bool				ret = false;
  Job				*tmp = NULL;

  tmp = this->getJob(job);
  std::cout << "Player::doGather() : tmp=" << tmp << std::endl;
  if (tmp)
    {
      std::cout << "Player::doGather() : if tmp" << std::endl;
      if (carcass)
	ret = tmp->doGather(res, result, idRessource, carcass);
      else
	ret = tmp->doGather(res, result, idRessource);
      this->addItem(result);
    }
  return (ret);
}

bool				Player::mobtoBattleMob(unsigned int const id)
{
  return (this->_digitaliser->mobtoBattleMob(id));
}

bool				Player::battleMobtoMob(unsigned int const id)
{
  return (this->_digitaliser->battleMobtoMob(id));
}

bool				Player::switchMobs(unsigned int const idMob1, unsigned int const idMob2)
{
  return (this->_digitaliser->switchMobs(idMob1, idMob2));
}

void				Player::mergeStack(unsigned int const idStack, unsigned int const idStack2)
{
  this->_inventory->mergeStack(idStack, idStack2);
}

unsigned int			Player::newStack(unsigned int const idStack, unsigned int const nb)
{
  return (this->_inventory->splitStack(idStack, nb));
}
