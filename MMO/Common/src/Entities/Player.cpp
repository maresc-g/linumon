//
// Player.cpp for Player in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Dec  3 13:45:16 2013 alexis mestag
// Last update Tue Mar  4 13:34:14 2014 laurent ansel
//

#include			<functional>
#include			"Entities/Player.hh"
#include			"Map/Map.hh"
#ifndef			CLIENT_COMPILATION
# include			"Database/Repositories/Repository.hpp"
# include			"Stats/TalentTree-odb.hxx"
# include			"Stats/StatKey-odb.hxx"
# include			"Entities/DBZone-odb.hxx"
# include			"Database/Repositories/FactionRepository.hpp"
#endif

Player::Player() :
  Persistent(), ACharacter("", eCharacter::PLAYER), _type(PlayerType::PLAYER),
  _digitaliser(new Digitaliser), _coord(new PlayerCoordinate),
  _faction(NULL), _talentTree(NULL), _talents(new Talents),
  _inventory(new Inventory), _jobs(new Jobs), _guild(NULL)
# ifndef	CLIENT_COMPILATION
  , _dbZone(NULL)
# else
  , _zone("NONE")
# endif
{

}

Player::Player(std::string const &name, std::string const &factionName) :
  Persistent(), ACharacter(name, eCharacter::PLAYER), _type(PlayerType::PLAYER),
  _digitaliser(new Digitaliser), _coord(new PlayerCoordinate),
  _faction(NULL), _talentTree(NULL), _talents(new Talents),
  _inventory(new Inventory), _jobs(new Jobs), _guild(NULL)
# ifndef	CLIENT_COMPILATION
  , _dbZone(NULL)
# else
  , _zone("NONE")
# endif
{
  # ifndef	CLIENT_COMPILATION
  this->initConstPointersForNewPlayers();

  Faction			*faction = Database::getRepository<Faction>().getByName(factionName);

  if (faction) {
    this->setFaction(*faction);
    this->applyFactionEffect();
  }
  # else
  (void)factionName;
  # endif
}

Player::Player(Player const &rhs) :
  Persistent(rhs), ACharacter(rhs), _digitaliser(new Digitaliser), _coord(new PlayerCoordinate),
  _talents(new Talents), _jobs(new Jobs)
{
  *this = rhs;
}

Player::~Player()
{
  delete _digitaliser;
  delete _coord;
  this->deleteTalents();
  // delete _faction; // Causes an invalid pointer delete
}

Player				&Player::operator=(Player const &rhs)
{
  if (this != &rhs)
    {
      this->setDigitaliser(rhs.getDigitaliser());
      this->setCoord(rhs.getCoord());
      this->setFaction(rhs.getFaction());
      this->setGuild(*rhs.getGuild());
      this->setZone(rhs.getZone());
    }
  return (*this);
}

#ifndef		CLIENT_COMPILATION
void					Player::initConstPointersForNewPlayers()
{
  Repository<TalentTree>		*rtt = &Database::getRepository<TalentTree>();
  Repository<AuthorizedStatKeys>	*rask = &Database::getRepository<AuthorizedStatKeys>();
  Repository<DBZone>			*rdbz = &Database::getRepository<DBZone>();

  this->setTalentTree(*rtt->getById(1));
  this->setStatKeys(*rask->getById(1));
  this->setDBZone(*rdbz->getById(1));
}

void					Player::applyFactionEffect()
{
  _faction->applyEffect(*this);
}
#endif

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

Guild const			*Player::getGuild() const
{
  return (_guild);
}

void				Player::setGuild(Guild const &guild)
{
  _guild = &guild;
}

Digitaliser const		&Player::getDigitaliser() const
{
  return (*_digitaliser);
}

void				Player::setDigitaliser(Digitaliser const &digit)
{
  *this->_digitaliser = digit;
}

Inventory const			&Player::getInventory() const
{
  return (*this->_inventory);
}

void				Player::setInventory(Inventory *inventory)
{
  this->_inventory = inventory;
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

void				Player::deleteItem(unsigned int const item)
{
  this->_inventory->deleteItem(item);
}

void				Player::addItem(AItem *item)
{
  this->_inventory->addItem(item);
}

AItem				*Player::getAndDeleteItem(unsigned int const item) const
{
  return (this->_inventory->getAndDeleteItem(item));
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

bool				Player::putPlayerEquipment(unsigned int const idItem)
{
  bool				ret = false;
  AItem				*item;
  Stuff				*old;

  /*effect item*/
  item = this->getAndDeleteItem(idItem);
  if (item && item->getItemType() == AItem::STUFF)
    {
      ret = this->addStuff(dynamic_cast<Stuff *>(item), old);
      if (ret && old)
	this->addItem(old);
    }
  else if (item)
    this->addItem(item);
  return (ret);
}

bool				Player::putMobEquipment(unsigned int const idMod,unsigned int const idItem)
{
  bool				ret = false;
  AItem				*item;
  Stuff				*old;
  Mob				*mob;

  mob = this->_digitaliser->getMob(idMod);
  if (mob)
    {
      item = this->getAndDeleteItem(idItem);
      if (item && item->getItemType() == AItem::STUFF)
	{
	  ret = mob->addStuff(reinterpret_cast<Stuff *>(item), old);
	  if (ret && old)
	    this->addItem(old);
	}
      else if (item)
	this->addItem(item);
    }
  return (ret);
}



bool				Player::serialization(Trame &trame) const
{
  bool				ret = true;

  trame["PLAYER"]["ID"] = static_cast<int>(this->getId());
  trame["PLAYER"]["NAME"] = this->getName();
  trame["PLAYER"]["TYPE"] = this->getStatEntityType();
  this->_coord->serialization(trame(trame["PLAYER"]));
  this->_faction->serialization(trame(trame["PLAYER"]));
  if (this->_guild)
    this->_guild->serialization(trame(trame["PLAYER"]));
  this->_digitaliser->serialization(trame(trame["PLAYER"]));
  this->getStats().serialization(trame(trame["PLAYER"]["STATS"]));
  this->getTmpStats().serialization(trame(trame["PLAYER"]["TMPSTATS"]));
  this->getLevelObject().serialization(trame(trame["PLAYER"]));
  trame["PLAYER"]["CEXP"] = this->getCurrentExp();
  trame["PLAYER"]["ZONE"] = this->getZone();
  this->_inventory->serialization(trame(trame["PLAYER"]));
  this->_talentTree->serialization(trame(trame["PLAYER"]));
  this->getEquipment().serialization(trame(trame["PLAYER"]));
  for (auto it = this->_talents->begin() ; it != this->_talents->end() ; ++it)
    (*it)->serialization(trame(trame["PLAYER"]["TALENTS"]));
  this->_jobs->serialization(trame(trame["PLAYER"]));
  return (ret);
}

Player				*Player::deserialization(Trame const &trame)
{
  Player			*player = NULL;
  Talents			*talents = NULL;

  if (trame.isMember("PLAYER"))
    {
      player = new Player(trame["PLAYER"]["NAME"].asString());
      player->setId(trame["PLAYER"]["ID"].asUInt());
      player->setStatEntityType(static_cast<AStatEntity::eStatEntity>(trame["PLAYER"]["TYPE"].asInt()));
      player->setCoord(*PlayerCoordinate::deserialization(trame(trame["PLAYER"])));
      player->setFaction(*Faction::deserialization(trame(trame["PLAYER"])));
      player->setGuild(*Guild::deserialization(trame(trame["PLAYER"])));
      player->setZone(trame["PLAYER"]["ZONE"].asString());

      Level			*lvl = Level::deserialization(trame(trame["PLAYER"]));
      if (lvl)
	player->setLevelObject(*lvl);

      if (trame["PLAYER"].isMember("CEXP"))
	player->setCurrentExp(trame["PLAYER"]["CEXP"].asUInt());

      TalentTree		*tree = TalentTree::deserialization(trame(trame["PLAYER"]));
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

      Stats			*stats = Stats::deserialization(trame(trame["PLAYER"]));
      if (stats)
      	player->setStats(*stats);

      stats = Stats::deserialization(trame(trame["PLAYER"]));
      if (stats)
      	player->setTmpStats(*stats);

      if (!trame["PLAYER"]["TALENTS"].empty())
	{
	  auto			members = trame["PLAYER"]["TALENTS"].getMemberNames();

	  talents = new Talents;
	  for (auto it = members.begin() ; it != members.end() ; ++it)
	    {
	      talents->getContainer().push_back(Talent::deserialization(trame(trame["PLAYER"]["TALENTS"][*it])));
	    }
	  player->setTalents(*talents);
	}

      Jobs			*jobs = Jobs::deserialization(trame(trame["PLAYER"]));
      if (jobs)
	player->setJobs(jobs);
    }
  return (player);
}

void				Player::addTalent(Talent *talent)
{
  this->_talents->getContainer().push_back(talent);
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

void				Player::deleteTalents()
{
  static std::function<bool(Talent *)>	talentsDeleter = [](Talent *t) {
    delete t;
    return (true);
  };

  _talents->getContainer().remove_if(talentsDeleter);
}

Talents const			&Player::getTalents() const
{
  return (*_talents);
}

void				Player::capture(Mob const &mob)
{
  this->_digitaliser->addMob(mob);
}

bool				Player::doCraft(std::string const &job, std::string const &craft, std::list<AItem *> &result, std::list<std::pair<unsigned int, unsigned int> > &object)
{
  bool				ret = false;
  Job				*tmp = NULL;
  std::list<std::pair<std::string, unsigned int> >	tmpObject;

  tmp = this->getJob(job);
  if (tmp)
    {
      tmp->doCraft(craft, result, tmpObject);
      for (auto it = result.begin() ; it != result.end() ; ++it)
	{
	  unsigned int		id = _inventory->getIdItem((*it)->getName());
	  if (id != 0)
	    (*it)->setId(id);
	  this->addItem(*it);
	}
      for (auto it = tmpObject.begin() ; it != tmpObject.end() ; ++it)
	{
	  object.push_back(std::make_pair(_inventory->getIdItem(it->first), it->second));
	  for (unsigned int i = 0 ; i < it->second ; ++i)
	    this->deleteItem(object.back().first);
	}
    }
  return (ret);
}

bool				Player::doGather(std::string const &job, std::string const &res, std::list<AItem *> &result, unsigned int &idRessource)
{
  bool				ret = false;
  Job				*tmp = NULL;

  tmp = this->getJob(job);
  if (tmp)
    {
      tmp->doGather(res, result, idRessource);
      for (auto it = result.begin() ; it != result.end() ; ++it)
	{
	  unsigned int		id = _inventory->getIdItem((*it)->getName());
	  if (id != 0)
	    (*it)->setId(id);
	  this->addItem(*it);
	}
    }
  return (ret);
}
