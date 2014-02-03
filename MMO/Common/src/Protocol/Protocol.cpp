//
// Protocol.cpp for  in /home/ansel_l/Documents/Pfa/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Jan 24 10:57:48 2014 laurent ansel
// Last update Mon Feb  3 16:02:35 2014 guillaume marescaux
//

#include		"Protocol/Protocol.hpp"
#include		"Error/Error.hpp"
#include		"Entities/Players.hh"

Protocol::Protocol(bool const server):
  _container(new std::map<std::string, funcProtocol>),
  _decode(new std::map<std::string, funcDecode>),
  _server(server)
{
  ObjectPoolManager::getInstance()->runObjectPool<Trame>("trame");
  ObjectPoolManager::getInstance()->runObjectPool<Header>("header");

  if (server)
    {
      (*this->_container)["WELCOME"] = &Protocol::welcome;
      (*this->_container)["CHECK"] = &Protocol::check;
      (*this->_container)["ERROR"] = &Protocol::error;
      (*this->_container)["LAUNCHBATTLE"] = &Protocol::launchBattle;
      (*this->_container)["SPELL"] = &Protocol::spell;
      (*this->_container)["SPELLEFFECT"] = &Protocol::spellEffect;
      (*this->_container)["CAPTUREEFFECT"] = &Protocol::captureEffect;
      (*this->_container)["SWITCH"] = &Protocol::dswitch;
      (*this->_container)["DEADMOB"] = &Protocol::deadMob;
      (*this->_container)["ENDBATTLE"] = &Protocol::endBattle;
      (*this->_container)["PLAYERLIST"] = &Protocol::playerlist;
    }
  else
    {
      (*this->_container)["INITIALIZE"] = &Protocol::initialize;
      (*this->_container)["CONNECTION"] = &Protocol::connection;
      (*this->_container)["ERROR"] = &Protocol::error;
      (*this->_container)["CREATE"] = &Protocol::create;
      (*this->_container)["CHOOSEPLAYER"] = &Protocol::choosePlayer;
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

bool			Protocol::welcome(unsigned int const id, void *)
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

bool			Protocol::error(unsigned int const id, void *param)
{
  Trame			*trame;
  Header		*header;
  Error			*error = reinterpret_cast<Error *>(param);

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

bool			Protocol::initialize(unsigned int const id, void *)
{
  Trame			*trame;
  Header		*header;

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

bool			Protocol::connection(unsigned int const id, std::string const &pseudo, std::string const &pass)
{
  Trame			*trame;
  Header		*header;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["CONNECTION"]["PSEUDO"] = pseudo;
      (*trame)[CONTENT]["CONNECTION"]["PASS"] = pass;
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
    }
  delete header;
  return (false);
}

bool			Protocol::create(unsigned int const id, void *param)
{
  Trame			*trame;
  Header		*header;
  CreateInfos		*infos = reinterpret_cast<CreateInfos *>(param);

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["CREATE"]["NAME"] = infos->name;
      (*trame)[CONTENT]["CREATE"]["FACTION"] = infos->faction;
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
    }
  delete header;
  return (false);
}

bool			Protocol::choosePlayer(unsigned int const id, int playerId)
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

bool			Protocol::check(unsigned int const id, void *)
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

bool                    Protocol::playerlist(unsigned int const id, void *param)
{
  Trame                 *trame;
  Header                *header;
  Players               *ps = reinterpret_cast<Players *>(param);

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

bool			Protocol::launchBattle(unsigned int const id, void *param)
{
  Trame			*trame;
  Header		*header;
  auto			params = reinterpret_cast<std::tuple<unsigned int const, Player const> *>(param);

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["LAUNCHBATTLE"]["IDBATTLE"] = std::get<0>(*params);
      // (*trame)[CONTENT]["LAUNCHBATTLE"]["ENEMY"] = std::get<1>(*params)->;
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
    }
  delete header;
  delete params;
  return (false);
}

bool			Protocol::spell(unsigned int const id, void *param)
{
  Trame			*trame;
  Header		*header;
  auto			params = reinterpret_cast<std::tuple<unsigned int const, Spell const, unsigned int const> *>(param);

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["SPELL"]["IDBATTLE"] = std::get<0>(*params);
      // (*trame)[CONTENT]["SPELL"]["SPELL"] = std::get<1>(*params)->;
      (*trame)[CONTENT]["SPELL"]["TARGET"] = std::get<2>(*params);
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
    }
  delete header;
  delete params;
  return (false);
}

bool			Protocol::spellEffect(unsigned int const id, void *param)
{
  Trame			*trame;
  Header		*header;
  auto			params = reinterpret_cast<std::tuple<unsigned int const, int const, unsigned int const> *>(param);

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["SPELLEFFECT"]["IDBATTLE"] = std::get<0>(*params);
      (*trame)[CONTENT]["SPELLEFFECT"]["HPCHANGE"] = std::get<1>(*params);
      (*trame)[CONTENT]["SPELLEFFECT"]["TARGET"] = std::get<2>(*params);
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
    }
  delete header;
  delete params;
  return (false);
}

bool			Protocol::captureEffect(unsigned int const id, void *param)
{
  Trame			*trame;
  Header		*header;
  auto			params = reinterpret_cast<std::tuple<unsigned int const, bool> *>(param);

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["CAPTUREEFFECT"]["IDBATTLE"] = std::get<0>(*params);
      (*trame)[CONTENT]["CAPTUREEFFECT"]["SUCCESS"] = std::get<1>(*params);
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
    }
  delete header;
  delete params;
  return (false);
}

bool			Protocol::dswitch(unsigned int const id, void *param)
{
  Trame			*trame;
  Header		*header;
  auto			params = reinterpret_cast<std::tuple<unsigned int const, unsigned int const, unsigned int const> *>(param);

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["SwITCH"]["IDBATTLE"] = std::get<0>(*params);
      (*trame)[CONTENT]["SWITCH"]["TARGET"] = std::get<1>(*params);
      (*trame)[CONTENT]["SWITCH"]["NEWMOB"] = std::get<2>(*params);
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
    }
  delete params;
  delete header;
  return (false);
}

bool			Protocol::deadMob(unsigned int const id, void *param)
{
  Trame			*trame;
  Header		*header;
  auto			params = reinterpret_cast<std::tuple<unsigned int const, unsigned int const> *>(param);

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["DEADMOB"]["IDBATTLE"] = std::get<0>(*params);
      (*trame)[CONTENT]["DEADMOB"]["ID"] = std::get<1>(*params);
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
    }
  delete params;
  delete header;
  return (false);
}

bool			Protocol::endBattle(unsigned int const id, void *param)
{
  Trame			*trame;
  Header		*header;
  auto			params = reinterpret_cast<std::tuple<unsigned int const, bool, unsigned int const, unsigned int const, std::list<AItem *>> *>(param);

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["ENDBATTLE"]["IDBATTLE"] = std::get<0>(*params);
      (*trame)[CONTENT]["ENDBATTLE"]["WIN"] = std::get<1>(*params);
      (*trame)[CONTENT]["ENDBATTLE"]["MONEY"] = std::get<2>(*params);
      (*trame)[CONTENT]["ENDBATTLE"]["EXP"] = std::get<3>(*params);
      // (*trame)[CONTENT]["ENDBATTLE"]["ITEMS"] = std::get<1>(*params);
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
    }
  delete params;
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

bool			Protocol::operator()(std::string const &key, unsigned int const id, void *param)
{
  if (this->_container->find(key) != this->_container->end())
    return ((this->*(*_container)[key])(id, param));
  return (false);
}

