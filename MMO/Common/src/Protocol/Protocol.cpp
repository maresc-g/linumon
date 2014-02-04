//
// Protocol.cpp for  in /home/ansel_l/Documents/Pfa/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Jan 24 10:57:48 2014 laurent ansel
// Last update Tue Feb  4 14:21:12 2014 antoine maitre
//

#include		"Protocol/Protocol.hpp"
#include		"Error/Error.hpp"
#include		"Entities/Players.hh"

Protocol::Protocol(bool const server):
  //  _container(new std::map<std::string, funcProtocol>),
  _container(new FunctorContainer<std::string, bool>),
  _decode(new std::map<std::string, funcDecode>),
  _server(server)
{
  ObjectPoolManager::getInstance()->runObjectPool<Trame>("trame");
  ObjectPoolManager::getInstance()->runObjectPool<Header>("header");

  if (server)
    {
      this->_container->load<unsigned int>("WELCOME", &welcome);
      this->_container->load<unsigned int>("CHECK", &check);
      this->_container->load<unsigned int, Error *>("ERROR", &error);
      this->_container->load<unsigned int, Players *>("PLAYERLIST", &playerlist);

      this->_container->load<unsigned int, unsigned int, Player const *>("LAUNCHBATTLE", &launchBattle);
      this->_container->load<unsigned int, unsigned int, Spell const *, unsigned int>("SPELL", &spell);
      this->_container->load<unsigned int, unsigned int, int, unsigned int>("SPELLEFFECT", &spellEffect);
      this->_container->load<unsigned int, unsigned int, bool>("CAPTUREEFFECT", &captureEffect);
      this->_container->load<unsigned int, unsigned int, unsigned int, unsigned int>("SWITCH", &dswitch);
      this->_container->load<unsigned int, unsigned int, unsigned int>("DEADMOB", &deadMob);
      this->_container->load<unsigned int, unsigned int, bool, unsigned int, unsigned int, std::list<AItem *>*>("ENDBATTLE", &endBattle);
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
      this->_container->load<unsigned int, std::string const &>("CREATE", &create);
      this->_container->load<unsigned int, int>("CHOOSEPLAYER", &choosePlayer);
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

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["WELCOME"];
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
    }
  delete header;
  return (false);
}

bool			error(unsigned int const id, Error *error)
{
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame) && error->serialization(*trame))
    {
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
    }
  delete header;
  return (false);
}

bool			check(unsigned int const id)
{
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["CHECK"];
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
    }
  delete header;
  return (false);
}

bool		         initialize(unsigned int const id)
{
  Trame                 *trame;
  Header                *header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("UDP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["INITIALIZE"];
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
    }
  delete header;
  return (false);
}

bool			connection(unsigned int const id, std::string pseudo, std::string pass)
{
  Trame			*trame;
  Header		*header;

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
    }
  delete header;
  return (false);
}

bool			create(unsigned int const id, std::string const &name)
{
  Trame                 *trame;
  Header                *header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["CREATE"]["NAME"] = name;
      (*trame)[CONTENT]["CREATE"]["FACTION"] = 0;
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
    }
  delete header;
  return (false);
}

bool                    choosePlayer(unsigned int const id, int playerId)
{
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["CHOOSEPLAYER"]["ID"] = playerId;
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
    }
  delete header;
  return (false);
}

bool                    playerlist(unsigned int const id, Players *ps)
{
  Trame                 *trame;
  Header                *header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame) && ps->serialization(*trame))
    {
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
    }
  delete header;
  return (false);
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
      (*trame)[CONTENT]["SwITCH"]["IDBATTLE"] = idBattle;
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

