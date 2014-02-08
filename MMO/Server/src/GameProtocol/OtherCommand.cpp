//
// otherCommand.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Sat Feb  8 17:46:12 2014 laurent ansel
// Last update Sat Feb  8 17:47:32 2014 laurent ansel
//

#include			<functional>
#include			"GameProtocol/OtherCommand.hh"
#include			"Server/Server.hh"

OtherCommand::OtherCommand()
{
  std::function<bool (Trame *)> func;

  func = std::bind1st(std::mem_fun(&OtherCommand::heal), this);
  Server::getInstance()->addFuncProtocol("HEAL", func);
}

OtherCommand::~OtherCommand()
{

}

bool				OtherCommand::heal(Trame *)
{

  return (false);
}
