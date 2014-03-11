//
// Trade.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Tue Mar 11 14:16:44 2014 guillaume marescaux
// Last update Tue Mar 11 15:15:15 2014 guillaume marescaux
//

#include				"Trade/Trade.hh"

Trade::Trade():
  _id(0), _name(""),
  _playerItems(new std::list<AItem const *>), _otherItems(new std::list<AItem const *>),
  _playerMobs(new std::list<Mob const *>), _otherMobs(new std::list<Mob const *>),
  _playerMoney(0), _otherMoney(0),
  _changed(false)
{
}

Trade::~Trade()
{
  delete _playerItems;
  delete _otherItems;
  delete _playerMobs;
  delete _otherMobs;
}

void				Trade::putPlayerMoney(unsigned int money) { _playerMoney += money;}
void				Trade::putOtherMoney(unsigned int money) { _otherMoney += money; }
void				Trade::getPlayerMoney(unsigned int money) { _playerMoney -= money; }
void				Trade::getOtherMoney(unsigned int money) { _otherMoney -= money; }
void				Trade::putPlayerMob(Mob const *mob) { _playerMobs->push_back(mob); }
void				Trade::putOtherMob(Mob const *mob) { _otherMobs->push_back(mob); }
void				Trade::getPlayerMob(Mob const *mob) { _playerMobs->remove(mob); }
void				Trade::getOtherMob(Mob const *mob) { _otherMobs->remove(mob); }
void				Trade::putPlayerItem(AItem const *item) { _playerItems->push_back(item); }
void				Trade::putOtherItem(AItem const *item) { _otherItems->push_back(item); }
void				Trade::getPlayerItem(AItem const *item) { _playerItems->remove(item); }
void				Trade::getOtherItem(AItem const *item) { _otherItems->remove(item); }
void				Trade::setName(std::string const &name) { _name = name; }
void				Trade::setChanged(bool changed) { _changed = changed; }

unsigned int			Trade::getPlayerMoney(void) const { return (_playerMoney); }
unsigned int			Trade::getOtherMoney(void) const { return (_otherMoney); }
std::list<AItem const*> const	&Trade::getPlayerItems(void) const { return (*_playerItems); }
std::list<AItem const*> const	&Trade::getOtherItems(void) const { return (*_otherItems); }
std::list<Mob const*> const	&Trade::getPlayerMobs(void) const { return (*_playerMobs); }
std::list<Mob const*> const	&Trade::getOtherMobs(void) const { return (*_otherMobs); }
std::string const		&Trade::getName(void) const { return (_name); }
bool				Trade::getChanged(void) const { return (_changed); }

void				Trade::reset(unsigned int id, std::string const &name)
{
  _id = id;
  _name = name;
  _playerItems->clear();
  _otherItems->clear();
  _playerMobs->clear();
  _otherMobs->clear();
  _changed = false;
}
