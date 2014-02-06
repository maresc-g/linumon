//
// User.hh for User in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 19:34:16 2013 alexis mestag
// Last update Thu Feb  6 14:45:07 2014 alexis mestag
//

#ifndef			__USER_HH__
# define		__USER_HH__

# include		<list>
# include		<string>
# include		"Database/Persistent.hh"
# include		"Entities/Players.hh"
# include		"Utility/ISerialization.hh"

class			PlayerView;

class			User : public Persistent, public ISerialization
{
  friend class		odb::access;

private:
  std::string		_pseudo;
  std::string		_password;
  // Players		_players;
  unsigned int		_id;

  User();
  User(User const &rhs);

  User			&operator=(User const &rhs);

public:
  User(std::string const &pseudo, std::string const &password);
  virtual ~User();

  std::string const	&getPseudo() const;
  void			setPseudo(std::string const &pseudo);
  std::string const	&getPassword() const;
  void			setPassword(std::string const &password);

  // Players const		&getPlayers() const;
  bool			addPlayer(Player &player);

  unsigned int		getId() const;
  void			setId(unsigned int const id);

  virtual bool		serialization(Trame &trame) const;
  static std::list<PlayerView *>	*deserialization(Trame const &trame);
};

# include		"Entities/Views/PlayerView.hh"

# ifdef	ODB_COMPILER
#  pragma db object(User)
#  pragma db member(User::_pseudo)
#  pragma db member(User::_password)
// #  pragma db member(User::_players) inverse(_user)
#  pragma db member(User::_id) transient
# endif

#endif
