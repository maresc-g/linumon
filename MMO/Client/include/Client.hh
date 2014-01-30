//
// Client.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Jan 24 13:21:17 2014 guillaume marescaux
// Last update Fri Jan 24 15:32:02 2014 guillaume marescaux
//

#ifndef				__CLIENT_HH__
# define	 		__CLIENT_HH__

#include			"Utility/Singleton.hpp"
#include			"Mutex/MutexVar.hpp"
#include			"eState.hh"
#include			"Core/Core.hh"

class				Client : public Singleton<Client>
{
  friend class			Singleton<Client>;

private:

  // Attributes
  MutexVar<eState>		*_state;
  Core				*_core;

  // Ctor / Dtor
  Client();
  virtual ~Client();
  Client(Client const &);
  Client			&operator=(Client const &);
};

#endif
