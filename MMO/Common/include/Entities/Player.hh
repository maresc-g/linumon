//
// Player.hh for Player in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Dec  3 13:44:25 2013 alexis mestag
// Last update Wed Mar 26 02:52:35 2014 alexis mestag
//

#ifndef			__PLAYER_HH__
# define		__PLAYER_HH__

# include		<list>
# include		"Database/Persistent.hh"
# include		"Entities/Digitaliser.hh"
# ifndef	CLIENT_COMPILATION
#  include		"Entities/DBZone.hh"
# endif
# include		"Entities/ACharacter.hh"
# include		"Stats/Talents.hh"
# include		"Zone/Coordinate.hpp"
# include		"Utility/ISerialization.hh"
# include		"Entities/Inventory.hh"
# include		"Entities/Jobs.hh"
# include		"Entities/Guild.hh"

class			User;
class			Faction;
class			Drop;
class			TalentTree;

class			Player : public Persistent, public ACharacter, public ISerialization
{
  friend class		odb::access;

  // If you want to change the Coordinate template
  //	from iCoordinate (= Coordinate<int>)
  //	to Coordinate<Whatever>
  // Please just change the typedef statement below to
  // typedef Coordinate<Whatever>	PlayerCoordinate;
  // /!\ There's no need to change any getter or setter !!
  // If you are scared, please refer to mestag_a
public:
  typedef iCoordinate		PlayerCoordinate; // This one is kept for compatibility issues
  typedef PlayerCoordinate	Coordinate;

  enum				PlayerType
    {
      PLAYER,
      AI
    };

protected:
  PlayerType			_type;
  Digitaliser			*_digitaliser;

private:
  bool				_out;
  PlayerCoordinate		*_coord;
  Faction const			*_faction;
  TalentTree const		*_talentTree;
  Talents			*_talents;
  User const			*_user;
  Inventory			*_inventory;
  Jobs				*_jobs;
  Guild				*_guild;
# ifndef		CLIENT_COMPILATION
  ExperienceCurve const		*_expCurve;
  DBZone const			*_dbZone;
# else
  std::string			_zone;
# endif

private:
  Player();
  Player(Player const &rhs);

  Player		&operator=(Player const &rhs);

# ifndef		CLIENT_COMPILATION
  void			initConstPointersForNewPlayers();
  void			applyFactionEffect();
  void			setExperienceCurve(ExperienceCurve const &expCurve);
# endif
public:
  Player(std::string const &name, std::string const &factionName = "", User const *user = NULL);
  virtual ~Player();

  void				setOut(bool const);
  bool				getOut() const;
  PlayerCoordinate const	&getCoord() const;
  PlayerCoordinate::type const	&getX() const;
  PlayerCoordinate::type const	&getY() const;
  void				setType(Player::PlayerType const type);
  Player::PlayerType		getType() const;
  void				setCoord(PlayerCoordinate const &coord);
  void				setCoord(PlayerCoordinate::type const &x,  // Keep calm :
					 PlayerCoordinate::type const &y); // these are just integers
  void				setX(PlayerCoordinate::type const &x);
  void				setY(PlayerCoordinate::type const &y);

  Faction const			&getFaction() const;
  void				setFaction(Faction const &faction);

  Guild				*getGuild() const;
  void				setGuild(Guild *guild);
  void				guildAddPlayer(PlayerView *playerView);
  void				guildRemovePlayer(std::string const &name);

  void				setDigitaliser(Digitaliser const &digit);
  Digitaliser const		&getDigitaliser() const;
  Digitaliser			&getDigitaliser();

# ifndef	CLIENT_COMPILATION
  DBZone const			&getDBZone() const;
  void				setDBZone(DBZone const &dbZone);
# endif
  std::string			getZone() const;
  void				setZone(std::string const zone);

  Inventory const		&getInventory() const;
  void				setInventory(Inventory *inventory);

# ifndef	CLIENT_COMPILATION
  virtual ExperienceCurve const	&getExperienceCurve() const;
# endif
  virtual void			levelUp();

  void				addTalent(Talent *talent);
  Talents const			&getTalents() const;
  void				setTalents(Talents const &list);
  bool				incTalent(TalentModel const &model);
  Talent const			*getTalentFromModel(TalentModel const &model) const;
  bool				updateTalent(TalentModel const &model, unsigned int const toPoints);
  void				applyAllTalentsToMob(Mob &mob);

  TalentTree const		&getTalentTree() const;
  void				setTalentTree(TalentTree const &tree);

  User const			&getUser() const;
  void				setUser(User const &user);

  void				addCartridge(Cartridge const &cartridge);
  Cartridge			*getNextCartridge();
  bool				capture(Mob &mob, bool const check = true);

  Mob const			&getMob(unsigned int const id);

  bool				isMyMob(unsigned int const id);

  void				deleteItem(unsigned int const stack);
  void				deleteItem(Stack<AItem> *stack);
  void				addItem(AItem *item);
  void				addItem(Stack<AItem> *stack);
  AItem				*getAndDeleteItem(unsigned int const stack) const;
  void				drop(Drop const &drop);

  void				addMob(Mob *mob);
  Mob				*getAndDeleteMob(unsigned int const mob) const;

  void				addMoney(int const money);

  Jobs const			&getJobs() const;
  void				setJobs(Jobs *jobs);
  void				setJob(Job *job);
  void				setJob(std::string const &name, Job *job);
  Job				*getJob(std::string const &name) const;

  bool				doCraft(std::string const &job, std::string const &craft, Stack<AItem> *&result, std::list<Stack<AItem> *> *&object);
  bool				doGather(std::string const &job, std::string const &ressource, Stack<AItem> *&result, unsigned int &idRessource, Carcass *carcass);
  bool				doGather(std::string const &job, std::list<Stack<AItem>*> *&result,
  					 Carcass *carcass);

  bool				getPlayerEquipment(unsigned int const idItem);
  bool				getMobEquipment(unsigned int const idMod, unsigned int const idItem);
  bool				putPlayerEquipment(unsigned int const idStack);
  bool				putMobEquipment(unsigned int const idMod, unsigned int const idStack);

  void				useObject(unsigned int const target, unsigned int const stack);

  bool				mobtoBattleMob(unsigned int const id);
  bool				battleMobtoMob(unsigned int const id);
  bool				switchMobs(unsigned int const idMob1, unsigned int const idMob2);

  void				mergeStack(unsigned int const idStack, unsigned int const idStack2);
  unsigned int			newStack(unsigned int const idStack, unsigned int const nb);


  virtual bool			serialization(Trame &trame) const;
  static Player			*deserialization(Trame const &trame);
};

# include			"Stats/TalentTree.hh"
# include			"Entities/User.hh"
# include			"Entities/Faction.hh"

# ifdef	ODB_COMPILER
#  pragma db object(Player)
#  pragma db member(Player::_out) transient
#  pragma db member(Player::_type) transient
#  pragma db member(Player::_coord) transient
#  pragma db member(Player::_digitaliser) transient
#  pragma db member(Player::_talents) transient
#  pragma db member(Player::_inventory) transient
#  pragma db member(Player::_jobs) transient
#  pragma db member(Player::name) virtual(std::string) get(getName()) set(setName(?)) unique type("VARCHAR(24)")
#  pragma db member(Player::_x) virtual(Player::Coordinate::type) get(_coord->getX()) set(_coord->setX(?))
#  pragma db member(Player::_y) virtual(Player::Coordinate::type) get(_coord->getY()) set(_coord->setY(?))
#  pragma db member(Player::_faction) not_null
#  pragma db member(Player::mobs) virtual(Digitaliser::container_type) get(_digitaliser->getContainer()) set(_digitaliser->setContainer(?)) value_not_null
#  pragma db member(Player::battleMobs) virtual(Digitaliser::container_type) get(_digitaliser->getBattleMobs()) set(_digitaliser->setBattleMobs(?)) value_not_null
#  pragma db member(Player::_dbZone) not_null
#  pragma db member(Player::_inventoryPath) virtual(std::string) get(_inventory->getPath()) set(_inventory->setPath(?))
#  pragma db member(Player::_money) virtual(unsigned int) get(_inventory->getMoney()) set(_inventory->setMoney(?))
#  pragma db member(Player::_limit) virtual(unsigned int) get(_inventory->getLimit()) set(_inventory->setLimit(?))
#  pragma db member(Player::jobs) virtual(Jobs::container_type) get(_jobs->getContainer()) set(_jobs->setContainer(?)) value_not_null
#  pragma db member(Player::talents) virtual(Talents::container_type) get(_talents->getContainer()) set(_talents->setContainer(?)) value_not_null
#  pragma db member(Player::currentPts) virtual(unsigned int) get(_talents->getCurrentPts()) set(_talents->setCurrentPts(?))
// #  pragma db member(Player::digitaliserEfficiency) virtual(double) get(_digitaliser->getEfficiency()) set(_digitaliser->setEfficiency(?))
#  pragma db member(Player::cartridgeClip) virtual(CartridgeClip::summary_type) get(_digitaliser->getCartridgeClip().getClipSummary()) set(_digitaliser->setCartridgeClip(?))
#  pragma db member(Player::_talentTree) not_null
#  pragma db member(Player::_user) not_null
#  pragma db member(Player::_expCurve) not_null
# endif

#endif
