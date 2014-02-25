//
// Client.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Jan 24 13:19:55 2014 guillaume marescaux
// Last update Tue Feb 25 15:10:13 2014 guillaume marescaux
//

#include			"Client.hh"

//-----------------------------------BEGIN CTOR / DTOR-----------------------------------------

Client::Client():
  _state(new MutexVar<CLIENT::eState>(CLIENT::LOGIN)),
  _player(new MutexVar<Player *>(NULL)),
  _players(new MutexVar<std::list<PlayerView *> *>(new std::list<PlayerView *>)),
  _chat(new MutexVar<Chat *>(new Chat)),
  _newPlayer(new MutexVar<bool>(false)),
  _core(new Core(_state, _player, _players, _chat, _newPlayer)),
  _manager(NULL)
{
}


Client::~Client()
{
  delete _state;
  delete _core;
}

//------------------------------------END CTOR / DTOR------------------------------------------

//-------------------------------------BEGIN METHODS-------------------------------------------

void				Client::init(int ac, char **av)
{
  _core->init();
  _manager = new WindowManager(ac, av, _state, _players, _player, _newPlayer);
  _manager->exec();
  _core->quit();
}

void				Client::connection(std::string const &pseudo, std::string const &pass)
{ _core->connection(pseudo, pass); }

void				Client::choosePlayer(PlayerView const &player) { _core->choosePlayer(player); }

void				Client::create(std::string const &name, std::string const &faction)
{ _core->createPlayer(name, faction); }

bool				Client::move(CLIENT::eDirection dir) { return (_core->move(dir)); }

void				Client::sendChat(std::string const &msg) { _core->sendChat(msg); }
MutexVar<Chat *>		*Client::getChat() {return _chat;}

void				Client::spell(unsigned int idBattle, Spell const &spell, unsigned int target)
{ _core->spell(idBattle, spell, target); }

void				Client::capture(unsigned int idBattle, unsigned int target) { _core->capture(idBattle, target); }

void				Client::sendSwitch(unsigned int idBattle, unsigned int target, unsigned int newMob)
{ _core->sendSwitch(idBattle, target, newMob); }

// void				Client::stuff();

// void				Client::talents();

// void				Client::craft();

// void				Client::gather();

void				Client::useObject(unsigned int target, AItem const &item) { _core->useObject(target, item); }

// void				Client::unsigned interaction();

void				Client::putItem(AItem const &item) { _core->putItem(item); }

void				Client::getItem(AItem const &item) { _core->getItem(item); }

void				Client::sendMoney(unsigned int money) { _core->sendMoney(money); }

void				Client::accept(void) { _core->accept(); }

void				Client::refuse(void) { _core->refuse(); }

void				Client::heal(void) { _core->heal(); }

void				Client::disconnect(void) { _core->disconnect(); }

void				Client::switchPlayer(void) { _core->switchPlayer(); }

//--------------------------------------END METHODS--------------------------------------------
