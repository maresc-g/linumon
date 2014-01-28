//
// Players.hh for Players in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Dec  3 15:53:16 2013 alexis mestag
// Last update Fri Jan 24 13:17:03 2014 alexis mestag
//

#ifndef			__PLAYERS_HH__
# define		__PLAYERS_HH__

# include		<odb/core.hxx>
# include		<list>
# include		"Entities/Player.hh"

class			Players
{
  friend class		odb::access;

private:
  std::list<Player *>	_players;

private:
  Players(Players const &rhs);

  Players		&operator=(Players const &rhs);

public:
  Players();
  virtual ~Players();

  void			deletePlayers();
};

# ifdef ODB_COMPILER
#  pragma db value(Players)
# endif

#endif
