//
// Client.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Jan 24 13:19:55 2014 guillaume marescaux
// Last update Sat Mar 15 19:02:28 2014 guillaume marescaux
//

#include			"Client.hh"

//-----------------------------------BEGIN CTOR / DTOR-----------------------------------------

Client::Client():
  _state(new MutexVar<CLIENT::eState>(CLIENT::LOGIN)),
  _player(new MutexVar<Player *>(NULL)),
  _players(new MutexVar<std::list<PlayerView *> *>(new std::list<PlayerView *>)),
  _chat(new MutexVar<Chat *>(new Chat)),
  _newPlayer(new MutexVar<bool>(false)),
  _battle(new MutexVar<Battle *>(new Battle)),
  _trade(new MutexVar<Trade *>(new Trade)),
  _core(new Core(_state, _player, _players, _chat, _newPlayer, _battle, _trade)),
  _manager(NULL)
{
}


Client::~Client()
{
  delete **_player;
  for (auto it = (**_players)->begin() ; it != (**_players)->end() ; it++)
    delete *it;
  delete **_players;
  delete **_chat;
  delete _state;
  delete _core;
  delete _player;
  delete _players;
  delete _chat;
  delete _battle;
  delete _trade;
  delete _newPlayer;
  delete _manager;
}

//------------------------------------END CTOR / DTOR------------------------------------------

//-------------------------------------BEGIN METHODS-------------------------------------------

void				Client::init(int &ac, char **av)
{
  _core->init();
  _manager = new WindowManager(ac, av, _state, _players, _player, _newPlayer, _battle, _trade);
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

void				Client::spell(unsigned int idBattle, Spell const &spell, unsigned int launcher, unsigned int target)
{ _core->spell(idBattle, spell, launcher, target); }

void				Client::capture(unsigned int idBattle, unsigned int target) { _core->capture(idBattle, target); }

void				Client::sendSwitch(unsigned int idBattle, unsigned int target, unsigned int newMob)
{ _core->sendSwitch(idBattle, target, newMob); }

void				Client::putStuff(unsigned int idItem, unsigned int target)
{ _core->putStuff(idItem, target); }

void				Client::getStuff(unsigned int idItem, unsigned int target)
{ _core->getStuff(idItem, target); }

// void				Client::talents();

void				Client::craft(std::string const &craftName, std::string const &jobName)
{ _core->craft(craftName, jobName); }

// void				Client::gather();

void				Client::useObject(unsigned int target, unsigned int item) { _core->useObject(target, item); }

void				Client::interaction(eInteraction interact, std::string const &name)
{ _core->interaction(interact, name); }

void				Client::putItem(unsigned int idTrade, unsigned int idStack) { _core->putItem(idTrade, idStack); }

void				Client::getItem(unsigned int idTrade, unsigned int idStack) { _core->getItem(idTrade, idStack); }

void				Client::putMob(unsigned int idTrade, unsigned int idMob) { _core->putMob(idTrade, idMob); }

void				Client::getMob(unsigned int idTrade, unsigned int idMob) { _core->getMob(idTrade, idMob); }

void				Client::putMoney(unsigned int idTrade, unsigned int money) { _core->putMoney(idTrade, money); }

void				Client::getMoney(unsigned int idTrade, unsigned int money) { _core->getMoney(idTrade, money); }

void				Client::accept() { _core->accept(); }

void				Client::refuse() { _core->refuse(); }

void				Client::heal(void) { _core->heal(); }

void				Client::disconnect(void) { _core->disconnect(); }

void				Client::switchPlayer(void) { _core->switchPlayer(); }

void				Client::mobtoBattleMob(unsigned int idMob) { _core->mobtoBattleMob(idMob); }

void				Client::battleMobtoMob(unsigned int idMob) { _core->battleMobtoMob(idMob); }

void				Client::switchMobs(unsigned int idMob1, unsigned int idMob2) { _core->switchMobs(idMob1, idMob2); }

void				Client::merge(unsigned int idStack1, unsigned int idStack2) { _core->merge(idStack1, idStack2); }

void				Client::newStack(unsigned int idStack, unsigned int nb) { _core->newStack(idStack, nb); }

//--------------------------------------END METHODS--------------------------------------------
