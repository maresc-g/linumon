//
// InitializeConnection.cpp for  in /home/ansel_l/Documents/Pfa/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Sun Dec  8 13:12:48 2013 laurent ansel
// Last update Mon Dec  9 19:11:29 2013 laurent ansel
//

#include			"InitializeConnection/InitializeConnection.hh"

InitializeConnection::InitializeConnection(unsigned int const id, bool const tcp, bool const udp):
  _id(id),
  _tcp(tcp),
  _udp(udp)
{

}

InitializeConnection::InitializeConnection(InitializeConnection const &other)
{
  *this = other;
}

InitializeConnection::~InitializeConnection()
{

}

InitializeConnection		&InitializeConnection::operator=(InitializeConnection const &other)
{
  if (this != &other)
    {
      this->_id = other.getId();
      this->_tcp = other.getTcp();
      this->_udp = other.getUdp();
    }
  return (*this);
}

unsigned int			InitializeConnection::getId() const
{
  return (this->_id);
}

bool				InitializeConnection::getTcp() const
{
  return (this->_tcp);
}

bool				InitializeConnection::getUdp() const
{
  return (this->_udp);
}

void				InitializeConnection::setId(unsigned int const id)
{
  this->_id = id;
}

void				InitializeConnection::setTcp(bool const tcp)
{
  this->_tcp = tcp;
}

void				InitializeConnection::setUdp(bool const udp)
{
  this->_udp = udp;
}

void				InitializeConnection::setAll(unsigned int const id, bool const tcp, bool const udp)
{
  this->setId(id);
  this->setTcp(tcp);
  this->setUdp(udp);
}

bool				InitializeConnection::serialization(Trame &trame)
{
  if (&trame)
    {
      if (_tcp)
	{
	  trame[CONTENT]["INITIALIZE"]["ID"] = this->_id;
	  trame[CONTENT]["INITIALIZE"]["PROTOCOLE"] = this->_tcp;
	}
      else
	trame[CONTENT]["INITIALIZE"]["PROTOCOLE"] = this->_udp;
      return (true);
    }
  return (false);
}

bool				InitializeConnection::deserialization(Trame const &trame)
{
  if (trame.isMember(CONTENT))
    {
      if (trame.isMember("INITIALIZE"))
	{
	  if (trame[CONTENT]["INITIALIZE"].isMember("ID"))
	    {
	      this->_id = trame[CONTENT]["INITIALIZE"]["ID"].asUInt();
	      if (trame[CONTENT]["INITIALIZE"].isMember("PROTOCOLE"))
		this->_tcp = trame[CONTENT]["INITIALIZE"]["PROTOCOLE"].asBool();
	      else
		return (false);
	    }
	  else if (trame[CONTENT]["INITIALIZE"].isMember("PROTOCOLE"))
	    this->_udp = trame[CONTENT]["INITIALIZE"]["PROTOCOLE"].asBool();
	  else
	    return (false);
	  return (true);
	}
    }
  return (false);
}
