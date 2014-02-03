//
// Client.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Jan 24 13:19:55 2014 guillaume marescaux
// Last update Mon Feb  3 14:28:40 2014 guillaume marescaux
//

#include			"Client.hh"

//-----------------------------------BEGIN CTOR / DTOR-----------------------------------------

Client::Client():
  _state(new MutexVar<eState>(LOGIN)),
  _player(new MutexVar<Player *>(NULL)),
  _players(new MutexVar<Players *>(NULL)),
  _core(new Core(_state, _player, _players)),
  _manager(NULL)
{
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
  _manager = new WindowManager(ac, av, _state);
  _manager->exec();
  _core->quit();
}

void				Client::connection(Protocol::LoginInfos *infos)
{
  _core->connection(infos);
}

void				Client::choosePlayer(int id)
{
  _core->choosePlayer(id);
}
