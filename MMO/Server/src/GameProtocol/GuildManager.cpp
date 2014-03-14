//
// GuildManager.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Mar 13 15:42:01 2014 laurent ansel
// Last update Thu Mar 13 20:25:13 2014 laurent ansel
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
  Server::getInstance()->addFuncProtocol("ACCEPT", func);

  func = std::bind1st(std::mem_fun(&GuildManager::refuse), this);
  Server::getInstance()->addFuncProtocol("REFUSE", func);

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
  bool				ret = false;

  if ((*trame)[CONTENT].isMember("GCREATE"))
    {
      ret = ClientManager::getInstance()->inGuild((*trame)[HEADER]["IDCLIENT"].asInt());
      if (ret && ObjectPoolManager::getInstance()->setObject(error, "error"))
	{
	  error->setType(Error::ALREADYINGUILD);
	  Server::getInstance()->callProtocol<Error *>("ERROR", (*trame)[HEADER]["IDCLIENT"].asInt(), error);
	  delete error;
	}
      return (true);
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

  if ((*trame)[CONTENT].isMember("ACCEPT"))
    {
      guild = Guild::getGuild((*trame)[CONTENT]["ACCEPT"].asString());
      if (guild)
	ClientManager::getInstance()->newGuild((*trame)[HEADER]["IDCLIENT"].asInt(), guild);
    }
  return (ret);
}

