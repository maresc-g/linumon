//
// TalentTreeLoader.cpp for TalentTreeLoader in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Mar 19 13:44:49 2014 alexis mestag
// Last update Wed Mar 19 17:35:49 2014 alexis mestag
//

#ifndef		CLIENT_COMPILATION
# include			"Stats/TalentTree-odb.hxx"
# include			"Database/Repositories/Repository.hpp"
#endif
#include			<algorithm>
#include			<functional>
#include			"Loader/TalentTreeLoader.hh"

TalentTrees::TalentTrees() :
  _talentTrees(new std::list<TalentTree *>)  
{
#ifndef		CLIENT_COMPILATION
  Repository<TalentTree>	&rtt = Database::getRepository<TalentTree>();
  *_talentTrees = rtt.getAll();
#endif
}

TalentTrees::~TalentTrees()
{
  delete _talentTrees;
}

std::list<TalentTree *> const	&TalentTrees::getTalentTrees() const
{
  return (*_talentTrees);
}

void				TalentTrees::addTalentTree(TalentTree *talentTree)
{
  _talentTrees->push_back(talentTree);
}

TalentTree			*TalentTrees::getTalentTree(std::string const &name) const
{
  std::function<bool(TalentTree *)>	talentTreeSeeker = [&](TalentTree *tt) -> bool {
    return (tt->getName() == name);
  };
  auto					it = std::find_if(_talentTrees->begin(), _talentTrees->end(), talentTreeSeeker);
  TalentTree				*ret = NULL;

  if (it != _talentTrees->end())
    ret = *it;
  return (ret);
}

TalentTree			*TalentTrees::getTalentTree(unsigned int const id) const
{
  std::function<bool(TalentTree *)>	talentTreeSeeker = [&](TalentTree *tt) -> bool {
    return (tt->getPersistentId() == id);
  };
  auto					it = std::find_if(_talentTrees->begin(), _talentTrees->end(), talentTreeSeeker);
  TalentTree				*ret = NULL;

  if (it != _talentTrees->end())
    ret = *it;
  return (ret);
}

TalentTreeLoader::TalentTreeLoader() :
  _talentTrees(new TalentTrees)
{

}

TalentTreeLoader::~TalentTreeLoader()
{
  delete _talentTrees;
}

bool				TalentTreeLoader::serialization(Trame &trame) const
{
  trame[CONTENT]["TALENTTREES"];
  for (auto it = _talentTrees->getTalentTrees().begin() ;
  it != _talentTrees->getTalentTrees().end() ; ++it)
    (*it)->serialization(trame(trame[CONTENT]["TALENTTREES"][(*it)->getName()]));
  return (true);
}

bool				TalentTreeLoader::deserialization(Trame &trame)
{
  TalentTree			*talentTree;

  if (trame[CONTENT].isMember("TALENTTREES"))
    {
      auto			members = trame[CONTENT]["TALENTTREES"].getMemberNames();

      for (auto it = members.begin() ; it != members.end() ; ++it) {
	talentTree = TalentTree::deserialization(trame(trame[CONTENT]["TALENTTREES"][*it]));
	talentTree->setName(*it);
	_talentTrees->addTalentTree(talentTree);
      }
    }
  return (true);
}

TalentTrees const		&TalentTreeLoader::getLoaderContent() const
{
  return (*_talentTrees);
}

TalentTree			*TalentTreeLoader::getValue(std::string const &name) const
{
  return (_talentTrees->getTalentTree(name));
}

TalentTree			*TalentTreeLoader::getValue(unsigned int const id) const
{
  return (_talentTrees->getTalentTree(id));
}
