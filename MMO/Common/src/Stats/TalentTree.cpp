//
// TalentTree.cpp for TalentTree in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Fri Jan 31 12:50:05 2014 alexis mestag
// Last update Fri Feb 28 13:49:59 2014 laurent ansel
//

#include			"Stats/TalentTree.hh"

TalentTree::TalentTree() :
  Persistent(), Nameable(), _talent(NULL)
{

}

TalentTree::TalentTree(std::string const &name) :
  Persistent(), Nameable(name), _talent(NULL)
{

}

TalentTree::TalentTree(TalentTree const &rhs) :
  Persistent(rhs), Nameable(rhs), _talent(NULL)
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
      this->setTalent(rhs.getTalent());
    }
  return (*this);
}

TalentModel const		&TalentTree::getTalent() const
{
  return (*_talent);
}

void				TalentTree::setTalent(TalentModel const &talent)
{
  _talent = &talent;
}

bool				TalentTree::serialization(Trame &trame) const
{
  bool				ret = true;

  this->_talent->serialization(trame(trame["TREE"]));
  return (ret);
}

TalentTree			*TalentTree::deserialization(Trame const &trame)
{
  TalentTree			*talentTree = NULL;

  if (trame.isMember("TREE"))
    {
      talentTree = new TalentTree;
      talentTree->setTalent(*TalentModel::deserialization(trame(trame["TREE"])));
    }
  return (talentTree);
}
