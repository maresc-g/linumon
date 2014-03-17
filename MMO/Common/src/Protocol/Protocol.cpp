//
// Protocol.cpp for  in /home/ansel_l/Documents/Pfa/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Jan 24 10:57:48 2014 laurent ansel
// Last update Fri Mar 14 16:24:55 2014 antoine maitre
//

#include		"Protocol/Protocol.hpp"
#include		"Error/Error.hpp"
#include		"Entities/User.hh"
#include		"Loader/LoaderManager.hh"
#include		"Entities/Guild.hh"
#ifndef	CLIENT_COMPILATION
#include		"ClientWriter/ClientWriter.hh"
#endif

Protocol::Protocol(bool const server):
  //  _container(new std::map<std::string, funcProtocol>),
  _container(new FunctorContainer<std::string, bool>),
  _decode(new std::map<std::string, funcDecode>),
  _server(server)
{
  ObjectPoolManager::getInstance()->runObjectPool<Trame>("trame");
  ObjectPoolManager::getInstance()->runObjectPool<Header>("header");
  ObjectPoolManager::getInstance()->runObjectPool<Coordinate<int>>("coordinateint");
  ObjectPoolManager::getInstance()->runObjectPool<Coordinate<double>>("coordinatedouble");

  if (server)
    {
      this->_container->load<unsigned int>("WELCOME", &welcome);
      this->_container->load<unsigned int>("CHECK", &check);
      this->_container->load<unsigned int, Error *>("ERROR", &error);
      this->_container->load<unsigned int, User *>("PLAYERLIST", &playerlist);
      this->_container->load<unsigned int, Player *>("PLAYER", &player);
      this->_container->load<unsigned int, Player *, Zone *>("NEWPLAYER", &newPlayer);
      this->_container->load<unsigned int, Zone *>("MAP", &map);
      this->_container->load<unsigned int, Trame *, Zone *, bool>("SENDTOALLCLIENT", &sendToAllClient);
      this->_container->load<unsigned int, Trame *>("ALREADYREADY", &sendTrameAlreadyReady);
      this->_container->load<unsigned int, unsigned int, Stats const *>("OBJECTEFFECT", &objectEffect);
      this->_container->load<unsigned int, ACharacter const *>("UPDATECHARACTER", &updateCharacter);

      this->_container->load<unsigned int, unsigned int, std::string>("LAUNCHTRADE", &launchTrade);
      this->_container->load<unsigned int, unsigned int, AItem const *>("PUTITEM", &putItem);
      this->_container->load<unsigned int, unsigned int, AItem const *>("GETITEM", &getItem);
      this->_container->load<unsigned int, unsigned int, Mob const *>("PUTMOB", &putMob);
      this->_container->load<unsigned int, unsigned int, Mob const *>("GETMOB", &getMob);
      this->_container->load<unsigned int, unsigned int, unsigned int>("PUTMONEY", &putMoney);
      this->_container->load<unsigned int, unsigned int, unsigned int>("GETMONEY", &getMoney);
      this->_container->load<unsigned int, unsigned int>("ACCEPT", &accept);
      this->_container->load<unsigned int, unsigned int>("REFUSE", &refuse);

      this->_container->load<unsigned int, unsigned int, Player const *, unsigned int>("LAUNCHBATTLE", &launchBattle);
      this->_container->load<unsigned int, unsigned int, Spell const *, unsigned int, unsigned int>("SPELL", &spell);
      this->_container->load<unsigned int, unsigned int, int, unsigned int>("SPELLEFFECT", &spellEffect);
      this->_container->load<unsigned int, unsigned int, bool>("CAPTUREEFFECT", &captureEffect);
      this->_container->load<unsigned int, unsigned int, unsigned int, unsigned int, unsigned int>("SWITCH", &dswitch);
      this->_container->load<unsigned int, unsigned int, unsigned int>("DEADMOB", &deadMob);
      this->_container->load<unsigned int, unsigned int>("TURNTO", &turnTo);
      this->_container->load<unsigned int, unsigned int, bool, unsigned int, unsigned int, std::list<AItem *>*>("ENDBATTLE", &endBattle);
      this->_container->load<unsigned int, int, Player::PlayerCoordinate const *>("ENTITY", &entity);
      this->_container->load<unsigned int, int, Zone *>("REMOVEENTITY", &removeEntity);

      this->_container->load<unsigned int, Stack *>("ADDTOINVENTORY", &addToInventory);
      this->_container->load<unsigned int, std::list<Stack *> *>("DELETEFROMINVENTORY", &deleteFromInventory);
      this->_container->load<unsigned int, Job const *>("JOB", &job);

      this->_container->load<unsigned int, Player *, Zone *, Zone *>("NEWZONE", &newZone);
      this->_container->load<unsigned int, unsigned int, bool, Zone *>("VISIBLE", &visible);

      this->_container->load<unsigned int, unsigned int, bool, Zone *>("ISINBATTLE", &isInBattle);

      this->_container->load<unsigned int>("MOBMODELS", &mobModels);
      this->_container->load<unsigned int>("JOBMODELS", &jobModels);
      this->_container->load<unsigned int>("STUFFS", &stuffs);
      this->_container->load<unsigned int>("CONSUMABLES", &consumables);
      this->_container->load<unsigned int>("TALENTMODELS", &talentModels);
      this->_container->load<unsigned int>("RESSOURCES", &ressources);
      this->_container->load<unsigned int>("HEALS", &heals);
      this->_container->load<unsigned int>("SPELLSLIST", &spells);
      this->_container->load<unsigned int>("AUTHORIZEDSTATKEYSLIST", &authorizedStatKeys);

      this->_container->load<unsigned int, std::string>("NEWGUILD", &newGuild);
      this->_container->load<unsigned int, Guild *>("GUILD", &guild);
      this->_container->load<unsigned int, std::string, Zone *>("NEWMEMBER", &newMember);
      this->_container->load<unsigned int, std::string, Zone *>("DELETEMEMBER", &deleteMember);
      this->_container->load<unsigned int, std::string>("invite", &invite);

    }
  else
    {
      this->_container->load<unsigned int>("INITIALIZE", &initialize);
      this->_container->load<unsigned int, std::string, std::string>("CONNECTION", &connection);
      this->_container->load<unsigned int, Error *>("ERROR", &error);
      this->_container->load<unsigned int, std::string, Faction const *>("CREATE", &create);
      this->_container->load<unsigned int, int>("CHOOSEPLAYER", &choosePlayer);
      this->_container->load<unsigned int, int, Player::PlayerCoordinate const *>("ENTITY", &entity);
      this->_container->load<unsigned int, std::string, std::string>("CHAT", &chat);
      this->_container->load<unsigned int, unsigned int, Spell const *, unsigned int, unsigned int>("SPELL", &spell);
      this->_container->load<unsigned int, unsigned int, unsigned int, unsigned int>("SWITCH", &dswitch);
      this->_container->load<unsigned int, unsigned int, unsigned int>("USEOBJECT", &useObject);
      this->_container->load<unsigned int, unsigned int, unsigned int>("PUTITEM", &putItem);
      this->_container->load<unsigned int, unsigned int, unsigned int>("GETITEM", &getItem);
      this->_container->load<unsigned int, unsigned int, unsigned int>("PUTMOB", &putMob);
      this->_container->load<unsigned int, unsigned int, unsigned int>("GETMOB", &getMob);
      this->_container->load<unsigned int, unsigned int, unsigned int>("PUTMONEY", &putMoney);
      this->_container->load<unsigned int, unsigned int, unsigned int>("GETMONEY", &getMoney);
      this->_container->load<unsigned int, unsigned int>("ACCEPT", &accept);
      this->_container->load<unsigned int, unsigned int>("REFUSE", &refuse);
      this->_container->load<unsigned int, unsigned int>("MOBTOBATTLEMOB", &mobtoBattleMob);
      this->_container->load<unsigned int, unsigned int>("BATTLEMOBTOMOB", &battleMobtoMob);
      this->_container->load<unsigned int, unsigned int, unsigned int>("SWITCHMOBS", &switchMobs);
      this->_container->load<unsigned int, unsigned int, unsigned int>("MERGE", &merge);
      this->_container->load<unsigned int, unsigned int, unsigned int>("NEWSTACK", &newStack);
      this->_container->load<unsigned int, std::string, std::string>("CRAFT", &craft);
      this->_container->load<unsigned int>("HEAL", &heal);
      this->_container->load<unsigned int>("DISCONNECT", &disconnect);
      this->_container->load<unsigned int>("SWITCHPLAYER", &switchPlayer);
      this->_container->load<unsigned int, unsigned int, Spell const *, unsigned int>("SPELL", &spell);
      this->_container->load<unsigned int, int, unsigned int, unsigned int>("STUFF", &stuff);
    }
}

Protocol::~Protocol()
{
  delete _container;
  delete _decode;
}

bool			Protocol::addFunc(std::string const &key, bool (*func)(Trame *))
{
  (*this->_decode)[key] = func;
  return (true);
}

bool			Protocol::addFunc(std::string const &key, std::function<bool (Trame *)> func)
{
  (*this->_decode)[key] = func;
  return (true);
}

bool			welcome(unsigned int const id)
{
  Trame			*trame;
  Header		*header;
  bool			ret = false;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["WELCOME"];
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
    }
  delete header;
  return (ret);
}

bool			error(unsigned int const id, Error *error)
{
  Trame			*trame;
  Header		*header;
  bool			ret = false;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame) && error->serialization(*trame))
    {
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
    }
  delete header;
  return (ret);
}

bool			check(unsigned int const id)
{
  Trame			*trame;
  Header		*header;
  bool			ret = false;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["CHECK"];
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
    }
  delete header;
  return (ret);
}


bool			chat(unsigned int const id, std::string idZone, std::string msg)
{
  Trame			*trame;
  Header		*header;
  bool			ret = false;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["CHAT"]["IDZONE"] = idZone;
      (*trame)[CONTENT]["CHAT"]["MESSAGE"] = msg;
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
    }
  delete header;
  return (ret);
}

bool		         initialize(unsigned int const id)
{
  Trame                 *trame;
  Header                *header;
  bool			ret = false;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("UDP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["INITIALIZE"];
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
    }
  delete header;
  return (ret);
}

bool		         entity(unsigned int const id, int playerId, Player::PlayerCoordinate const *coord)
{
  Trame                 *trame;
  Header                *header;
  bool			ret = false;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("UDP");
  if (header->serialization(*trame) && coord->serialization((*trame)((*trame)[CONTENT]["ENTITY"])))
    {
      (*trame)[CONTENT]["ENTITY"]["ID"] = playerId;
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
    }
  delete header;
  return (ret);
}

bool		         removeEntity(unsigned int const id, int entityId, Zone *zone)
{
  Trame                 *trame;
  Header                *header;
  bool			ret = false;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["REMOVEENTITY"]["ID"] = entityId;
      trame->setEnd(true);
      ret = sendToAllClient(id, trame, zone, false);
    }
  delete header;
  return (ret);
}

bool			newPlayer(unsigned int const id, Player *player, Zone *zone)
{
  Trame			*trame;
  Header		*header;
  bool			ret = false;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["NEWPLAYER"]["PLAYER"]["ID"] = static_cast<int>(player->getId());
      (*trame)[CONTENT]["NEWPLAYER"]["PLAYER"]["NAME"] = player->getName();
      (*trame)[CONTENT]["NEWPLAYER"]["PLAYER"]["TYPE"] = player->getStatEntityType();
      (*trame)[CONTENT]["NEWPLAYER"]["PLAYER"]["ZONE"] = player->getZone();
      player->getCoord().serialization((*trame)((*trame)[CONTENT]["NEWPLAYER"]["PLAYER"]));
      player->getFaction().serialization((*trame)((*trame)[CONTENT]["NEWPLAYER"]["PLAYER"]));
      if (player->getGuild())
	player->getGuild()->serialization((*trame)((*trame)[CONTENT]["NEWPLAYER"]["PLAYER"]));
      trame->setEnd(true);
      ret = sendToAllClient(id, trame, zone, false);
    }
  delete header;
  return (ret);
}

bool			connection(unsigned int const id, std::string pseudo, std::string pass)
{
  Trame			*trame;
  Header		*header;
  bool			ret = false;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["CONNECTION"]["PSEUDO"]= pseudo;
      (*trame)[CONTENT]["CONNECTION"]["PASS"] =pass;
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
    }
  delete header;
  return (ret);
}

bool			create(unsigned int const id, std::string name, Faction const *faction)
{
  Trame                 *trame;
  Header                *header;
  bool			ret = false;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["CREATE"]["NAME"] = name;
      faction->serialization((*trame)((*trame)[CONTENT]["CREATE"]));
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
    }
  delete header;
  return (ret);
}

bool                    newZone(unsigned int const id, Player *player, Zone *oldZone, Zone *zone)
{
  Trame			*trame;
  Header		*header;
  bool			ret = false;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["NEWZONE"]["ZONE"] = player->getZone();
      zone->serialization((*trame));
      player->getCoord().serialization((*trame)((*trame)[CONTENT]["NEWZONE"]));
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
      //      ret = map(id, zone);
      ret = newPlayer(id, player, zone);
      std::cout << "RET = " << ret << std::endl;
      ret = removeEntity(id, player->getId(), oldZone);
      std::cout << "RET = " << ret << std::endl;
    }
  delete header;
  return (ret);
}

bool                    visible(unsigned int const id, unsigned int const idRessource, bool const visible, Zone *zone)
{
  Trame			*trame;
  Header		*header;
  bool			ret = false;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["VISIBLE"]["IS"] = visible;
      (*trame)[CONTENT]["VISIBLE"]["ID"] = idRessource;
      trame->setEnd(true);
      ret = sendToAllClient(id, trame, zone, true);
    }
  delete header;
  return (ret);
}

bool                    choosePlayer(unsigned int const id, int playerId)
{
  Trame			*trame;
  Header		*header;
  bool			ret = false;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["CHOOSEPLAYER"] = playerId;
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
    }
  delete header;
  return (ret);
}

bool                    isInBattle(unsigned int const id, unsigned int const playerId, bool const battle, Zone *zone)
{
  Trame			*trame;
  Header		*header;
  bool			ret = false;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["ISINBATTLE"]["ID"] = playerId;
      (*trame)[CONTENT]["ISINBATTLE"]["IS"] = battle;
      trame->setEnd(true);
      ret = sendToAllClient(id, trame, zone, false);
    }
  delete header;
  return (ret);
}

bool                    playerlist(unsigned int const id, User *user)
{
  Trame                 *trame;
  Header                *header;
  bool			ret = false;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (user && header->serialization(*trame) && user->serialization(*trame))
    {
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
    }
  delete header;
  return (ret);
}

bool                    player(unsigned int const id, Player *player)
{
  Trame                 *trame;
  Header                *header;
  bool			ret = false;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame) && player->serialization((*trame)((*trame)[CONTENT])))
    {
      Player::deserialization(*trame);
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
    }
  delete header;
  return (ret);
}

bool                    map(unsigned int const id, Zone *zone)
{
  Trame                 *trame;
  Header                *header;
  bool			ret = false;

  if (zone)
    {
      ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
      ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
      header->setIdClient(id);
      header->setProtocole("TCP");
      if (header->serialization(*trame) && zone->serialization((*trame)))
	{
	  trame->setEnd(true);
	  CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
	  ret = true;
	}
      delete header;
    }
  return (ret);
}

bool                    objectEffect(unsigned int const id, unsigned int const target, Stats const *stats)
{
  Trame                 *trame;
  Header                *header;
  bool			ret = false;

  if (stats)
    {
      ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
      ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
      header->setIdClient(id);
      header->setProtocole("TCP");
      if (header->serialization(*trame) && stats->serialization((*trame)((*trame)[CONTENT]["STATS"])))
	{
	  (*trame)[CONTENT]["TARGET"] = target;
	  trame->setEnd(true);
	  CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
	  ret = true;
	}
      delete header;
    }
  return (ret);
}

bool                    sendToAllClient(unsigned int const id, Trame *trame, Zone *zone, bool const send)
{
  std::list<AEntity *>	list;
  unsigned int		idClient;
  Trame			*tmp = NULL;
  bool			ret = false;

  if (trame && zone)
    {
      trame->setEnd(true);
      list = zone->getPlayers();
      for (auto ip = list.begin() ; ip != list.end() ; ++ip)
	{
	  if ((*ip))
	    {
	      if ((idClient = static_cast<Player *>(*ip)->getUser().getId()) && (idClient != id || id == 0))
		{
		  ObjectPoolManager::getInstance()->setObject(tmp, "trame");
		  *tmp = *trame;
		  (*tmp)[HEADER]["IDCLIENT"] = idClient;
		  CircularBufferManager::getInstance()->pushTrame(tmp, CircularBufferManager::WRITE_BUFFER);
		  tmp = NULL;
#ifndef CLIENT_COMPILATION
		  if (idClient != id)
		    ClientWriter::getInstance()->addNewTrame(idClient, 1);
#endif
		}
	    }
	  ret = true;
	}
      if (send && id != 0)
	{
	  (*trame)[HEADER]["IDCLIENT"] = id;
	  ObjectPoolManager::getInstance()->setObject(tmp, "trame");
	  *tmp = *trame;
	  CircularBufferManager::getInstance()->pushTrame(tmp, CircularBufferManager::WRITE_BUFFER);
	  ret = true;
	}
      ret = true;
    }
  return (ret);
}

bool			launchBattle(unsigned int const id, unsigned int const idBattle, Player const *player, unsigned int limit)
{
  Trame			*trame;
  Header		*header;
  bool			ret = false;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["LAUNCHBATTLE"]["IDBATTLE"] = idBattle;
      (*trame)[CONTENT]["LAUNCHBATTLE"]["LIMIT"] = limit;
      player->serialization((*trame)((*trame)[CONTENT]["LAUNCHBATTLE"]["ENEMY"]));
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
    }
  delete header;
  return (ret);
}

bool			spell(unsigned int const id,
			      unsigned int const idBattle,
			      Spell const *spell,
			      unsigned int const launcher,
			      unsigned int const target)
{
  Trame			*trame;
  Header		*header;
  bool			ret = false;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["SPELL"]["IDBATTLE"] = idBattle;
      //      spell->serialization((*trame)((*trame)[CONTENT]["SPELL"]["SPELL"]));
      (*trame)[CONTENT]["SPELL"]["NAME"] = spell->getName();
      (*trame)[CONTENT]["SPELL"]["LAUNCHER"] = launcher;
      (*trame)[CONTENT]["SPELL"]["TARGET"] = target;
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
    }
  delete header;
  return (ret);
}

bool			spellEffect(unsigned int const id, 
				    unsigned int const idBattle, 
				    int const hpChange, 
				    unsigned int const target)
{
  Trame			*trame;
  Header		*header;
  bool			ret = false;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["SPELLEFFECT"]["IDBATTLE"] = idBattle;
      (*trame)[CONTENT]["SPELLEFFECT"]["HPCHANGE"] = hpChange;
      (*trame)[CONTENT]["SPELLEFFECT"]["TARGET"] = target;
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
    }
  delete header;
  return (ret);
}

bool			captureEffect(unsigned int const id, unsigned int const idBattle, bool success)
{
  Trame			*trame;
  Header		*header;
  bool			ret = false;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["CAPTUREEFFECT"]["IDBATTLE"] = idBattle;
      (*trame)[CONTENT]["CAPTUREEFFECT"]["SUCCESS"] = success;
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
    }
  delete header;
  return (ret);
}

bool			dswitch(unsigned int const id, 
				unsigned int const idBattle, 
				unsigned int const target, 
				unsigned int const newMob,
				unsigned int const player)
{
  Trame			*trame;
  Header		*header;
  bool			ret = false;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["SWITCH"]["IDBATTLE"] = idBattle;
      (*trame)[CONTENT]["SWITCH"]["TARGET"] = target;
      (*trame)[CONTENT]["SWITCH"]["NEWMOB"] = newMob;
      (*trame)[CONTENT]["SWITCH"]["PLAYER"] = player;
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
    }
  delete header;
  return (ret);
}

bool			deadMob(unsigned int const id, unsigned int const idBattle, unsigned int const idMob)
{
  Trame			*trame;
  Header		*header;
  bool			ret = false;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["DEADMOB"]["IDBATTLE"] = idBattle;
      (*trame)[CONTENT]["DEADMOB"]["ID"] = idMob;
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
    }
  delete header;
  return (ret);
}

bool			turnTo(unsigned int const id, unsigned int const idMob)
{
  Trame			*trame;
  Header		*header;
  bool			ret = false;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      std::cout << "JE SUIS DANS LE PROTOCOL" << std::endl;
      (*trame)[CONTENT]["TURNTO"] = idMob;
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
    }
  delete header;
  return (ret);
}

bool			endBattle(unsigned int const id, 
					    unsigned int const idBattle,
					    bool win, 
					    unsigned int const money, 
					    unsigned int const exp, 
					    std::list<AItem *> *items)
{
  Trame			*trame;
  Header		*header;
  bool			ret = false;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["ENDBATTLE"]["IDBATTLE"] = idBattle;
      (*trame)[CONTENT]["ENDBATTLE"]["WIN"] = win;
      (*trame)[CONTENT]["ENDBATTLE"]["MONEY"] = money;
      (*trame)[CONTENT]["ENDBATTLE"]["EXP"] = exp;
      (void) items;
      // (*trame)[CONTENT]["ENDBATTLE"]["ITEMS"] = std::get<1>(*params);
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
    }
  delete header;
  return (ret);
}

bool			useObject(unsigned int const id, unsigned int target, unsigned int idItem)
{
  bool			ret = false;
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["USEOBJECT"]["TARGET"] = target;
      (*trame)[CONTENT]["USEOBJECT"]["ITEM"] = idItem;
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
    }
  delete header;
  return (ret);
}

bool			launchTrade(unsigned int const id, unsigned int const idTrade, std::string namePlayer)
{
  bool			ret = false;
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["LAUNCHTRADE"]["IDTRADE"] = idTrade;
      (*trame)[CONTENT]["LAUNCHTRADE"]["NAMEPLAYER"] = namePlayer;
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
    }
  delete header;
  return (ret);
}

bool			putItem(unsigned int const id, unsigned int const idTrade, AItem const *item)
{
  bool			ret = false;
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame) && item->serialization((*trame)((*trame)[CONTENT]["PUTITEM"])))
    {
      (*trame)[CONTENT]["PUTITEM"]["IDTRADE"] = idTrade;
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
    }
  delete header;
  return (ret);
}

bool			getItem(unsigned int const id, unsigned int const idTrade, AItem const *item)
{
  bool			ret = false;
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame) && item->serialization((*trame)((*trame)[CONTENT]["GETITEM"])))
    {
      (*trame)[CONTENT]["GETITEM"]["IDTRADE"] = idTrade;
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
    }
  delete header;
  return (ret);
}

bool			putMob(unsigned int const id, unsigned int const idTrade, Mob const *mob)
{
  bool			ret = false;
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame) && mob->serialization((*trame)((*trame)[CONTENT]["PUTMOB"])))
    {
      (*trame)[CONTENT]["PUTMOB"]["IDTRADE"] = idTrade;
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
    }
  delete header;
  return (ret);
}

bool			getMob(unsigned int const id, unsigned int const idTrade, Mob const *mob)
{
  bool			ret = false;
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame) && mob->serialization((*trame)((*trame)[CONTENT]["GETMOB"])))
    {
      (*trame)[CONTENT]["GETMOB"]["IDTRADE"] = idTrade;
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
    }
  delete header;
  return (ret);
}

bool			putItem(unsigned int const id, unsigned int const idTrade, unsigned int const idItem)
{
  bool			ret = false;
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["PUTITEM"]["IDTRADE"] = idTrade;
      (*trame)[CONTENT]["PUTITEM"]["IDITEM"] = idItem;
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
    }
  delete header;
  return (ret);
}

bool			getItem(unsigned int const id, unsigned int const idTrade, unsigned int const idItem)
{
  bool			ret = false;
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["GETITEM"]["IDTRADE"] = idTrade;
      (*trame)[CONTENT]["GETITEM"]["IDITEM"] = idItem;
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
    }
  delete header;
  return (ret);
}

bool			putMob(unsigned int const id, unsigned int const idTrade, unsigned int const idMob)
{
  bool			ret = false;
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["PUTMOB"]["IDTRADE"] = idTrade;
      (*trame)[CONTENT]["PUTMOB"]["IDMOB"] = idMob;
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
    }
  delete header;
  return (ret);
}

bool			getMob(unsigned int const id, unsigned int const idTrade, unsigned int const idMob)
{
  bool			ret = false;
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["GETMOB"]["IDTRADE"] = idTrade;
      (*trame)[CONTENT]["GETMOB"]["IDMOB"] = idMob;
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
    }
  delete header;
  return (ret);
}

bool			putMoney(unsigned int const id, unsigned int const idTrade, unsigned int const money)
{
  bool			ret = false;
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["PUTMONEY"]["MONEY"] = money;
      (*trame)[CONTENT]["PUTMONEY"]["IDTRADE"] = idTrade;
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
    }
  delete header;
  return (ret);
}

bool			getMoney(unsigned int const id, unsigned int const idTrade, unsigned int const money)
{
  bool			ret = false;
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["GETMONEY"]["MONEY"] = money;
      (*trame)[CONTENT]["GETMONEY"]["IDTRADE"] = idTrade;
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
    }
  delete header;
  return (ret);
}

bool			accept(unsigned int const id, unsigned int const idTrade)
{
  bool			ret = false;
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["ACCEPT"] = idTrade;
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
    }
  delete header;
  return (ret);
}

bool			refuse(unsigned int const id, unsigned int const idTrade)
{
  bool			ret = false;
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["REFUSE"] = idTrade;
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
    }
  delete header;
  return (ret);
}

bool			mobtoBattleMob(unsigned int const id, unsigned int const idMob)
{
  bool			ret = false;
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["MOBTOBATTLEMOB"] = idMob;
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
    }
  delete header;
  return (ret);
}

bool			switchMobs(unsigned int const id, unsigned int const idMob1, unsigned int const idMob2)
{
  bool			ret = false;
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["SWITCHMOBS"]["IDMOB1"] = idMob1;
      (*trame)[CONTENT]["SWITCHMOBS"]["IDMOB2"] = idMob2;
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
    }
  delete header;
  return (ret);
}

bool			battleMobtoMob(unsigned int const id, unsigned int const idMob)
{
  bool			ret = false;
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["BATTLEMOBTOMOB"] = idMob;
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
    }
  delete header;
  return (ret);
}

bool			merge(unsigned int const id, unsigned int const idStack1, unsigned int const idStack2)
{
  bool			ret = false;
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["MERGE"]["IDSTACK1"] = idStack1;
      (*trame)[CONTENT]["MERGE"]["IDSTACK2"] = idStack2;
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
    }
  delete header;
  return (ret);
}

bool			newStack(unsigned int const id, unsigned int const idStack, unsigned int const nb)
{
  bool			ret = false;
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["NEWSTACK"]["IDSTACK"] = idStack;
      (*trame)[CONTENT]["NEWSTACK"]["NB"] = nb;
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
    }
  delete header;
  return (ret);
}

bool			newGuild(unsigned int const id, std::string guild)
{
  bool			ret = false;
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["NEWGUILD"] = guild;
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
    }
  delete header;
  return (ret);
}

bool			invite(unsigned int const id, std::string guild)
{
  bool			ret = false;
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["INVITE"] = guild;
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
    }
  delete header;
  return (ret);
}

bool			guild(unsigned int const id, Guild *g)
{
  bool			ret = false;
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      //      g->serializationMembers((*trame)((*trame)[CONTENT]["GUILD"]));
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
    }
  delete header;
  return (ret);
}

bool			newMember(unsigned int const id, std::string player, Zone *zone)
{
  bool			ret = false;
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["NEWMEMBER"] = player;
      trame->setEnd(true);
      ret = sendToAllClient(id, trame, zone, false);
    }
  delete header;
  return (ret);
}

bool			deleteMember(unsigned int const id, std::string player, Zone *zone)
{
  bool			ret = false;
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["DELETEMEMBER"] = player;
      trame->setEnd(true);
      ret = sendToAllClient(id, trame, zone, false);
    }
  delete header;
  return (ret);
}

bool			mobModels(unsigned int const id)
{
  bool			ret = false;
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      ret = (**LoaderManager::getInstance()->getMobModelLoader())->serialization(*trame);;
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
    }
  delete header;
  return (ret);
}

bool			jobModels(unsigned int const id)
{
  bool			ret = false;
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      ret = (**LoaderManager::getInstance()->getJobModelLoader())->serialization(*trame);
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
    }
  delete header;
  return (ret);
}

bool			stuffs(unsigned int const id)
{
  bool			ret = false;
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      ret = (**LoaderManager::getInstance()->getStuffLoader())->serialization(*trame);
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
    }
  delete header;
  return (ret);
}

bool			consumables(unsigned int const id)
{
  bool			ret = false;
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      ret = (**LoaderManager::getInstance()->getConsumableLoader())->serialization(*trame);
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
    }
  delete header;
  return (ret);
}

bool			talentModels(unsigned int const id)
{
  bool			ret = false;
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      ret = (**LoaderManager::getInstance()->getTalentModelLoader())->serialization(*trame);
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
    }
  delete header;
  return (ret);
}

bool			ressources(unsigned int const id)
{
  bool			ret = false;
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      ret = (**LoaderManager::getInstance()->getRessourceLoader())->serialization(*trame);
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
    }
  delete header;
  return (ret);
}

bool			heals(unsigned int const id)
{
  bool			ret = false;
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      ret = (**LoaderManager::getInstance()->getHealLoader())->serialization(*trame);
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
    }
  delete header;
  return (ret);
}


bool			spells(unsigned int const id)
{
  bool			ret = false;
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      ret = (**LoaderManager::getInstance()->getSpellLoader())->serialization(*trame);
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
    }
  delete header;
  return (ret);
}

bool			authorizedStatKeys(unsigned int const id)
{
  bool			ret = false;
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      ret = (**LoaderManager::getInstance()->getAuthorizedStatKeyLoader())->serialization(*trame);
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
    }
  delete header;
  return (ret);
}

bool			updateCharacter(unsigned int const id, ACharacter const *character)
{
  bool			ret = false;
  Trame			*trame;
  Header		*header;

  if (character)
    {
      ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
      ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
      header->setIdClient(id);
      header->setProtocole("TCP");
      if (header->serialization(*trame))
	{
	  character->getStats().serialization((*trame)((*trame)[CONTENT]["UPDATECHARACTER"]));
	  trame->setEnd(true);
	  CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
	  ret = true;
	}
      delete header;
    }
  return (ret);
}

bool			addToInventory(unsigned int const id, Stack *stack)
{
  bool			ret = false;
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["ADDTOINVENTORY"][stack->getItem()->getName()] = stack->getNb();
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
    }
  delete header;
  return (ret);
}

bool			deleteFromInventory(unsigned int const id, std::list<Stack *> *stacks)
{
  bool			ret = false;
  Trame			*trame;
  Header		*header;
  int			nb = 0;
  std::ostringstream	str;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      for (auto it = stacks->begin() ; it != stacks->end() ; ++it)
	{
	  str << nb;
	  (*trame)[CONTENT]["DELETEFROMINVENTORY"][str.str()][(*it)->getItem()->getName()] = (*it)->getNb();
	  str.str("");
	  nb++;
	}
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
    }
  delete header;
  return (ret);
}

bool			stuff(unsigned int const id, int action, unsigned int idItem, unsigned int target)
{
  bool			ret = false;
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["STUFF"]["ACTION"] = action;
      (*trame)[CONTENT]["STUFF"]["TARGET"] = target;
      (*trame)[CONTENT]["STUFF"]["IDITEM"] = idItem;
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
    }
  delete header;
  return (ret);
}

bool			job(unsigned int const id, Job const *job)
{
  bool			ret = false;
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame) && job->serialization((*trame)((*trame)[CONTENT]["JOB"])))
    {
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
      ret = true;
    }
  delete header;
  return (ret);
}

bool			craft(unsigned int const id, std::string craftName, std::string jobName)
{
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["CRAFT"]["CRAFTNAME"] = craftName;
      (*trame)[CONTENT]["CRAFT"]["JOBNAME"] = jobName;
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
    }
  delete header;
  return (false);
}

bool			heal(unsigned int const id)
{
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["HEAL"];
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
    }
  delete header;
  return (false);
}

bool			disconnect(unsigned int const id)
{
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["DISCONNECT"];
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
    }
  delete header;
  return (false);
}

bool			switchPlayer(unsigned int const id)
{
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["SWITCHPLAYER"];
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
    }
  delete header;
  return (false);
}

bool			sendTrameAlreadyReady(unsigned int const id, Trame *trame)
{
  (*trame)[HEADER]["IDCLIENT"] = id;
  trame->setEnd(true);
  CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
  return (true);
}

bool			Protocol::decodeTrame(Trame *trame)
{
  bool			ret = false;

  for (auto it = this->_decode->begin() ; it != this->_decode->end() ; ++it)
    {
      if ((*trame)[CONTENT].isMember(it->first))
	ret = ((*this->_decode)[it->first])(trame);
    }
  return (ret);
}

// bool			Protocol::operator()(std::string const &key, unsigned int const id, void *param)
// {
//   if (this->_container->find(key) != this->_container->end())
//     return ((this->*(*_container)[key])(id, param));
//   return (false);
// }

