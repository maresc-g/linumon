//
// Protocole.hh for  in /home/ansel_l/Documents/Pfa/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Dec 12 13:29:12 2013 laurent ansel
// Last update Fri Jan 24 14:13:49 2014 laurent ansel
//

#ifndef 			__PROTOCOL_HPP__
# define 			__PROTOCOL_HPP__

#include			<sstream>
#include			<fstream>
#include			<list>
#include			"Header/Header.hh"
#include			"Trame/Trame.hh"
#include			"ObjectPool/ObjectPoolManager.hpp"
#include			"CircularBufferManager/CircularBufferManager.hh"

class				Protocol;

typedef bool			(Protocol::*funcProtocol)(unsigned int const, void *);
typedef bool			(*funcDecode)(Trame *);

class				Protocol
{
private:
  std::map<std::string, funcProtocol>	*_container;
  std::map<std::string, funcDecode>	*_decode;
  bool				_server;
public:
  Protocol(bool const server);
  virtual ~Protocol();
  bool				operator()(std::string const &key, unsigned int const id, void *param);
  bool				addFunc(std::string const &key, bool (*func)(Trame *));
  bool				welcome(unsigned int const id, void *);
  bool				initialize(unsigned int const id, void *);
  bool				check(unsigned int const id, void *);
  bool				decodeTrame(Trame *trame);
};

#endif
