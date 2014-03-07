//
// TrameManager.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Wed Feb 12 20:12:21 2014 laurent ansel
// Last update Fri Mar  7 13:46:40 2014 laurent ansel
//

#ifndef 			__TRADEMANAGER_HH__
# define 			__TRADEMANAGER_HH__

#include			<list>
#include			"Utility/Singleton.hpp"
#include			"Trade/Trade.hh"
#include			"Mutex/Mutex.hpp"

#define	DEFAULT_TRADE		100

class				TradeManager : public Singleton<TradeManager>
{
  friend class			Singleton<TradeManager>;

private:
  std::list<std::pair<bool, Trade *> >	*_list;
  Mutex				*_mutex;

private:
  bool				getMob(Trame *trame);
  bool				putMob(Trame *trame);
  bool				getItem(Trame *trame);
  bool				putItem(Trame *trame);
  bool				getMoney(Trame *trame);
  bool				putMoney(Trame *trame);
  bool				accept(Trame *trame);
  bool				refuse(Trame *trame);

  TradeManager();
  virtual ~TradeManager();

public:
  void				newTrade(Player *player1, Player *player2);
  bool				disconnectPlayer(unsigned int const idPlayer);
};

#endif
