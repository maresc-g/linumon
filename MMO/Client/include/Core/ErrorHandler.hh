//
// ErrorHandler.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Mon Feb  3 12:55:31 2014 guillaume marescaux
// Last update Mon Mar 24 11:22:18 2014 guillaume marescaux
//

#ifndef 		__ERRORHANDLER_HH__
# define 		__ERRORHANDLER_HH__

#include		<map>
#include		"Error/Error.hpp"
#include		"Mutex/MutexVar.hpp"
#include		"Common/eState.hh"
#include		"Common/ErrorBox.hh"

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
  void			handleError(Error const &error, MutexVar<CLIENT::eState> *state, MutexVar<ErrorBox *> *errorBox);

private:

  // Private Methods
  void			badUsernamePass(MutexVar<CLIENT::eState> *state, MutexVar<ErrorBox *> *errorBox);
  void			userConnected(MutexVar<CLIENT::eState> *state, MutexVar<ErrorBox *> *errorBox);
  void			nameExists(MutexVar<CLIENT::eState> *state, MutexVar<ErrorBox *> *errorBox);
  void			guildExists(MutexVar<CLIENT::eState> *state, MutexVar<ErrorBox *> *errorBox);
  void			alreadyInGuild(MutexVar<CLIENT::eState> *state, MutexVar<ErrorBox *> *errorBox);
  void			occupied(MutexVar<CLIENT::eState> *state, MutexVar<ErrorBox *> *errorBox);
};

#endif
