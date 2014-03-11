//
// Drop.cpp for toto in /home/maitre_c/work/linumon/MMO/Common
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Mon Mar 10 14:57:10 2014 antoine maitre
// Last update Mon Mar 10 16:58:10 2014 antoine maitre
//

#include			"Entities/Drop.hh"

Drop::Drop()
  : Persistent(), ContainerWrapper<container_type>(), _money(0), _exp(0)
{
  
}

Drop::~Drop()
{
  
}

void				Drop::setMoney(int const money)
{
  this->_money = money;
}

void				Drop::setExp(int const exp)
{
  this->_exp = exp;
}

int				Drop::getMoney() const
{
  return (this->_money);
}

int				Drop::getExp() const
{
  return (this->_exp);
}
