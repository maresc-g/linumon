//
// Client.cpp for  in /home/ansel_l/Documents/Pfa/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Tue Dec  3 16:04:56 2013 laurent ansel
// Last update Tue Feb 11 13:11:20 2014 laurent ansel
//

#include			"ClientManager/Client.hh"
#include			"Server/Server.hh"
#include			"Map/Map.hh"
#include			"ClientWriter/ClientWriter.hh"

Client::Client():
  _use(false),
  _id(0),
  _sockets(new std::map<std::string, ISocketClient *>),
  _user(NULL),
  _player(NULL)
{
  (*_sockets)["UDP"] = NULL;
  (*_sockets)["TCP"] = NULL;
}

Client::~Client()
{
  delete (*_sockets)["UDP"];
  delete (*_sockets)["TCP"];
  delete _sockets;
}

void				Client::clear()
{
  if (_player)
    Server::getInstance()->callProtocol<int, Zone *>("REMOVEENTITY", _id, _id, Map::getInstance()->getZone(_player->getZone()));
  delete (*_sockets)["UDP"];
  delete (*_sockets)["TCP"];
  (*_sockets)["UDP"] = NULL;
  (*_sockets)["TCP"] = NULL;
  _id = 0;
  _use = false;
  if (_user)
    _user->setId(0);
  _user = NULL;
  delete _player;
  _player = NULL;
}

bool				Client::isUse() const
{
  return (this->_use);
}

FD				Client::getId() const
{
  return (this->_id);
}

void				Client::use(FD const id)
{
  this->_id = id;
  this->_use = true;
}

void				Client::setSocket(ISocketClient const *socket, std::string const &proto)
{
  if ((*_sockets)[proto])
    delete (*_sockets)[proto];
  (*_sockets)[proto] = new SocketClient(socket);
}

bool				Client::writeTrame(Trame *trame, std::string const &proto)
{
  size_t			ret;
  std::string			str;
  std::string			tmp;

  if (trame && trame->toString(str))
    {
      // //      Crypto::getInstance()->encryption(str, tmp);
      // //      ret = (*this->_sockets)[proto]->writeSocket(const_cast<char *>(tmp.c_str()), tmp.size());
      ret = (*this->_sockets)[proto]->writeSocket(const_cast<char *>(str.c_str()), str.size());
      // //      if (ret < tmp.size())
      if (ret < str.size())
	{
	  trame->setSize(ret);
	  return (false);
	}
      ClientWriter::getInstance()->addNewTrame(_id, -1);
      return (true);
    }
  return (false);
}

bool				Client::readTrame(std::string &str, std::string const &proto)
{
  char                          tmp[SIZE_BUFFER] = "";
  std::string			decrypt;
  int				ret = (*this->_sockets)[proto]->readSocket(tmp, SIZE_BUFFER);

  if (ret > 0)
    {
      str.append(tmp, ret);
      // // decrypt.append(tmp, ret);
      // // if (Crypto::getInstance()->decryption(decrypt, str))
      return (true);
    }
  return (false);
}

void				Client::addUser(User *user)
{
  this->_user = user;
  this->_user->setId(this->_id);
}

bool				Client::addPlayer(std::string const &name, Faction *faction)
{
  if (this->_user)
    {
      Repository<Player>	*rp = &Database::getRepository<Player>();
      Player			*player = new Player(name);

      player->setFaction(*faction);
      this->_user->addPlayer(*player);
      rp->persist(*player);
      return (true);
    }
  return (false);
}

void				Client::sendListPlayers()
{
  if (_user)
    Server::getInstance()->callProtocol<User *>("PLAYERLIST", _id, _user);
}

void				Client::choosePlayer(unsigned int const id, bool const send)
{
  Repository<Player>		*rp = &Database::getRepository<Player>();

  this->_player = rp->getById(id);
  if (this->_player && send)
    {
      Map::getInstance()->addEntity(_player->getZone(), _player);
      Server::getInstance()->callProtocol<Player *>("PLAYER", _id, _player);
      Server::getInstance()->callProtocol<Zone *>("MAP", _id, Map::getInstance()->getZone(_player->getZone()));
    }
}

void				Client::move(Player::PlayerCoordinate *coord)
{
  Trame				*trame = NULL;

  if (this->_player && coord)
    this->_player->setCoord(*coord);
  ObjectPoolManager::getInstance()->setObject(trame, "trame");
  Server::getInstance()->callProtocol<Trame *, Zone *, bool>("SENDTOALLCLIENT", _id, trame, Map::getInstance()->getZone(_player->getZone()), false);
  /*
  ** random battle
  */
}

void				Client::updateTalents(Trame *trame) const
{
  TalentManager::updateTalents(trame, _player);
  Server::getInstance()->callProtocol<Player *>("PLAYER", _id, _player);
}
