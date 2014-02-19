//
// Chat.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Thu Feb  6 12:59:30 2014 guillaume marescaux
// Last update Wed Feb 19 15:00:12 2014 cyril jourdain
//

#include <iostream>
#include			"Chat/Chat.hh"

//-----------------------------------BEGIN CTOR / DTOR-----------------------------------------

Chat::Chat():
  _msgs(new std::list<std::string>), _newMessage(false)
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
  std::cout << "MSG TO ADD = " << msg << std::endl;
  _msgs->push_back(msg);
}

std::list<std::string> const	&Chat::getMsgs(void) const
{
  return (*_msgs);
}

bool				Chat::getNewMessage() const
{
  return _newMessage;
}

void				Chat::setNewMessage(bool n)
{
  _newMessage = n;
}

//--------------------------------------END METHODS--------------------------------------------
