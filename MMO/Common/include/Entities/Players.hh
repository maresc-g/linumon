//
// Players.hh for Players in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Dec  3 15:53:16 2013 alexis mestag
// Last update Thu Dec  5 11:04:56 2013 alexis mestag
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
  std::list<Player *>	*_players;

public:
  Players();
  virtual ~Players();

  void			deletePlayers();
};

#endif
