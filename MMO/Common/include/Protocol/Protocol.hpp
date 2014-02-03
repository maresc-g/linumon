//
// Protocole.hh for  in /home/ansel_l/Documents/Pfa/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Dec 12 13:29:12 2013 laurent ansel
// Last update Fri Jan 31 14:10:20 2014 antoine maitre
//

#ifndef 			__PROTOCOL_HPP__
# define 			__PROTOCOL_HPP__

#include			<sstream>
#include			<fstream>
#include			<list>
#include			<functional>
#include			"Battle/BattleUpdater.hh"
#include			"Header/Header.hh"
#include			"Trame/Trame.hh"
#include			"ObjectPool/ObjectPoolManager.hpp"
#include			"CircularBufferManager/CircularBufferManager.hh"
#include			"Entities/AItem.hh"

class				Protocol;

typedef bool			(Protocol::*funcProtocol)(unsigned int const, void *);
typedef std::function <bool (Trame *)> funcDecode;

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
  bool				addFunc(std::string const &key, std::function<bool (Trame *)> func);
  bool				decodeTrame(Trame *trame);
private:
  bool				welcome(unsigned int const id, void *);
  bool				initialize(unsigned int const id, void *);
  bool				check(unsigned int const id, void *);
  bool				launchBattle(unsigned int const id, void *param);
  bool				spell(unsigned int const id, void *param);
  bool				spellEffect(unsigned int const id, void *param);
  bool				captureEffect(unsigned int const id, void *param);
  bool				dswitch(unsigned int const id, void *param);
  bool				deadMob(unsigned int const id, void *param);
  bool				endBattle(unsigned int const id, void *param);
  bool				error(unsigned int const id, void *error);
  bool				playerlist(unsigned int const id, void *players);
  bool				connection(unsigned int const id, void *param);
};

#endif
