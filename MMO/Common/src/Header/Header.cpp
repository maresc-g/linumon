//
// Header.cpp for  in /home/ansel_l/Documents/Pfa/work/Common
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Nov 29 15:26:56 2013 laurent ansel
// Last update Mon Jan 27 13:14:46 2014 laurent ansel
//

#include			"Header/Header.hh"

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

bool				Header::deserialization(Trame const &trame)
{
  if (trame.isMember(HEADER))
    {
      if (trame[HEADER].isMember("IDCLIENT"))
	this->_idClient = trame[HEADER]["IDCLIENT"].asUInt();
      else
	return (false);
      if (trame[HEADER].isMember("PROTOCOLE"))
	this->_protocole = trame[HEADER]["PROTOCOLE"].asString();
      else
	return (false);
      return (true);
    }
  return (false);
}
