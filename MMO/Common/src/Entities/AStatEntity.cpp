//
// AStatEntity.cpp for AStatEntity in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 21:33:57 2013 alexis mestag
// Last update Tue Dec  3 13:13:10 2013 alexis mestag
//

#include			"Entities/AStatEntity.hh"

AStatEntity::AStatEntity() :
  AEntity("", eEntity::STATENTITY), _statEntityType(eStatEntity::NONE), _stats(NULL)
{

}

AStatEntity::AStatEntity(std::string const &name, AStatEntity::eStatEntity const statEntityType) :
  AEntity(name, eEntity::STATENTITY), _statEntityType(statEntityType), _stats(new Stats)
{

}

AStatEntity::AStatEntity(AStatEntity const &rhs) :
  AEntity(rhs)
{
  *this = rhs;
}

AStatEntity::~AStatEntity()
{
  delete _stats;
}

AStatEntity			&AStatEntity::operator=(AStatEntity const &rhs)
{
  if (this != &rhs)
    {
      this->setStatEntityType(rhs.getStatEntityType());
      this->setStats(new Stats(*rhs.getStats()));
    }
  return (*this);
}

AStatEntity::eStatEntity	AStatEntity::getStatEntityType() const
{
  return (_statEntityType);
}

void				AStatEntity::setStatEntityType(AStatEntity::eStatEntity const statEntityType)
{
  _statEntityType = statEntityType;
}

Stats const			*AStatEntity::getStats() const
{
  return (_stats);
}

void				AStatEntity::setStats(Stats *const stats)
{
  delete _stats;
  _stats = stats;
}
