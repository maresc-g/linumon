//
// Player.hh for Player in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Dec  3 13:44:25 2013 alexis mestag
// Last update Tue Dec 10 15:39:16 2013 alexis mestag
//

#ifndef			__PLAYER_HH__
# define		__PLAYER_HH__

# include		"Database/Persistent.hh"
# include		"Entities/Digitaliser.hh"
# include		"Entities/ACharacter.hh"
# include		"Entities/Faction.hh"
# include		"Map/Coordinate.hpp"

class			Player : public Persistent, public ACharacter
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
  Digitaliser			*_digitaliser;

private:
  Player();
  Player(Player const &rhs);

  Player		&operator=(Player const &rhs);

public:
  Player(std::string const &name);
  virtual ~Player();

  PlayerCoordinate const	&getCoord() const;
  void			setCoord(PlayerCoordinate const &coord);
  void			setCoord(PlayerCoordinate::type const &x,  // Keep calm :
				 PlayerCoordinate::type const &y); // these are just integers (int)

  Faction const		&getFaction() const;
  void			setFaction(Faction const &faction);

  Digitaliser const	&getDigitaliser() const;
  // No setter for this attribute
};

# ifdef	ODB_COMPILER
#  pragma db object(Player)
#  pragma db member(Player::_coord) transient
#  pragma db member(Player::_x) virtual(Player::PlayerCoordinate::type) access(Player::_coord->_x)
#  pragma db member(Player::_y) virtual(Player::PlayerCoordinate::type) access(Player::_coord->_y)
#  pragma db member(Player::_faction) not_null
#  pragma db member(Player::_digitaliser) value_not_null id_column("player_id") value_column("mob_id")
# endif

#endif
