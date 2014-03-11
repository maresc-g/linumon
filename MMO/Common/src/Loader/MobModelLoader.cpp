//
// MobModelLoader.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Wed Mar  5 12:21:17 2014 laurent ansel
// Last update Mon Mar 10 19:11:54 2014 alexis mestag
//

#ifndef CLIENT_COMPILATION
# include			"Entities/MobModel-odb.hxx"
# include			"Database/Repositories/Repository.hpp"
#endif
#include			"Loader/MobModelLoader.hh"

/*
**
**	MobModels
**
*/

MobModels::MobModels() :
  _mobModels(new std::list<MobModel *>)
{
#ifndef CLIENT_COMPILATION
  Repository<MobModel>		*mm = &Database::getRepository<MobModel>();

  *_mobModels = mm->getAll();
#endif
}

MobModels::~MobModels()
{
  for (auto it = _mobModels->begin() ; it != _mobModels->end() ; ++it)
    delete *it;
  delete _mobModels;
}

std::list<MobModel *> const	&MobModels::getMobModels() const
{
  return (*this->_mobModels);
}

void				MobModels::addMobModel(MobModel *mob)
{
  this->_mobModels->push_back(mob);
}

MobModel			*MobModels::getMobModel(std::string const &name) const
{
  for (auto it = _mobModels->begin() ; it != _mobModels->end() ; ++it)
    if ((*it)->getName() == name)
      return (*it);
  return (NULL);
}

MobModel			*MobModels::getMobModel(unsigned int const id) const
{
  for (auto it = _mobModels->begin() ; it != _mobModels->end() ; ++it)
    if ((*it)->getId() == id)
      return (*it);
  return (NULL);
}

/*
**
**	MobModelLoader
**
*/

MobModelLoader::MobModelLoader() :
  _mobModels(new MobModels)
{

}

MobModelLoader::~MobModelLoader()
{
  delete _mobModels;
}

bool				MobModelLoader::serialization(Trame &trame) const
{
  bool				ret = true;

  trame[CONTENT]["MOBMODELS"];
  for (auto it = _mobModels->getMobModels().begin() ; it != _mobModels->getMobModels().end() ; ++it)
    (*it)->serialization(trame(trame[CONTENT]["MOBMODELS"][(*it)->getName()]));
  return (ret);
}

bool				MobModelLoader::deserialization(Trame &trame)
{
  bool				ret = false;
  MobModel			*mob;

  if (trame[CONTENT].isMember("MOBMODELS"))
    {
      auto			members = trame[CONTENT]["MOBMODELS"].getMemberNames();

      for (auto it = members.begin() ; it != members.end() ; ++it)
	{
	  mob = MobModel::deserialization(trame(trame[CONTENT]["MOBMODELS"][*it]));
	  if (mob)
	    {
	      mob->setName(*it);
	      _mobModels->addMobModel(mob);
	    }
	}
    }
  return (ret);
}

MobModels const			&MobModelLoader::getLoaderContent() const
{
  return (*_mobModels);
}

MobModels::value		*MobModelLoader::getValue(std::string const &name) const
{
  return (this->_mobModels->getMobModel(name));
}

MobModels::value		*MobModelLoader::getValue(unsigned int const id) const
{
  return (this->_mobModels->getMobModel(id));
}
