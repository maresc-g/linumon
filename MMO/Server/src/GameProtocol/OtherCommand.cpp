//
// otherCommand.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Sat Feb  8 17:46:12 2014 laurent ansel
// Last update Fri Mar 21 15:24:00 2014 antoine maitre
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
  std::cout << "JE PASSE DANS LE HEAL COTE SERVER " << std::endl;
  if (trame && (*trame)[CONTENT].isMember("HEAL"))
    {
      std::cout << "BEREFORE CALL PROTOCOL" << std::endl;
      Server::getInstance()->callProtocol("HEAL", (*trame)[HEADER]["IDCLIENT"].asUInt());
      std::cout << "after CALL PROTOCOL" << std::endl;      
      return (true);
    }
  return (false);
}
