//
// Protocole.hh for  in /home/ansel_l/Documents/Pfa/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Dec 12 13:29:12 2013 laurent ansel
// Last update Mon Mar 10 15:59:02 2014 laurent ansel
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
#include			"Zone/Zone.hh"

class				Protocol;

typedef bool			(Protocol::*funcProtocol)(unsigned int const, void *);
typedef std::function <bool (Trame *)> funcDecode;

class				Protocol
{
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
  // bool				connection(unsigned int const id, std::string const &pseudo, std::string const &pass);
  // bool				create(unsigned int const id, void *param);
  // bool				choosePlayer(unsigned int const id, int playerId);
};

bool				launchBattle(unsigned int const id, unsigned int const idBatlle, Player const*);
bool				spell(unsigned int const id, unsigned int const idBattle, Spell const *spell, unsigned int const launcher, unsigned int const target);
bool				spellEffect(unsigned int const id, unsigned int const idBattle, int const hpChange, unsigned int const target);
bool				captureEffect(unsigned int const id, unsigned int const idBattle, bool success);
bool				dswitch(unsigned int const id, unsigned int const idBattle, unsigned int const target, unsigned int const newMob);
bool				deadMob(unsigned int const id, unsigned int const idBattle, unsigned int const idMob);
bool				endBattle(unsigned int const id, unsigned int const idBattle, bool win, unsigned int const money, unsigned int const exp, std::list<AItem *> *items);
bool				turnTo(unsigned int const id, unsigned int const idMob);

bool				welcome(unsigned int const id);
bool				check(unsigned int const id);
bool				error(unsigned int const id, Error *error);
bool				playerlist(unsigned int const id, User *user);
bool				initialize(unsigned int const id);
bool				connection(unsigned int const id, std::string pseudo, std::string pass);
bool				create(unsigned int const id, std::string name, Faction const *faction);
bool				choosePlayer(unsigned int const id, int playerId);
bool				player(unsigned int const id, Player *player);
bool				map(unsigned int const id, Zone *zone);
bool				sendToAllClient(unsigned int const id, Trame *trame, Zone *zone, bool const send);
bool				entity(unsigned int const id, int playerId, Player::PlayerCoordinate const *coord);
bool				removeEntity(unsigned int const id, int removeId, Zone *zone);
bool				chat(unsigned int const id, std::string idZone, std::string msg);
bool				capture(unsigned int const id, unsigned int idBattle, unsigned int target);
bool				stuff(unsigned int const id, int action, unsigned int idItem, unsigned int target);
//  bool				stuff(void *action);
  // bool				talents();'
bool				craft(unsigned int const id, std::string craftName, std::string jobName);
  // bool				gather();
bool				objectEffect(unsigned int const id, unsigned int const target, Stats const *stats);
bool				useObject(unsigned int const id, unsigned int target, unsigned int idItem);
// bool				interaction();
bool				launchTrade(unsigned int const id, unsigned int const idTrade, std::string namePlayer);
bool				putMob(unsigned int const id, unsigned int const idTrade, Mob const *mob);
bool				getMob(unsigned int const id, unsigned int const idTrade, Mob const *mob);
bool				putItem(unsigned int const id, unsigned int const idTrade, AItem const *item);
bool				getItem(unsigned int const id, unsigned int const idTrade, AItem const *item);
bool				putMoney(unsigned int const id, unsigned int const idTrade, unsigned int const money);
bool				getMoney(unsigned int const id, unsigned int const idTrade, unsigned int const money);
bool				accept(unsigned int const id, unsigned int const idTrade);
bool				refuse(unsigned int const id, unsigned int const idTrade);
bool				updateCharacter(unsigned int const id, ACharacter const *character);
bool				heal(unsigned int const id);
bool				disconnect(unsigned int const id);
bool				switchPlayer(unsigned int const id);
bool				sendTrameAlreadyReady(unsigned int const id, Trame *trame);

bool				addToInventory(unsigned int const id, std::list<AItem *> *list);
bool				deleteFromInventory(unsigned int const id, std::list<std::pair<unsigned int, unsigned int> > *list);
bool				job(unsigned int const id, Job const *job);
bool				newPlayer(unsigned int const id, Player *player, Zone *zone);
bool				newZone(unsigned int const id, Player *player, Zone *oldZone, Zone *zone);
bool				visible(unsigned int const id, unsigned int const idRessource, bool const visible, Zone *zone);

bool				mobModels(unsigned int const id);
bool				jobModels(unsigned int const id);
bool				stuffs(unsigned int const id);
bool				consumables(unsigned int const id);
bool				talentModels(unsigned int const id);
bool				ressources(unsigned int const id);
bool				heals(unsigned int const id);
bool				spells(unsigned int const id);
bool				authorizedStatKeys(unsigned int const id);

#endif
