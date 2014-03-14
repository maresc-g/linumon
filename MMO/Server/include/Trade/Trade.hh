//
// Trade.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Sat Feb  8 17:43:32 2014 laurent ansel
// Last update Fri Mar 14 14:47:16 2014 laurent ansel
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
  Inventory			*_inv1;
  Inventory			*_inv2;
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
