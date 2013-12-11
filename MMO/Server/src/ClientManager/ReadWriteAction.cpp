//
// ReadWriteAction.cpp for  in /home/ansel_l/Documents/Pfa/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Dec  5 16:46:14 2013 laurent ansel
// Last update Thu Dec  5 17:02:15 2013 laurent ansel
//

#include			"ClientManager/ReadWriteAction.hh"

ReadWriteAction::ReadWriteAction(std::string const &proto, enum ReadWriteAction::eAction const type):
  _use(true),
  _protocole(proto),
  _action(type)
{

}

ReadWriteAction::~ReadWriteAction()
{

}

std::string const		&ReadWriteAction::getProtocole() const
{
  return (this->_protocole);
}

enum ReadWriteAction::eAction	ReadWriteAction::getAction() const
{
  return (this->_action);
}

bool				ReadWriteAction::isUse() const
{
  return (this->_use);
}

void				ReadWriteAction::setProtocole(std::string const &protocole)
{
  this->_protocole = protocole;
}

void				ReadWriteAction::setAction(enum ReadWriteAction::eAction const type)
{
  this->_action = type;
}

void				ReadWriteAction::clear()
{
  this->_use = false;
}

void				ReadWriteAction::use()
{
  this->_use = true;
}
