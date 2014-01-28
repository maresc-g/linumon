//
// Players.hh for Players in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Dec  3 15:53:16 2013 alexis mestag
// Last update Tue Jan 28 12:44:16 2014 laurent ansel
//

#ifndef			__PLAYERS_HH__
# define		__PLAYERS_HH__

# include		<odb/core.hxx>
# include		<list>
# include		"Entities/Player.hh"
# include		"Utility/ISerialization.hh"

class			Players// : public ISerialization
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
  //  virtual bool		serialization(Trame &trame);
};

# ifdef ODB_COMPILER
#  pragma db value(Players)
# endif

#endif
