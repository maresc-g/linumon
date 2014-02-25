//
// otherCommand.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Sat Feb  8 17:46:12 2014 laurent ansel
// Last update Tue Feb 25 10:53:40 2014 laurent ansel
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

bool				OtherCommand::heal(Trame *trame)
{
  if (trame && (*trame)[CONTENT].isMember("HEAL"))
    {
      return (true);
    }
  return (false);
}
