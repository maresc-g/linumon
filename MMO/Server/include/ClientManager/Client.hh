//
// Client.hh for  in /home/ansel_l/Documents/Pfa/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Tue Dec  3 15:58:04 2013 laurent ansel
// Last update Sat Feb 15 13:22:40 2014 laurent ansel
//

#ifndef 			__CLIENT_HH__
# define 			__CLIENT_HH__

#include			<string>
#include			<map>
#include			"Trame/Trame.hh"
#include			"Socket/SocketClient.hpp"
#include			"Crypto/Crypto.hh"
#include			"Database/Repositories/PlayerRepository.hpp"
#include			"Entities/User.hh"
#include			"GameProtocol/TalentManager.hh"

class				Client
{
public:
  typedef enum			eState
    {
      NONE,
      GAME,
      BATTLE,
      TRADE
    }				eState;

private:
  bool				_use;
  FD				_id;
  std::map<std::string, ISocketClient *>	*_sockets;
  User				*_user;
  Player			*_player;
  Client::eState		_state;

public:
  Client();
  virtual ~Client();
  void				clear();
  bool				isUse() const;
  void				use(FD const fd);
  FD				getId() const;
  void				setSocket(ISocketClient const *socket, std::string const &proto);
  bool				writeTrame(Trame *trame, std::string const &proto);
  bool				readTrame(std::string &str, std::string const &proto);
  void				addUser(User *user);
  bool				addPlayer(std::string const &name, Faction *faction);
  void				sendListPlayers();
  void				choosePlayer(unsigned int const idPlayer, bool const send);
  void				move(Player::PlayerCoordinate *coord);
  void				updateTalents(Trame *trame) const;
  void				useObject(unsigned int const target, unsigned int const item);
  void				deleteObject(unsigned int const item);
  void				startBattle();
  void				endBattle();
  void				startTrade(Player *&player);
  void				endTrade();
};

#endif
