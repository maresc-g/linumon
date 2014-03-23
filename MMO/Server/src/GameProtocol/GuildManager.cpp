//
// GuildManager.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Mar 13 15:42:01 2014 laurent ansel
// Last update Sun Mar 23 13:33:19 2014 guillaume marescaux
//

#include			<functional>
#include			"GameProtocol/GuildManager.hh"
#include			"Server/Server.hh"
#include			"Entities/Guild.hh"

GuildManager::GuildManager()
{
  std::function<bool (Trame *)> func;

  func = std::bind1st(std::mem_fun(&GuildManager::gCreate), this);
  Server::getInstance()->addFuncProtocol("GCREATE", func);

  func = std::bind1st(std::mem_fun(&GuildManager::invite), this);
  Server::getInstance()->addFuncProtocol("INVITE", func);

  func = std::bind1st(std::mem_fun(&GuildManager::accept), this);
  Server::getInstance()->addFuncProtocol("GACCEPT", func);

  func = std::bind1st(std::mem_fun(&GuildManager::refuse), this);
  Server::getInstance()->addFuncProtocol("GREFUSE", func);

  func = std::bind1st(std::mem_fun(&GuildManager::gQuit), this);
  Server::getInstance()->addFuncProtocol("GQUIT", func);
}

GuildManager::~GuildManager()
{

}

bool				GuildManager::gCreate(Trame *trame)
{
  Guild				*guild;
  Error				*error = NULL;

  if ((*trame)[CONTENT].isMember("GCREATE"))
    {
      guild = Guild::createAndPersist((*trame)[CONTENT]["GCREATE"].asString());
      if (guild)
	ClientManager::getInstance()->newGuild((*trame)[HEADER]["IDCLIENT"].asInt(), guild);
      else
	{
	  if (ObjectPoolManager::getInstance()->setObject(error, "error"))
	    {
	      error->setType(Error::GUILDEXIST);
	      Server::getInstance()->callProtocol<Error *>("ERROR", (*trame)[HEADER]["IDCLIENT"].asInt(), error);
	      delete error;
	    }
	  return (false);
	}
      return (true);
    }
  return (false);
}

bool				GuildManager::gQuit(Trame *trame)
{
  if ((*trame)[CONTENT].isMember("GQUIT"))
    {
      ClientManager::getInstance()->newGuild((*trame)[HEADER]["IDCLIENT"].asInt(), NULL);
      return (true);
    }
  return (false);
}

bool				GuildManager::invite(Trame *trame)
{
  Error				*error = NULL;
  Guild				*guild;

  if ((*trame)[CONTENT].isMember("INVITE"))
    {
      guild = Guild::getGuild((*trame)[CONTENT]["INVITE"]["GUILD"].asString());
      if (guild && !guild->inGuild((*trame)[CONTENT]["INVITE"]["PLAYER"].asString()))
	{
	  ClientManager::getInstance()->inviteInGuild((*trame)[CONTENT]["INVITE"]["PLAYER"].asString(), (*trame)[CONTENT]["INVITE"]["GUILD"].asString());
	  //	  ClientManager::getInstance()->newGuild((*trame)[CONTENT]["INVITE"]["PLAYER"].asString(), guild);
	  return (true);
	}
      else if (ObjectPoolManager::getInstance()->setObject(error, "error"))
	{
	  error->setType(Error::ALREADYINGUILD);
	  Server::getInstance()->callProtocol<Error *>("ERROR", (*trame)[HEADER]["IDCLIENT"].asInt(), error);
	  delete error;
	}
    }
  return (false);
}

bool				GuildManager::refuse(Trame *)
{
  return (true);
}

bool				GuildManager::accept(Trame *trame)
{
  Guild				*guild;
  bool				ret = false;

  if ((*trame)[CONTENT].isMember("GACCEPT"))
    {
      guild = Guild::getGuild((*trame)[CONTENT]["GACCEPT"].asString());
      if (guild)
	ClientManager::getInstance()->newGuild((*trame)[HEADER]["IDCLIENT"].asInt(), guild);
    }
  return (ret);
}

