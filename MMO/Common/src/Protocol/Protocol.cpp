//
// Protocol.cpp for  in /home/ansel_l/Documents/Pfa/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Jan 24 10:57:48 2014 laurent ansel
// Last update Fri Jan 24 16:50:01 2014 laurent ansel
//

#include		"Protocol/Protocol.hpp"

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
      (*this->_container)["CHECK"] = &Protocol::welcome;
    }
  else
    {
      (*this->_container)["INITIALIZE"] = &Protocol::initialize;
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

bool			Protocol::welcome(unsigned int const id, void *)
{
  Trame			*trame;
  Header		*header;
  std::string str;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)["WELCOME"];
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
  std::string str;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("UDP");
  if (header->serialization(*trame))
    {
      (*trame)["INITIALIZE"];
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
  std::string str;

  ObjectPoolManager::getInstance()->setObject<Trame>(trame, "trame");
  ObjectPoolManager::getInstance()->setObject<Header>(header, "header");
  header->setIdClient(id);
  header->setProtocole("TCP");
  if (header->serialization(*trame))
    {
      (*trame)["CHECK"];
      trame->setEnd(true);
      CircularBufferManager::getInstance()->pushTrame(trame, CircularBufferManager::WRITE_BUFFER);
    }
  delete header;
  return (false);
}

bool			Protocol::decodeTrame(Trame *trame)
{
  for (auto it = this->_decode->begin() ; it != this->_decode->end() ; ++it)
    {
      if (trame->isMember(it->first))
	return (((*this->_decode)[it->first])(trame));
    }
  return (false);
}

bool			Protocol::operator()(std::string const &key, unsigned int const id, void *param)
{
  if (this->_container->find(key) != this->_container->end())
    return ((this->*(*_container)[key])(id, param));
  return (false);
}
