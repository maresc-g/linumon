//
// TalentModelLoader.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Mar  7 15:56:40 2014 laurent ansel
// Last update Fri Mar  7 21:14:01 2014 laurent ansel
//

#ifndef CLIENT_COMPILATION
#include			"Stats/TalentModel-odb.hxx"
#endif
#include			"Database/Repositories/Repository.hpp"
#include			"Loader/TalentModelLoader.hh"

/*
**
**	TalentModels
**
*/

TalentModels::TalentModels() :
  _talentModels(new std::list<TalentModel *>)
{
#ifndef CLIENT_COMPILATION
  Repository<TalentModel>		*mm = &Database::getRepository<TalentModel>();

  *_talentModels = mm->getAll();
#endif
}

TalentModels::~TalentModels()
{
  for (auto it = _talentModels->begin() ; it != _talentModels->end() ; ++it)
    delete *it;
  delete _talentModels;
}

std::list<TalentModel *> const	&TalentModels::getTalentModels() const
{
  return (*this->_talentModels);
}

void				TalentModels::addTalentModel(TalentModel *talentModel)
{
  this->_talentModels->push_back(talentModel);
}

TalentModel				*TalentModels::getTalentModel(std::string const &name) const
{
  for (auto it = _talentModels->begin() ; it != _talentModels->end() ; ++it)
    if ((*it)->getName() == name)
      return (*it);
  return (NULL);
}

TalentModel				*TalentModels::getTalentModel(unsigned int const) const
{
  return (NULL);
}

/*
**
**	TalentModelLoader
**
*/

TalentModelLoader::TalentModelLoader() :
  _talentModels(new TalentModels)
{

}

TalentModelLoader::~TalentModelLoader()
{
  delete _talentModels;
}

bool				TalentModelLoader::serialization(Trame &trame) const
{
  bool				ret = true;

  trame[CONTENT]["TALENTMODELS"];
  for (auto it = _talentModels->getTalentModels().begin() ; it != _talentModels->getTalentModels().end() ; ++it)
    (*it)->serialization(trame(trame[CONTENT]["TALENTMODELS"][(*it)->getName()]));
  return (ret);
}

bool				TalentModelLoader::deserializationTreeModel(Trame &trame)
{
  bool				ret = true;
  auto				members = trame[CONTENT]["TALENTMODELS"].getMemberNames();
  TalentModel			*talentModel;

  for (auto it = members.begin() ; it != members.end() ; ++it)
    {
      talentModel = _talentModels->getTalentModel(*it);
      if (talentModel)
	talentModel->deserializationTreeModel(trame(trame[CONTENT]["TALENTMODELS"][*it]));
    }
  return (ret);
}

bool				TalentModelLoader::deserialization(Trame &trame)
{
  bool				ret = true;
  TalentModel			*talentModel;

  if (trame[CONTENT].isMember("TALENTMODELS"))
    {
      auto			members = trame[CONTENT]["TALENTMODELS"].getMemberNames();

      for (auto it = members.begin() ; it != members.end() ; ++it)
	{
	  talentModel = TalentModel::deserialization(trame(trame[CONTENT]["TALENTMODELS"][*it]));
	  if (talentModel)
	    {
	      talentModel->setName(*it);
	      _talentModels->addTalentModel(talentModel);
	    }
	}
      ret = this->deserializationTreeModel(trame);
    }
  return (ret);
}

TalentModels const			&TalentModelLoader::getLoaderContent() const
{
  return (*_talentModels);
}

TalentModels::value			*TalentModelLoader::getValue(std::string const &name) const
{
  return (this->_talentModels->getTalentModel(name));
}

TalentModels::value			*TalentModelLoader::getValue(unsigned int const id) const
{
  return (this->_talentModels->getTalentModel(id));
}
