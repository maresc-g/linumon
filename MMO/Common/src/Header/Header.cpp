//
// Header.cpp for  in /home/ansel_l/Documents/Pfa/work/Common
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Nov 29 15:26:56 2013 laurent ansel
// Last update Wed Feb  5 13:24:50 2014 laurent ansel
//

#include			"Header/Header.hh"
#include			"ObjectPool/ObjectPoolManager.hpp"

Header::Header(unsigned int const idClient, std::string const &protocole):
  _idClient(idClient),
  _protocole(protocole)
{

}

Header::Header(Header const &header)
{
  *this = header;
}

Header::~Header()
{
}

Header				&Header::operator=(Header const &header)
{
  if (this != &header)
    {
      this->_idClient = header.getIdClient();
      this->_protocole = header.getProtocole();
    }
  return (*this);
}

unsigned int			Header::getIdClient() const
{
  return (this->_idClient);
}

std::string const		&Header::getProtocole() const
{
  return (this->_protocole);
}

void				Header::setIdClient(unsigned int const id)
{
  this->_idClient = id;
}

void				Header::setProtocole(std::string const &protocole)
{
  this->_protocole = protocole;
}

void				Header::setAll(unsigned int const id, std::string const &protocole)
{
  this->setIdClient(id);
  this->setProtocole(protocole);
}

bool				Header::serialization(Trame &trame) const
{
  if (&trame)
    {
      trame[HEADER]["IDCLIENT"] = this->_idClient;
      trame[HEADER]["PROTOCOLE"] = this->_protocole;
      return (true);
    }
  return (false);
}

Header				*Header::deserialization(Trame const &trame)
{
  Header			*header = NULL;

  if (trame.isMember(HEADER))
    {
      if (trame[HEADER].isMember("IDCLIENT") && trame[HEADER].isMember("PROTOCOLE"))
	{
	  ObjectPoolManager::getInstance()->setObject(header, "header");
	  if (header)
	    {
	      header->setIdClient(trame[HEADER]["IDCLIENT"].asUInt());
	      header->setProtocole(trame[HEADER]["PROTOCOLE"].asString());
	    }
	}
    }
  return (header);
}
