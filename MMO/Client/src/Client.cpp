//
// Client.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Jan 24 13:19:55 2014 guillaume marescaux
// Last update Fri Jan 31 11:01:31 2014 guillaume marescaux
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
  _manager = new WindowManager(ac, av);
  _manager->exec();
  _core->quit();
}

void				Client::connection(LoginInfos *infos)
{
  _core->connection(infos);
}
