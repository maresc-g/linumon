//
// Trade.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Sat Feb  8 17:43:32 2014 laurent ansel
// Last update Sun Mar 16 16:50:02 2014 laurent ansel
//

#ifndef 			__TRADE_HH__
# define 			__TRADE_HH__

#include			"Trame/Trame.hh"
#include			"ClientManager/ClientManager.hh"
#include			"Utility/Id.hh"
#include			"Entities/Inventory.hh"

class				Trade : public Id
{
private:
  Player			*_player1;
  Player			*_player2;
  std::list<Mob *>		*_mobs1;
  std::list<Mob *>		*_mobs2;
  std::list<Stack<AItem> *>		*_inv1;
  std::list<Stack<AItem> *>		*_inv2;
  // Inventory			*_inv1;
  // Inventory			*_inv2;
  unsigned int			_money1;
  unsigned int			_money2;
  bool				_accept1;
  bool				_accept2;

public:
  bool				getMob(unsigned int const id, unsigned int const idMob);
  bool				putMob(unsigned int const id, unsigned int const idMob);
  bool				getItem(unsigned int const id, unsigned int const idItem);
  bool				putItem(unsigned int const id, unsigned int const idItem);
  bool				getMoney(unsigned int const id, int const money);
  bool				putMoney(unsigned int const id, int const money);
  bool				accept(unsigned int const id);
  bool				refuse();

public:
  Trade();
  virtual ~Trade();
  void				launchTrade(Player *player1, Player *player2);
  bool				stopTrade(unsigned int const idPlayer);
  unsigned int			getIdPlayer(unsigned int const idUser) const;
};

#endif
