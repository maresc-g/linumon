//
// TalentModelLoader.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Mar  7 15:56:40 2014 laurent ansel
// Last update Wed Mar 19 17:20:39 2014 alexis mestag
//

#ifndef CLIENT_COMPILATION
# include			"Stats/TalentModel-odb.hxx"
# include			"Database/Repositories/Repository.hpp"
#endif
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
  for (auto it = _talentModels->getTalentModels().begin() ;
       it != _talentModels->getTalentModels().end() ; ++it)
    (*it)->serialization(trame(trame[CONTENT]["TALENTMODELS"][(*it)->getName()]));
  return (ret);
}

bool				TalentModelLoader::deserialization(Trame &trame)
{
  auto				members = trame[CONTENT]["TALENTMODELS"].getMemberNames();
  TalentModel			*tm;

  for (auto it = members.begin() ; it != members.end() ; ++it)
    {
      tm = TalentModel::deserialization(trame(trame[CONTENT]["TALENTMODELS"][*it]));
      _talentModels->addTalentModel(tm);
    }

  TalentModel			*tmp;

  for (auto it = _talentModels->getTalentModels().begin() ;
       it != _talentModels->getTalentModels().end() ; ++it)
    {
      tmp = NULL;
      if (trame[CONTENT]["TALENTMODELS"][(*it)->getName()].isMember("PARENT"))
	tmp = this->getValue(trame[CONTENT]["TALENTMODELS"][(*it)->getName()]["PARENT"].asString());
      (*it)->setParent(tmp);

      auto	talents = trame[CONTENT]["TALENTMODELS"][(*it)->getName()]["TALENTS"].getMemberNames();

      for (auto jt = talents.begin() ; jt != talents.end() ; ++jt)
	{
	  tmp = this->getValue(trame[CONTENT]["TALENTMODELS"][(*it)->getName()]["TALENTS"][*jt].asString());
	  if (tmp)
	    (*it)->addTalent(*tmp);
	}
    }

  return (true);  
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
