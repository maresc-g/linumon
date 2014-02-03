//
// TalentTree.cpp for TalentTree in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Fri Jan 31 12:50:05 2014 alexis mestag
// Last update Fri Jan 31 15:33:58 2014 alexis mestag
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
