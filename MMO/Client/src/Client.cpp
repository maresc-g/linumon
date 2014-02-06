//
// Client.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Jan 24 13:19:55 2014 guillaume marescaux
// Last update Thu Feb  6 13:35:21 2014 cyril jourdain
//

#include			"Client.hh"

//-----------------------------------BEGIN CTOR / DTOR-----------------------------------------

Client::Client():
  _state(new MutexVar<CLIENT::eState>(CLIENT::LOGIN)),
  _player(new MutexVar<Player *>(NULL)),
  _players(new MutexVar<std::list<PlayerView *> *>(new std::list<PlayerView *>)),
  _chat(new MutexVar<Chat *>(new Chat)),
  _core(new Core(_state, _player, _players, _chat)),
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
  _manager = new WindowManager(ac, av, _state, _players, _player);
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

void				Client::move(CLIENT::eDirection dir)
{
  _core->move(dir);
}

void				Client::sendChat(std::string const &msg)
{
  _core->sendChat(msg);
}

//--------------------------------------END METHODS--------------------------------------------
