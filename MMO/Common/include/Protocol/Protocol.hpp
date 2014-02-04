//
// Protocole.hh for  in /home/ansel_l/Documents/Pfa/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Dec 12 13:29:12 2013 laurent ansel
// Last update Tue Feb  4 10:40:53 2014 guillaume marescaux
//

#ifndef 			__PROTOCOL_HPP__
# define 			__PROTOCOL_HPP__

#include			<sstream>
#include			<fstream>
#include			<list>
#include			<functional>
#include			"Header/Header.hh"
#include			"Trame/Trame.hh"
#include			"ObjectPool/ObjectPoolManager.hpp"
#include			"CircularBufferManager/CircularBufferManager.hh"
#include			"Entities/AItem.hh"
#include			"Utility/FunctorContainer.hpp"
#include			"Error/Error.hpp"
#include			"Entities/Players.hh"

class				Protocol;

typedef bool			(Protocol::*funcProtocol)(unsigned int const, void *);
typedef std::function <bool (Trame *)> funcDecode;

class				Protocol
{
public:

  struct			LoginInfos
  {
    std::string			pseudo;
    std::string			pass;
  };

  struct			CreateInfos
  {
    std::string			name;
    int				faction;
  };

  struct			ChatInfos
  {
    ZONE::eZone			zone;
    std::string			msg;
  };

private:
  FunctorContainer<std::string, bool>	*_container;
  std::map<std::string, funcDecode>	*_decode;
  bool				_server;
public:
  Protocol(bool const server);
  virtual ~Protocol();

  template<typename... P>
  bool				operator()(std::string const &key, P... params)
  {
    return (this->_container->operator()(key, params ...));
  }

  bool				addFunc(std::string const &key, bool (*func)(Trame *));
  bool				addFunc(std::string const &key, std::function<bool (Trame *)> func);
  bool				decodeTrame(Trame *trame);

private:
  bool				launchBattle(unsigned int const id, void *param);
  bool				spell(unsigned int const id, void *param);
  bool				spellEffect(unsigned int const id, void *param);
  bool				captureEffect(unsigned int const id, void *param);
  bool				dswitch(unsigned int const id, void *param);
  bool				deadMob(unsigned int const id, void *param);
  bool				endBattle(unsigned int const id, void *param);
};

bool				welcome(unsigned int const id);
bool				check(unsigned int const id);
bool				error(unsigned int const id, Error *error);
bool				playerlist(unsigned int const id, Players *players);
bool				initialize(unsigned int const id);
bool				connection(unsigned int const id, std::string pseudo, std::string pass);
bool				create(unsigned int const id, std::string const &name);
bool				choosePlayer(unsigned int const id, int playerId);

#endif
