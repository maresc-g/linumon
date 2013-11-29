//
// Header.cpp for  in /home/ansel_l/Documents/Pfa/work/Common
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Nov 29 15:26:56 2013 laurent ansel
// Last update Fri Nov 29 15:47:00 2013 laurent ansel
//

#include			"Header/Header.hh"

Header::Header(unsigned int const idClient, std::string const &protocole):
  _idClient(idClient),
  _protocole(protocole)
{

}

Header::~Header()
{
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

bool				Header::serialization(Trame &trame)
{
  if (&trame)
    {
      trame["HEADER"]["IDCLIENT"] = this->_idClient;
      trame["HEADER"]["PROTOCOLE"] = this->_protocole;
      return (true);
    }
  return (false);
}

bool				Header::deserialization(Trame const &trame)
{
  if (trame.isMember("HEADER"))
    {
      if (trame["HEADER"].isMember("IDCLIENT"))
	this->_idClient = trame["HEADER"]["IDCLIENT"].asUInt();
      else
	return (false);
      if (trame["HEADER"].isMember("PROTOCOLE"))
	this->_protocole = trame["HEADER"]["PROTOCOLE"].asString();
      else
	return (false);
      return (true);
    }
  return (false);
}
