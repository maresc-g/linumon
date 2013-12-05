//
// Player.hh for Player in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Dec  3 13:44:25 2013 alexis mestag
// Last update Thu Dec  5 14:34:20 2013 alexis mestag
//

#ifndef			__PLAYER_HH__
# define		__PLAYER_HH__

# include		"Database/Persistent.hh"
# include		"Entities/ACharacter.hh"

class			Player : public Persistent, public ACharacter
{
  friend class		odb::access;

private:
  Player();
  Player(Player const &rhs);

  Player		&operator=(Player const &rhs);

public:
  Player(std::string const &name);
  virtual ~Player();
};

# ifdef	ODB_COMPILER
#  pragma db object(Player)
# endif

#endif
