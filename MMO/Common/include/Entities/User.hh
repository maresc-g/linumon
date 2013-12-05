//
// User.hh for User in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 19:34:16 2013 alexis mestag
// Last update Thu Dec  5 13:12:46 2013 alexis mestag
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
  Players		*_players;

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
};

# ifdef	ODB_COMPILER
#  pragma db object(User)
#  pragma db member(User::_pseudo)
#  pragma db member(User::_password)
#  pragma db member(User::_players) value_not_null id_column("user_id") value_column("player_id")
# endif

#endif
