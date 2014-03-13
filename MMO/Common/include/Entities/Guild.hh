//
// Guild.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Tue Feb 25 12:42:29 2014 laurent ansel
// Last update Thu Mar 13 17:22:56 2014 alexis mestag
//

#ifndef 		__GUILD_HH__
# define 		__GUILD_HH__

# ifndef		CLIENT_COMPILATION
#  include		<odb/callback.hxx>
# endif
# include		"Database/Persistent.hh"
# include		"Utility/Nameable.hh"
# include		"Utility/ISerialization.hh"
# include		"Utility/Wrapper.hpp"

class			Player;
class			PlayerView;

class			Guild : public Persistent, public Nameable, public ISerialization,
				public ContainerWrapper<std::list<PlayerView *> >
{
  friend class		odb::access;

private:
#ifndef			CLIENT_COMPILATION
  void			odbCallback(odb::callback_event e, odb::database &db);
  void			odbCallback(odb::callback_event e, odb::database &db) const;
#endif
  void			deletePlayers();
  void			retrievePlayers();

private:
  Guild();
  Guild(Guild const &rhs);

  Guild		&operator=(Guild const &rhs);

public:
  Guild(std::string const &name);
  virtual ~Guild();

#ifndef			CLIENT_COMPILATION
  void			addPlayer(Player &player);

  static Guild		*createAndPersist(std::string const &name);
#endif

  void			addPlayer(PlayerView *playerView);

  virtual bool		serialization(Trame &trame) const;
  static Guild		*deserialization(Trame const &trame);
};

# include		"Entities/Views/PlayerView.hh"

# ifdef	ODB_COMPILER
#  pragma db object(Guild) callback(odbCallback)
#  pragma db member(Guild::name) virtual(std::string) get(getName()) set(setName(?)) unique type("VARCHAR(24)")
# endif

#endif
