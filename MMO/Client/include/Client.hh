//
// Client.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Jan 24 13:21:17 2014 guillaume marescaux
// Last update Fri Mar 21 15:38:30 2014 cyril jourdain
//

#ifndef				__CLIENT_HH__
# define	 		__CLIENT_HH__

# include			"Utility/Singleton.hpp"
# include			"Mutex/MutexVar.hpp"
# include			"Common/eState.hh"
# include			"Core/Core.hh"
# include		        "SFML/SFMLView.hpp"
# include		        "Qt/WindowManager.hh"
# include			"Qt/Views/LoginView.hh"
# include			<Qt/qapplication.h>
# include			<Qt/qframe.h>
# include			<Qt/qpushbutton.h>
# include			<Qt/qfile.h>
# include			<Qt/qgridlayout.h>
# include			"Entities/Views/PlayerView.hh"
# include			"Chat/Chat.hh"
# include			"Battle/Battle.hh"
# include			"Trade/Trade.hh"
# include			"Entities/AItem.hh"
# include			"Common/ErrorBox.hh"

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
  MutexVar<Trade *>		*_trade;
  MutexVar<bool>		*_heal;
  Core				*_core;
  MutexVar<ErrorBox*>		*_errorBox;
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
  void				getStuff(unsigned int idItem, unsigned int target);
  void				putStuff(unsigned int idItem, unsigned int target);
  void				talents(Talents const &talents);
  void				craft(std::string const &craftName, std::string const &jobName);
  void				gather(unsigned int idRessource, std::string const &jobName, unsigned int idCarcass = 0);
  void				useObject(unsigned int target, unsigned int item);
  void				interaction(eInteraction interact, std::string const &name);
  void				putItem(unsigned int idTrade, unsigned int idStack);
  void				getItem(unsigned int idTrade, unsigned int idStack);
  void				putMob(unsigned int idTrade, unsigned int idMob);
  void				getMob(unsigned int idTrade, unsigned int idMob);
  void				putMoney(unsigned int idTrade, unsigned int money);
  void				getMoney(unsigned int idTrade, unsigned int money);
  void				accept(void);
  void				refuse(void);
  void				quit(void);
  void				heal(void);
  void				disconnect(void);
  void				switchPlayer(void);
  void				mobtoBattleMob(unsigned int id);
  void				battleMobtoMob(unsigned int id);
  void				switchMobs(unsigned int idMob1, unsigned int idMob2);
  void				merge(unsigned int idStack1, unsigned int idStack2);
  void				newStack(unsigned int idStack, unsigned int nb);
};

#endif
