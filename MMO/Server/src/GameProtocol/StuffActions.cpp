//
// StuffActions.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Sat Feb  8 16:36:22 2014 laurent ansel
// Last update Sat Feb 15 21:13:33 2014 laurent ansel
//

#include			<functional>
#include			<map>
#include			"GameProtocol/StuffActions.hh"
#include			"Server/Server.hh"

StuffActions::StuffActions()
{
  std::function<bool (Trame *)> func;

  func = std::bind1st(std::mem_fun(&StuffActions::stuffAction), this);
  Server::getInstance()->addFuncProtocol("STUFF", func);
}

StuffActions::~StuffActions()
{
}

bool				StuffActions::stuffAction(Trame *trame)
{
  bool				ret = false;
  static std::map<StuffActions::eAction, std::function<bool (Trame *)> > map =
    {
      {StuffActions::eAction::GET,	std::bind1st(std::mem_fun(&StuffActions::getStuff), this)},
      {StuffActions::eAction::PUT,	std::bind1st(std::mem_fun(&StuffActions::putStuff), this)}
    };
  eAction			type = NONE;

  if ((*trame)[CONTENT].isMember("STUFF"))
    {
      type = static_cast<StuffActions::eAction>((*trame)[CONTENT]["STUFF"]["ACTION"].asInt());
      ret = map[type](trame);
    }
  return (ret);
}

bool				StuffActions::getStuff(Trame *trame)
{
  bool				ret = false;

  ret = ClientManager::getInstance()->stuff((*trame)[HEADER]["IDCLIENT"].asInt(), false, (*trame)[CONTENT]["STUFF"]["IDITEM"].asUInt(), (*trame)[CONTENT]["STUFF"]["TARGET"].asUInt());
  if (!ret)
    ;//ERROR
  return (ret);
}

bool				StuffActions::putStuff(Trame *trame)
{
  bool				ret = false;

  ret = ClientManager::getInstance()->stuff((*trame)[HEADER]["IDCLIENT"].asInt(), true, (*trame)[CONTENT]["STUFF"]["IDITEM"].asUInt(), (*trame)[CONTENT]["STUFF"]["TARGET"].asUInt());
  if (!ret)
    ;//ERROR
  return (ret);
}
