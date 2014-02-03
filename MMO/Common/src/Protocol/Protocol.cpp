//
// Protocol.cpp for  in /home/ansel_l/Documents/Pfa/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Jan 24 10:57:48 2014 laurent ansel
// Last update Fri Jan 31 16:03:49 2014 guillaume marescaux
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

bool			Protocol::connection(unsigned int const id, void *param)
{
  Trame			*trame;
  Header		*header;
  LoginInfos		*infos = reinterpret_cast<LoginInfos *>(param);

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["CONNECTION"]["PSEUDO"] = infos->pseudo;
      (*trame)[CONTENT]["CONNECTION"]["PASS"] = infos->pass;
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

bool			Protocol::choosePlayer(unsigned int const id, void *param)
{
  Trame			*trame;
  Header		*header;
  int			*playerId = reinterpret_cast<int *>(param);

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)[CONTENT]["CHOOSEPLAYER"]["ID"] = *playerId;
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

bool			Protocol::playerlist(unsigned int const id, void *param)
{
  Trame			*trame;
  Header		*header;
  Players		*ps = reinterpret_cast<Players *>(param);

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
