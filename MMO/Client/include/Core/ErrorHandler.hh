//
// ErrorHandler.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Mon Feb  3 12:55:31 2014 guillaume marescaux
// Last update Wed Feb  5 10:59:35 2014 guillaume marescaux
//

#ifndef 		__ERRORHANDLER_HH__
# define 		__ERRORHANDLER_HH__

#include		<map>
#include		"Error/Error.hpp"
#include		"Mutex/MutexVar.hpp"
#include		"eState.hh"

class			ErrorHandler
{
private:

  // private Ctor / Dtor
  ErrorHandler(ErrorHandler const &);
  ErrorHandler		&operator=(ErrorHandler const &);

public:

  // Ctor / Dtor
  ErrorHandler();
  virtual ~ErrorHandler();

  // Methods
  void			handleError(Error const &error, MutexVar<eState> *state);

private:

  // Private Methods
  void			badUsernamePass(MutexVar<eState> *state);
  void			userConnected(MutexVar<eState> *state);
  void			nameExists(MutexVar<eState> *state);
};

#endif
