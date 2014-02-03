//
// Client.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Jan 24 13:19:55 2014 guillaume marescaux
// Last update Mon Feb  3 12:42:45 2014 cyril jourdain
//

#include			"Client.hh"

//-----------------------------------BEGIN CTOR / DTOR-----------------------------------------

Client::Client():
  _state(new MutexVar<eState>(NONE)),
  _core(new Core(_state)),
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
