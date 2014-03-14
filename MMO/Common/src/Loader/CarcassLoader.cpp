//
// CarcassLoader.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Mar 14 15:03:55 2014 laurent ansel
// Last update Fri Mar 14 15:04:14 2014 laurent ansel
//

#ifndef CLIENT_COMPILATION
# include			"Entities/Carcass-odb.hxx"
# include			"Database/Repositories/Repository.hpp"
#endif
#include			"Loader/CarcassLoader.hh"

/*
**
**	Carcasss
**
*/

Carcasss::Carcasss() :
  _carcasss(new std::list<Carcass *>)
{
#ifndef CLIENT_COMPILATION
  Repository<Carcass>		*mm = &Database::getRepository<Carcass>();

  *_carcasss = mm->getAll();
#endif
}

Carcasss::~Carcasss()
{
  for (auto it = _carcasss->begin() ; it != _carcasss->end() ; ++it)
    delete *it;
  delete _carcasss;
}

std::list<Carcass *> const	&Carcasss::getCarcasss() const
{
  return (*this->_carcasss);
}

void				Carcasss::addCarcass(Carcass *carcass)
{
  this->_carcasss->push_back(carcass);
}

Carcass				*Carcasss::getCarcass(std::string const &name) const
{
  for (auto it = _carcasss->begin() ; it != _carcasss->end() ; ++it)
    if ((*it)->getName() == name)
      return (*it);
  return (NULL);
}

Carcass				*Carcasss::getCarcass(unsigned int const id) const
{
  for (auto it = _carcasss->begin() ; it != _carcasss->end() ; ++it)
    if ((*it)->getId() == id)
      return (*it);
  return (NULL);
}

/*
**
**	CarcassLoader
**
*/

CarcassLoader::CarcassLoader() :
  _carcasss(new Carcasss)
{

}

CarcassLoader::~CarcassLoader()
{
  delete _carcasss;
}

bool				CarcassLoader::serialization(Trame &trame) const
{
  bool				ret = true;

  trame[CONTENT]["CARCASSS"];
  for (auto it = _carcasss->getCarcasss().begin() ; it != _carcasss->getCarcasss().end() ; ++it)
    (*it)->serialization(trame(trame[CONTENT]["CARCASSS"][(*it)->getName()]));
  return (ret);
}

bool				CarcassLoader::deserialization(Trame &trame)
{
  bool				ret = false;
  Carcass			*carcass;

  if (trame[CONTENT].isMember("CARCASSS"))
    {
      auto			members = trame[CONTENT]["CARCASSS"].getMemberNames();

      for (auto it = members.begin() ; it != members.end() ; ++it)
	{
	  carcass = Carcass::deserialization(trame(trame[CONTENT]["CARCASSS"][*it]));
	  if (carcass)
	    {
	      carcass->setName(*it);
	      _carcasss->addCarcass(carcass);
	    }
	}
    }
  return (ret);
}

Carcasss const			&CarcassLoader::getLoaderContent() const
{
  return (*_carcasss);
}

Carcasss::value			*CarcassLoader::getValue(std::string const &name) const
{
  return (this->_carcasss->getCarcass(name));
}

Carcasss::value			*CarcassLoader::getValue(unsigned int const id) const
{
  return (this->_carcasss->getCarcass(id));
}
