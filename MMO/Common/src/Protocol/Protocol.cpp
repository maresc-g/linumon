//
// Protocol.cpp for  in /home/ansel_l/Documents/Pfa/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Jan 24 10:57:48 2014 laurent ansel
// Last update Tue Feb 11 11:27:43 2014 laurent ansel
//

#include		"Protocol/Protocol.hpp"
#include		"Error/Error.hpp"
#include		"Entities/User.hh"

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
      this->_container->load<unsigned int, Zone *>("MAP", &map);
      this->_container->load<unsigned int, Trame *, Zone *, bool>("SENDTOALLCLIENT", &sendToAllClient);
      this->_container->load<unsigned int, Trame *>("ALREADYREADY", &sendTrameAlreadyReady);


      this->_container->load<unsigned int, unsigned int, Player const *>("LAUNCHBATTLE", &launchBattle);
      this->_container->load<unsigned int, unsigned int, Spell const *, unsigned int>("SPELL", &spell);
      this->_container->load<unsigned int, unsigned int, int, unsigned int>("SPELLEFFECT", &spellEffect);
      this->_container->load<unsigned int, unsigned int, bool>("CAPTUREEFFECT", &captureEffect);
      this->_container->load<unsigned int, unsigned int, unsigned int, unsigned int>("SWITCH", &dswitch);
      this->_container->load<unsigned int, unsigned int, unsigned int>("DEADMOB", &deadMob);
      this->_container->load<unsigned int, unsigned int, bool, unsigned int, unsigned int, std::list<AItem *>*>("ENDBATTLE", &endBattle);
      this->_container->load<unsigned int, int, Player::PlayerCoordinate const *>("ENTITY", &entity);
      this->_container->load<unsigned int, int, Zone *>("REMOVEENTITY", &removeEntity);
      // (*this->_container)["CAPTUREEFFECT"] = &Protocol::captureEffect;
      // (*this->_container)["SWITCH"] = &Protocol::dswitch;
      // (*this->_container)["DEADMOB"] = &Protocol::deadMob;
      // (*this->_container)["ENDBATTLE"] = &Protocol::endBattle;
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
      this->_container->load<unsigned int, unsigned int, Spell const *, unsigned int>("SPELL", &spell);
      this->_container->load<unsigned int, unsigned int, unsigned int, unsigned int>("SWITCH", &dswitch);
      this->_container->load<unsigned int, unsigned int, AItem const *>("USEOBJECT", &useObject);
      this->_container->load<unsigned int, AItem const *>("PUTITEM", &putItem);
      this->_container->load<unsigned int, AItem const *>("GETITEM", &getItem);
      this->_container->load<unsigned int, unsigned int>("PUTMONEY", &putMoney);
      this->_container->load<unsigned int, unsigned int>("GETMONEY", &getMoney);
      this->_container->load<unsigned int>("ACCEPT", &accept);
      this->_container->load<unsigned int>("REFUSE", &refuse);
      this->_container->load<unsigned int>("HEAL", &heal);
      this->_container->load<unsigned int>("DISCONNECT", &disconnect);
      this->_container->load<unsigned int, unsigned int, Spell const *, unsigned int>("SPELL", &spell);
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
      (*trame)[CONTENT]["IDZONE"] = idZone;
      (*trame)[CONTENT]["MESSAGE"] = msg;
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
  if (header->serialization(*trame) && coord->serialization((*trame)((*trame)["ENTITY"])))
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
  header->setProtocole("UDP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["ID"] = entityId;
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
	  std::cout << trame->toString() << std::endl;
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
  Trame			*tmp = NULL;;
  bool			ret = false;

  if (trame && zone)
    {
      list = zone->getPlayers();
      for (auto ip = list.begin() ; ip != list.end() ; ++ip)
	{
	  if ((*ip))
	    {
	      if ((idClient = reinterpret_cast<Player *>(*ip)->getUser().getId()))
		{
		  ObjectPoolManager::getInstance()->setObject(tmp, "trame");
		  *tmp = *trame;
		  CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
		  tmp = NULL;
		}
	    }
	  ret = true;
	}
      if (send)
	{
	  (*trame)[HEADER]["IDCLIENT"] = id;
	  CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
	}
      return (ret);
    }
  return (ret);
}

bool			launchBattle(unsigned int const id, unsigned int const idBattle, Player const *player)
{
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["LAUNCHBATTLE"]["IDBATTLE"] = idBattle;
      (*trame)[CONTENT]["LAUNCHBATTLE"]["ENEMY"] = player->serialization((*trame)((*trame)[CONTENT]["LAUNCHBATTLE"]["ENEMY"]));
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
    }
  delete header;
  return (false);
}

bool			spell(unsigned int const id,
			      unsigned int const idBattle,
			      Spell const *spell,
			      unsigned int const target)
{
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["SPELL"]["IDBATTLE"] = idBattle;
      (*trame)[CONTENT]["SPELL"]["SPELL"] = spell->serialization((*trame)((*trame)[CONTENT]["SPELL"]["SPELL"]));
      (*trame)[CONTENT]["SPELL"]["TARGET"] = target;
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
    }
  delete header;
  return (false);
}

bool			spellEffect(unsigned int const id, 
				    unsigned int const idBattle, 
				    int const hpChange, 
				    unsigned int const target)
{
  Trame			*trame;
  Header		*header;

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
    }
  delete header;
  return (false);
}

bool			captureEffect(unsigned int const id, unsigned int const idBattle, bool success)
{
  Trame			*trame;
  Header		*header;

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
    }
  delete header;
  return (false);
}

bool			dswitch(unsigned int const id, 
					  unsigned int const idBattle, 
					  unsigned int const target, 
					  unsigned int const newMob)
{
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["SWITCH"]["IDBATTLE"] = idBattle;
      (*trame)[CONTENT]["SWITCH"]["TARGET"] = target;
      (*trame)[CONTENT]["SWITCH"]["NEWMOB"] = newMob;
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
    }
  delete header;
  return (false);
}

bool			deadMob(unsigned int const id, unsigned int const idBattle, unsigned int const idMob)
{
  Trame			*trame;
  Header		*header;

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
    }
  delete header;
  return (false);
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
    }
  delete header;
  return (false);
}

bool			useObject(unsigned int const id, unsigned int target, AItem const *item)
{
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["USEOBJECT"]["TARGET"] = target;
      (*trame)[CONTENT]["USEOBJECT"]["ITEM"] = item->serialization((*trame)((*trame)[CONTENT]["USEOBJECT"]["ITEM"]));
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
    }
  delete header;
  return (false);
}

bool			putItem(unsigned int const id, AItem const *item)
{
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["PUTITEM"] = item->serialization((*trame)((*trame)[CONTENT]["GETITEM"]));
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
    }
  delete header;
  return (false);
}

bool			getItem(unsigned int const id, AItem const *item)
{
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["GETITEM"] = item->serialization((*trame)((*trame)[CONTENT]["GETITEM"]));
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
    }
  delete header;
  return (false);
}

bool			putMoney(unsigned int const id, unsigned int money)
{
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["PUTMONEY"] = money;
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
    }
  delete header;
  return (false);
}

bool			getMoney(unsigned int const id, unsigned int money)
{
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["GETMONEY"] = money;
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
    }
  delete header;
  return (false);
}

bool			accept(unsigned int const id)
{
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["ACCEPT"];
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
    }
  delete header;
  return (false);
}

bool			refuse(unsigned int const id)
{
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["REFUSE"];
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

