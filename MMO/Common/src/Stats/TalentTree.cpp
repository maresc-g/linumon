//
// TalentTree.cpp for TalentTree in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Fri Jan 31 12:50:05 2014 alexis mestag
// Last update Wed Mar 19 17:53:21 2014 alexis mestag
//

#include			<sstream>
#include			"Stats/TalentTree.hh"
#include			"Loader/LoaderManager.hh"

TalentTree::TalentTree() :
  Persistent(), Nameable()
{

}

TalentTree::TalentTree(std::string const &name) :
  Persistent(), Nameable(name)
{

}

TalentTree::TalentTree(TalentTree const &rhs) :
  Persistent(rhs), Nameable(rhs)
{
  *this = rhs;
}

TalentTree::~TalentTree()
{

}

TalentTree			&TalentTree::operator=(TalentTree const &rhs)
{
  if (this != &rhs)
    {
      this->setTalents(rhs.getTalents());
    }
  return (*this);
}

std::list<TalentModel const *> const	&TalentTree::getTalents() const
{
  return (_talents);
}

void				TalentTree::setTalents(std::list<TalentModel const *> const &talents)
{
  _talents = talents;
}

bool				TalentTree::serialization(Trame &trame) const
{
  bool				ret = true;
  std::ostringstream		str;
  unsigned int			nb = 0;

  for (auto it = this->getTalents().begin() ; it != this->getTalents().end() ; ++it) {
    str << nb;
    trame["TALENTS"][str.str()] = (*it)->getName();
    str.str("");
    nb++;
  }
  return (ret);
}

TalentTree			*TalentTree::deserialization(Trame const &trame)
{
  TalentTree			*talentTree = NULL;

  auto				members = trame["TALENTS"].getMemberNames();
  std::list<TalentModel const *>	talents;
  TalentModel const			*talent;

  talentTree = new TalentTree;
  for (auto it = members.begin() ; it != members.end() ; ++it) {
    // std::cerr << "Passing in for statement" << std::endl;
    talent = (**LoaderManager::getInstance()
	      ->getTalentModelLoader())->getValue(trame["TALENTS"][*it].asString());
    if (talent)
      talents.push_back(talent);
    // else
    //   std::cerr << "\tTalent is null" << std::endl;
    talentTree->setTalents(talents);
  }
  return (talentTree);
}
