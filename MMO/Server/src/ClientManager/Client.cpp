//
// Client.cpp for  in /home/ansel_l/Documents/Pfa/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Tue Dec  3 16:04:56 2013 laurent ansel
// Last update Tue Feb  4 16:31:36 2014 laurent ansel
//

#include			"ClientManager/Client.hh"
#include			"Server/Server.hh"
#include			"Map/Map.hh"

Client::Client():
  _use(false),
  _id(0),
  _sockets(new std::map<std::string, ISocketClient *>),
  _trame(0),
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
  //  delete _user;
  delete _player;
}

void				Client::clear()
{
  delete (*_sockets)["UDP"];
  delete (*_sockets)["TCP"];
  (*_sockets)["UDP"] = NULL;
  (*_sockets)["TCP"] = NULL;
  _id = 0;
  _trame = 0;
  _use = false;
  //  delete _user;
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
      //      Crypto::getInstance()->encryption(str, tmp);
      //      ret = (*this->_sockets)[proto]->writeSocket(const_cast<char *>(tmp.c_str()), tmp.size());
      ret = (*this->_sockets)[proto]->writeSocket(const_cast<char *>(str.c_str()), str.size());
      //      if (ret < tmp.size())
      if (ret < str.size())
	{
	  trame->setSize(ret);
	  return (false);
	}
      this->_trame--;
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
      std::cout << "RETREAD = " << ret << std::endl;
      str.append(tmp, ret);
      // decrypt.append(tmp, ret);
      // if (Crypto::getInstance()->decryption(decrypt, str))
      return (true);
    }
  return (false);
}

void				Client::addTrame(unsigned int const nb)
{
  this->_trame += nb;
  std::cout << "TRAME = " << nb << std::endl;
}

unsigned int			Client::getNbTrame() const
{
  return (this->_trame);
}

void				Client::addUser(User *user)
{
  // if (user)
  //   delete user;
  this->_user = user;
}

bool				Client::addPlayer(std::string const &name, Faction *faction)
{
  if (this->_user)
    {
      Player			*player = new Player(name);

      player->setFaction(*faction);
      //      this->_user->addPlayer(*player);
      return (true);
    }
  return (false);
}

void				Client::sendListPlayers()
{
  if (_user)
    {
      Server::getInstance()->callProtocol<User *>("PLAYERLIST", _id, _user, false);
      this->_trame++;
    }
}

void				Client::choosePlayer(unsigned int const id, bool const send)
{
  Repository<Player>		*rp = &Database::getRepository<Player>();

  this->_player = rp->getById(id);
  if (this->_player && send)
    {
      Server::getInstance()->callProtocol<Player *>("PLAYER", _id, _player, false);
      this->_trame++;
      Server::getInstance()->callProtocol<Zone *>("MAP", _id, Map::getInstance()->getZone(_player->getZone()), false);
      this->_trame++;
    }
}

bool				Client::sameUser(User *user) const
{
  if (user == _user)
    return (true);
  return (false);
}
