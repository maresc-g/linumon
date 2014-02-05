//
// UserView.hh for UserView in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Feb  3 09:52:15 2014 alexis mestag
// Last update Mon Feb  3 16:43:46 2014 alexis mestag
//

#ifndef				__USERVIEW_HH__
# define			__USERVIEW_HH__

# include			<list>
# include			"Entities/User.hh"
// # include			"Entities/Views/PlayerView.hh"

class				UserView
{
public:
  unsigned long			persistentId;
  std::string			pseudo;
  std::string			password;
};

# ifdef	ODB_COMPILER
#  pragma db view(UserView) object(User)
# endif

#endif