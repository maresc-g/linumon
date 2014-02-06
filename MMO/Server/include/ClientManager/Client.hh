//
// Client.hh for  in /home/ansel_l/Documents/Pfa/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Tue Dec  3 15:58:04 2013 laurent ansel
// Last update Thu Feb  6 13:34:40 2014 laurent ansel
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

class				Client
{
private:
  bool				_use;
  FD				_id;
  std::map<std::string, ISocketClient *>	*_sockets;
  User				*_user;
  Player			*_player;

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
};

#endif
