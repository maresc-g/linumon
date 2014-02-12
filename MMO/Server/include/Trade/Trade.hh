//
// Trade.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Sat Feb  8 17:43:32 2014 laurent ansel
// Last update Wed Feb 12 20:07:38 2014 laurent ansel
//

#ifndef 			__TRADE_HH__
# define 			__TRADE_HH__

#include			"Trame/Trame.hh"

class				Trade
{
private:
  bool				getItem();
  bool				putItem();
  bool				getMoney();
  bool				putMoney();
  bool				accept();
  bool				refuse();

public:
  Trade();
  virtual ~Trade();
};

#endif
