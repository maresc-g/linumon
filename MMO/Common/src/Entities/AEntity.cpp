//
// AEntity.cpp for AEntity in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 19:53:28 2013 alexis mestag
// Last update Tue Dec  3 11:08:47 2013 alexis mestag
//

#include			"Entities/AEntity.hh"

AEntity::AEntity() :
  Id(), Nameable(""), _entityType(eEntity::NONE)
{

}

AEntity::AEntity(std::string const &name, eEntity const type) :
  Id(), Nameable(name), _entityType(type)
{

}

AEntity::AEntity(AEntity const &rhs) :
  Id(rhs), Nameable(rhs)
{
  *this = rhs;
}

AEntity::~AEntity()
{

}

AEntity				&AEntity::operator=(AEntity const &rhs)
{
  if (this != &rhs)
    {
      this->setEntityType(rhs.getEntityType());
    }
  return (*this);
}

AEntity::eEntity			AEntity::getEntityType() const
{
  return (_entityType);
}

void				AEntity::setEntityType(AEntity::eEntity const entityType)
{
  _entityType = entityType;
}
