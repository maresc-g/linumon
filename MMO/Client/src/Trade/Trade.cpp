//
// Trade.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Tue Mar 11 14:16:44 2014 guillaume marescaux
// Last update Sun Mar 16 14:22:26 2014 guillaume marescaux
//

#include				"Trade/Trade.hh"

Trade::Trade():
  _id(0), _name(""),
  _playerStacks(new std::list<Stack<AItem> const *>), _otherStacks(new std::list<Stack<AItem> const *>),
  _playerMobs(new std::list<Mob const *>), _otherMobs(new std::list<Mob const *>),
  _playerMoney(0), _otherMoney(0),
  _playerResponse(NONE), _otherResponse(NONE),
  _end(false), _changed(false)
{
}

Trade::~Trade()
{
  delete _playerStacks;
  delete _otherStacks;
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
void				Trade::putPlayerStack(Stack<AItem> const *item) { _playerStacks->push_back(item); }
void				Trade::putOtherStack(Stack<AItem> const *item) { _otherStacks->push_back(item); }
void				Trade::getPlayerStack(Stack<AItem> const *item) { _playerStacks->remove(item); }
void				Trade::getOtherStack(Stack<AItem> const *item) { _otherStacks->remove(item); }
void				Trade::setName(std::string const &name) { _name = name; }
void				Trade::setPlayerResponse(eResponse response) { _playerResponse = response; }
void				Trade::setOtherResponse(eResponse response) { _otherResponse = response; }
void				Trade::setEnd(bool end) { _end = end; }
void				Trade::setChanged(bool changed) { _changed = changed; }

unsigned int			Trade::getPlayerMoney(void) const { return (_playerMoney); }
unsigned int			Trade::getOtherMoney(void) const { return (_otherMoney); }
std::list<Stack<AItem> const *> const	&Trade::getPlayerStacks(void) const { return (*_playerStacks); }
std::list<Stack<AItem> const *> const	&Trade::getOtherStacks(void) const { return (*_otherStacks); }
std::list<Mob const*> const	&Trade::getPlayerMobs(void) const { return (*_playerMobs); }
std::list<Mob const*> const	&Trade::getOtherMobs(void) const { return (*_otherMobs); }
std::string const		&Trade::getName(void) const { return (_name); }
unsigned int			Trade::getId(void) const { return (_id); }
Trade::eResponse		Trade::getPlayerResponse(void) const { return (_playerResponse); }
Trade::eResponse		Trade::getOtherResponse(void) const { return (_otherResponse); }
bool				Trade::getEnd(void) const { return (_end); }
bool				Trade::getChanged(void) const { return (_changed); }

void				Trade::reset(unsigned int id, std::string const &name)
{
  _id = id;
  _name = name;
  _playerStacks->clear();
  _otherStacks->clear();
  _playerMobs->clear();
  _otherMobs->clear();
  _playerMoney = 0;
  _otherMoney = 0;
  _playerResponse = Trade::NONE;
  _otherResponse = Trade::NONE;
  _end = false;
  _changed = false;
}

void				Trade::handleEnd(MutexVar<Player *> *player)
{
  if (_otherResponse == Trade::ACCEPT && _playerResponse == Trade::ACCEPT)
    {
      for (auto it = _otherStacks->begin() ; it != _otherStacks->end() ; ++it)
	(**player)->addItem(new Stack<AItem>(**it));
      for (auto it = _otherMobs->begin() ; it != _otherMobs->end() ; ++it)
	(**player)->addMob(new Mob(**it));
      (**player)->addMoney(_otherMoney);
      (**player)->addMoney(-_playerMoney);
    }
  else if (_otherResponse == Trade::REFUSE || _playerResponse == Trade::REFUSE)
    {
      for (auto it = _playerStacks->begin() ; it != _playerStacks->end() ; ++it)
	(**player)->addItem(new Stack<AItem>(**it));
      for (auto it = _playerMobs->begin() ; it != _playerMobs->end() ; ++it)
	(**player)->addMob(new Mob(**it));
    }
}
