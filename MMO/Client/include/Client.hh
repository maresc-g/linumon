//
// Client.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Jan 24 13:21:17 2014 guillaume marescaux
// Last update Tue Mar 11 14:33:04 2014 laurent ansel
//

#ifndef				__CLIENT_HH__
# define	 		__CLIENT_HH__

#include			"Utility/Singleton.hpp"
#include			"Mutex/MutexVar.hpp"
#include			"Common/eState.hh"
#include			"Core/Core.hh"
#include		        "SFML/SFMLView.hpp"
#include		        "Qt/WindowManager.hh"
#include			"Qt/Views/LoginView.hh"
#include			<Qt/qapplication.h>
#include			<Qt/qframe.h>
#include			<Qt/qpushbutton.h>
#include			<Qt/qfile.h>
#include			<Qt/qgridlayout.h>
#include			"Entities/Views/PlayerView.hh"
#include			"Chat/Chat.hh"
#include			"Battle/Battle.hh"
#include			"Entities/AItem.hh"

class				Client : public Singleton<Client>
{
  friend class			Singleton<Client>;

private:

  // Attributes
  MutexVar<CLIENT::eState>	*_state;
  MutexVar<Player *>		*_player;
  MutexVar<std::list<PlayerView *> *>		*_players;
  MutexVar<Chat *>		*_chat;
  MutexVar<bool>		*_newPlayer;
  MutexVar<Battle *>		*_battle;
  Core				*_core;
  WindowManager			*_manager;

  // Ctor / Dtor
  Client();
  virtual ~Client();
  Client(Client const &);
  Client			&operator=(Client const &);

public:

  void				init(int &ac, char **av);
  void				connection(std::string const &pseudo, std::string const &pass);
  void				choosePlayer(PlayerView const &player);
  void				create(std::string const &name, std::string const &faction);
  bool				move(CLIENT::eDirection dir);
  void				sendChat(std::string const &msg);
  MutexVar<Chat *>		*getChat();
  void				spell(unsigned int idBattle, Spell const &spell, unsigned int launcher, unsigned int target);
  void				capture(unsigned int idBattle, unsigned int target);
  void				sendSwitch(unsigned int idBattle, unsigned int target, unsigned int newMob);
  void				stuff(int action, unsigned int idItem, unsigned int target);
  // void				talents();
  void				craft(std::string const &craftName, std::string const &jobName);
  // void				gather();
  void				useObject(unsigned int target, unsigned int item);
  // void				unsigned interaction();
  void				putItem(AItem const &item);
  void				getItem(AItem const &item);
  void				sendMoney(unsigned int money);
  void				accept(void);
  void				refuse(void);
  void				quit(void);
  void				heal(void);
  void				disconnect(void);
  void				switchPlayer(void);
};

#endif
