//
// Players.hh for Players in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Dec  3 15:53:16 2013 alexis mestag
// Last update Mon Feb  3 15:23:41 2014 alexis mestag
//

#ifndef			__PLAYERS_HH__
# define		__PLAYERS_HH__

# include		<odb/core.hxx>
# include		<list>
# include		"Utility/ISerialization.hh"

class			Player;

class			Players : public ISerialization
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

  void			addPlayer(Player &player);
  void			deletePlayers();
  virtual bool		serialization(Trame &trame) const;
};

# include		"Entities/Player.hh"

# ifdef ODB_COMPILER
#  pragma db value(Players)
# endif

#endif
