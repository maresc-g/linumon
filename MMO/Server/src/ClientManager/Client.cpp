//
// Client.cpp for  in /home/ansel_l/Documents/Pfa/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Tue Dec  3 16:04:56 2013 laurent ansel
// Last update Tue Dec 10 16:40:22 2013 laurent ansel
//

#include			"ClientManager/Client.hh"

Client::Client():
  _use(false),
  _id(0),
  _sockets(new std::map<std::string, ISocketClient *>),
  _trame(0)
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
  delete (*_sockets)["UDP"];
  delete (*_sockets)["TCP"];
  (*_sockets)["UDP"] = NULL;
  (*_sockets)["TCP"] = NULL;
  _id = 0;
  _trame = 0;
  _use = false;
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

void				Client::setSocket(ISocketClient *socket, std::string const &proto)
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
      Crypto::getInstance()->encryption(str, tmp);
      ret = (*this->_sockets)[proto]->writeSocket(const_cast<char *>(tmp.c_str()), tmp.size());
      if (ret < tmp.size())
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
      std::cout << ret << std::endl;
      decrypt.append(tmp, ret);
      if (Crypto::getInstance()->decryption(decrypt, str))
	return (true);
    }
  return (false);
}

void				Client::addTrame(unsigned int const nb)
{
  this->_trame += nb;
}

unsigned int			Client::getNbTrame() const
{
  return (this->_trame);
}
