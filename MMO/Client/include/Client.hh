//
// Client.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Jan 24 13:21:17 2014 guillaume marescaux
// Last update Tue Feb  4 11:16:43 2014 guillaume marescaux
//

#ifndef				__CLIENT_HH__
# define	 		__CLIENT_HH__

#include			"Utility/Singleton.hpp"
#include			"Mutex/MutexVar.hpp"
#include			"eState.hh"
#include			"Core/Core.hh"
#include		        "SFML/SFMLView.hpp"
#include		        "Qt/WindowManager.hh"
#include			"Qt/LoginView/LoginView.hh"
#include			<Qt/qapplication.h>
#include			<Qt/qframe.h>
#include			<Qt/qpushbutton.h>
#include			<Qt/qfile.h>
#include			<Qt/qgridlayout.h>
#include			"Entities/Views/PlayerView.hh"

class				Client : public Singleton<Client>
{
  friend class			Singleton<Client>;

private:

  // Attributes
  MutexVar<eState>		*_state;
  MutexVar<Player *>		*_player;
  MutexVar<std::list<PlayerView *> *>		*_players;
  Core				*_core;
  WindowManager			*_manager;

  // Ctor / Dtor
  Client();
  virtual ~Client();
  Client(Client const &);
  Client			&operator=(Client const &);

public:

  void				init(int ac, char **av);
  void				connection(std::string const &pseudo, std::string const &pass);
  void				choosePlayer(PlayerView const &player);
};

#endif
