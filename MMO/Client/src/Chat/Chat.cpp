//
// Chat.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Thu Feb  6 12:59:30 2014 guillaume marescaux
// Last update Thu Feb  6 13:03:06 2014 guillaume marescaux
//

#include			"Chat/Chat.hh"

//-----------------------------------BEGIN CTOR / DTOR-----------------------------------------

Chat::Chat():
  _msgs(new std::list<std::string>)
{
}

Chat::~Chat()
{
  delete _msgs;
}

//------------------------------------END CTOR / DTOR------------------------------------------

//-------------------------------------BEGIN METHODS-------------------------------------------

void				Chat::addMsg(std::string const &msg)
{
  _msgs->push_back(msg);
}

std::list<std::string> const	&Chat::getMsgs(void) const
{
  return (*_msgs);
}

//--------------------------------------END METHODS--------------------------------------------
