//
// JobManager.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Sat Feb  8 17:26:56 2014 laurent ansel
// Last update Mon Mar 10 11:53:28 2014 laurent ansel
//

#include			<functional>
#include			"GameProtocol/JobManager.hh"
#include			"Server/Server.hh"

JobManager::JobManager()
{
  std::function<bool (Trame *)> func;

  func = std::bind1st(std::mem_fun(&JobManager::craft), this);
  Server::getInstance()->addFuncProtocol("CRAFT", func);

  func = std::bind1st(std::mem_fun(&JobManager::gather), this);
  Server::getInstance()->addFuncProtocol("GATHER", func);
}

JobManager::~JobManager()
{

}

bool				JobManager::gather(Trame *trame)
{
  bool				ret = false;
  Ressource::RessourceCoordinate	*coord;

  if (trame && (*trame)[CONTENT].isMember("GATHER"))
    {
      coord = Ressource::RessourceCoordinate::deserialization((*trame)((*trame)[CONTENT]["GATHER"]));
      if (coord)
	{
	  ret = ClientManager::getInstance()->gatherSomething((*trame)[HEADER]["IDCLIENT"].asInt(), (*trame)[CONTENT]["GATHER"]["JOBNAME"].asString(), (*trame)[CONTENT]["GATHER"]["GATHERNAME"].asString(), *coord);
	  delete coord;
	}
    }
  return (ret);
}

bool				JobManager::craft(Trame *trame)
{
  bool				ret = false;

  if (trame && (*trame)[CONTENT].isMember("CRAFT"))
    ret = ClientManager::getInstance()->craftSomething((*trame)[HEADER]["IDCLIENT"].asInt(), (*trame)[CONTENT]["CRAFT"]["JOBNAME"].asString(), (*trame)[CONTENT]["CRAFT"]["CRAFTNAME"].asString());
  return (ret);
}
