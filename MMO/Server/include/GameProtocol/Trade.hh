//
// Trade.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Sat Feb  8 17:43:32 2014 laurent ansel
// Last update Sat Feb  8 17:56:06 2014 laurent ansel
//

#ifndef 			__TRADE_HH__
# define 			__TRADE_HH__

#include			"Trame/Trame.hh"

class				Trade
{
private:
  bool				getItem(Trame *trame);
  bool				putItem(Trame *trame);
  bool				getMoney(Trame *trame);
  bool				putMoney(Trame *trame);
  bool				accept(Trame *trame);
  bool				refuse(Trame *trame);

public:
  Trade();
  virtual ~Trade();
};

#endif
