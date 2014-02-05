//
// Player.hh for Player in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Dec  3 13:44:25 2013 alexis mestag
// Last update Wed Feb  5 15:33:36 2014 alexis mestag
//

#ifndef			__PLAYER_HH__
# define		__PLAYER_HH__

# include		<list>
# include		"Database/Persistent.hh"
# include		"Entities/Digitaliser.hh"
# include		"Entities/ACharacter.hh"
# include		"Entities/Faction.hh"
# include		"Stats/TalentTree.hh"
# include		"Stats/Talent.hh"
# include		"Zone/Coordinate.hpp"
# include		"Zone/Zone.hh"
# include		"Utility/ISerialization.hh"

class			Zone;
class			User;

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
  typedef iCoordinate	PlayerCoordinate;

private:
  PlayerCoordinate		*_coord;
  Faction const			*_faction;
  Digitaliser			_digitaliser;
  ZONE::eZone			_zone;
  TalentTree const		*_talentTree;
  std::list<Talent *>		_talents;
  User const			*_user;

private:
  Player();
  Player(Player const &rhs);

  Player		&operator=(Player const &rhs);

  void			deleteTalents();

public:
  Player(std::string const &name);
  virtual ~Player();

  PlayerCoordinate const	&getCoord() const;
  PlayerCoordinate::type const	&getX() const;
  PlayerCoordinate::type const	&getY() const;
  void				setCoord(PlayerCoordinate const &coord);
  void				setCoord(PlayerCoordinate::type const &x,  // Keep calm :
					 PlayerCoordinate::type const &y); // these are just integers
  void				setX(PlayerCoordinate::type const &x);
  void				setY(PlayerCoordinate::type const &y);

  Faction const		&getFaction() const;
  void			setFaction(Faction const &faction);

  Digitaliser const	&getDigitaliser() const;
  // No setter for this attribute

  ZONE::eZone		getZone() const;
  void			setZone(ZONE::eZone const zone);

  std::list<Talent *> const	&getTalents() const;

  virtual bool			serialization(Trame &trame) const;
  static Player			*deserialization(Trame const &trame);
};

# include			"Entities/User.hh"

# ifdef	ODB_COMPILER
#  pragma db object(Player) session(false)
#  pragma db member(Player::_zone)
#  pragma db member(Player::_coord) transient
#  pragma db member(Player::_x) virtual(Player::PlayerCoordinate::type) get(_coord->getX()) set(_coord->setX(?))
#  pragma db member(Player::_y) virtual(Player::PlayerCoordinate::type) get(_coord->getY()) set(_coord->setY(?))
#  pragma db member(Player::_faction) not_null
#  pragma db member(Player::_digitaliser) value_not_null id_column("player_id") value_column("mob_id")
# endif

#endif
