//
// Client.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Jan 24 13:19:55 2014 guillaume marescaux
// Last update Tue Feb  4 15:35:46 2014 guillaume marescaux
//

#include			"Client.hh"

//-----------------------------------BEGIN CTOR / DTOR-----------------------------------------

Client::Client():
  _state(new MutexVar<eState>(LOGIN)),
  _player(new MutexVar<Player *>(NULL)),
  _players(new MutexVar<std::list<PlayerView *> *>(new std::list<PlayerView *>)),
  _core(new Core(_state, _player, _players)),
  _manager(NULL)
{
  PlayerView			*pv = new PlayerView;

  pv->persistentId = 0;
  pv->name = "toto";
  pv->level = 10;
  pv->userId = 0;
  (**_players)->push_back(pv);
}


Client::~Client()
{
  delete _state;
  delete _core;
}

//------------------------------------END CTOR / DTOR------------------------------------------

void				Client::init(int ac, char **av)
{
  _core->init();
  _manager = new WindowManager(ac, av, _state, _players);
  _manager->exec();
  _core->quit();
}

void				Client::connection(std::string const &pseudo, std::string const &pass)
{
  _core->connection(pseudo, pass);
}

void				Client::choosePlayer(PlayerView const &player)
{
  _core->choosePlayer(player);
}

void				Client::create(std::string const &name, std::string const &faction)
{
  _core->createPlayer(name, faction);
}
