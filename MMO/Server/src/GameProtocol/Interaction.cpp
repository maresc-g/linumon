//
// Interaction.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Sat Feb  8 17:34:41 2014 laurent ansel
// Last update Sat Feb  8 17:57:35 2014 laurent ansel
//

#include			<functional>
#include			"GameProtocol/Interaction.hh"
#include			"Server/Server.hh"

Interaction::Interaction()
{
  std::function<bool (Trame *)> func;

  func = std::bind1st(std::mem_fun(&Interaction::interaction), this);
  Server::getInstance()->addFuncProtocol("INTERACTION", func);
}

Interaction::~Interaction()
{

}

bool				Interaction::interaction(Trame *trame)
{
  bool				ret = false;
  static std::map<Interaction::eInteraction, std::function<bool (Trame *)> > map =
    {
      {Interaction::eInteraction::AGRO,		std::bind1st(std::mem_fun(&Interaction::agro), this)},
      {Interaction::eInteraction::TRADE,	std::bind1st(std::mem_fun(&Interaction::trade), this)}
    };
  eInteraction			type = NONE;

  if ((*trame)[CONTENT].isMember("INTERACTION"))
    {
      type = static_cast<Interaction::eInteraction>((*trame)[CONTENT]["INTERACTION"]["TYPE"].asInt());
      ret = map[type](trame);
    }
  return (ret);
}


bool				Interaction::agro(Trame *)
{

  return (false);
}

bool				Interaction::trade(Trame *)
{

  return (false);
}
