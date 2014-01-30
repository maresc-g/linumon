//
// User.hh for User in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 19:34:16 2013 alexis mestag
// Last update Thu Jan 30 15:16:40 2014 alexis mestag
//

#ifndef			__USER_HH__
# define		__USER_HH__

# include		<list>
# include		<string>
# include		"Database/Persistent.hh"
# include		"Entities/Players.hh"

class			User : public Persistent
{
  friend class		odb::access;

private:
  std::string		_pseudo;
  std::string		_password;
  Players		_players;

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

  Players const		&getPlayers() const;
  bool			addPlayer(Player &player);
};

# ifdef	ODB_COMPILER
#  pragma db object(User)
#  pragma db member(User::_pseudo)
#  pragma db member(User::_password)
# endif

#endif
