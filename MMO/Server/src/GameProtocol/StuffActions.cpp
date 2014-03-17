//
// StuffActions.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Sat Feb  8 16:36:22 2014 laurent ansel
// Last update Sun Mar 16 11:30:52 2014 laurent ansel
//

#include			<functional>
#include			<map>
#include			"GameProtocol/StuffActions.hh"
#include			"Server/Server.hh"
#include			"Utility/CommonDefine.hh"

StuffActions::StuffActions()
{
  std::function<bool (Trame *)> func;

  func = std::bind1st(std::mem_fun(&StuffActions::getStuff), this);
  Server::getInstance()->addFuncProtocol("GETSTUFF", func);

  func = std::bind1st(std::mem_fun(&StuffActions::putStuff), this);
  Server::getInstance()->addFuncProtocol("PUTSTUFF", func);
}

StuffActions::~StuffActions()
{
}

// bool				StuffActions::stuffAction(Trame *trame)
// {
//   bool				ret = false;
//   static std::map<eStuffAction, std::function<bool (Trame *)> > map =
//     {
//       {eStuffAction::GET,	std::bind1st(std::mem_fun(&StuffActions::getStuff), this)},
//       {eStuffAction::PUT,	std::bind1st(std::mem_fun(&StuffActions::putStuff), this)}
//     };
//   eStuffAction			type = NONE;

//   if ((*trame)[CONTENT].isMember("STUFF"))
//     {
//       type = static_cast<eStuffAction>((*trame)[CONTENT]["STUFF"]["ACTION"].asInt());
//       ret = map[type](trame);
//     }
//   return (ret);
// }

bool				StuffActions::getStuff(Trame *trame)
{
  bool				ret = false;
  Error				*error = NULL;

  ret = ClientManager::getInstance()->stuff((*trame)[HEADER]["IDCLIENT"].asInt(), true, (*trame)[CONTENT]["GETSTUFF"]["IDITEM"].asUInt(), (*trame)[CONTENT]["GETSTUFF"]["TARGET"].asUInt());
  if (!ret)
    {
      if (ObjectPoolManager::getInstance()->setObject(error, "error"))
	{
	  error->setType(Error::NOITEM);
	  Server::getInstance()->callProtocol<Error *>("ERROR", (*trame)[HEADER]["IDCLIENT"].asInt(), error);
	  delete error;
	}
    }
  return (ret);
}

bool				StuffActions::putStuff(Trame *trame)
{
  bool				ret = false;
  Error				*error = NULL;

  ret = ClientManager::getInstance()->stuff((*trame)[HEADER]["IDCLIENT"].asInt(), false, (*trame)[CONTENT]["PUTSTUFF"]["IDSTACK"].asUInt(), (*trame)[CONTENT]["PUTSTUFF"]["TARGET"].asUInt());
  if (!ret)
    {
      if (ObjectPoolManager::getInstance()->setObject(error, "error"))
	{
	  error->setType(Error::NOTEQUIPPABLE);
	  Server::getInstance()->callProtocol<Error *>("ERROR", (*trame)[HEADER]["IDCLIENT"].asInt(), error);
	  delete error;
	}
    }
  return (ret);
}
