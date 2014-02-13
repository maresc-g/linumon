//
// TrameManager.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Wed Feb 12 20:12:21 2014 laurent ansel
// Last update Wed Feb 12 20:34:00 2014 laurent ansel
//

#ifndef 			__TRADEMANAGER_HH__
# define 			__TRADEMANAGER_HH__

#include			<list>
#include			"Utility/Singleton.hpp"
#include			"Trade/Trade.hh"

class				TradeManager : public Singleton<TradeManager>
{
  friend class			Singleton<TradeManager>;

private:
  std::list<Trade *>		*_list;

private:
  bool				getItem(Trame *trame);
  bool				putItem(Trame *trame);
  bool				getMoney(Trame *trame);
  bool				putMoney(Trame *trame);
  bool				accept(Trame *trame);
  bool				refuse(Trame *trame);

  TradeManager();
  virtual ~TradeManager();

public:
  void				newTrade(unsigned int const id, unsigned int const idTarget);
};

#endif
