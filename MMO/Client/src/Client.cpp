//
// Client.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Jan 24 13:19:55 2014 guillaume marescaux
// Last update Fri Jan 24 14:09:48 2014 guillaume marescaux
//

#include		"Client.hh"

//-----------------------------------BEGIN CTOR / DTOR-----------------------------------------

Client::Client():
  _state(new MutexVar<eState>(NONE))
{

}


Client::~Client()
{
  delete _state;
}

//------------------------------------END CTOR / DTOR------------------------------------------
