//
// ACharacter.cpp for ACharacter in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 23:37:01 2013 alexis mestag
// Last update Mon Mar 24 16:23:03 2014 alexis mestag
//

#include			"Entities/ACharacter.hh"

ACharacter::ACharacter() :
  AStatEntity("", eStatEntity::CHARACTER), Levelable(),
  _characterType(eCharacter::NONE), _equipment(new Equipment),
  _inBattle(false)
{

}

ACharacter::ACharacter(std::string const &name, ACharacter::eCharacter const characterType) :
  AStatEntity(name, eStatEntity::CHARACTER), Levelable(),
  _characterType(characterType), _equipment(new Equipment),
  _inBattle(false)
{

}

ACharacter::ACharacter(ACharacter const &rhs) :
  AStatEntity(rhs), Levelable(rhs), _equipment(new Equipment)
{
  *this = rhs;
}

ACharacter::~ACharacter()
{
  delete _equipment;
}

ACharacter			&ACharacter::operator=(ACharacter const &rhs)
{
  if (this != &rhs)
    {
      this->setCharacterType(rhs.getCharacterType());
      this->setEquipment(rhs.getEquipment());
      this->setInBattle(rhs.isInBattle());
    }
  return (*this);
}

ACharacter::eCharacter		ACharacter::getCharacterType() const
{
  return (_characterType);
}

void				ACharacter::setCharacterType(ACharacter::eCharacter const characterType)
{
  _characterType = characterType;
}

#ifndef		CLIENT_COMPILATION
void				ACharacter::resetExp()
{
  this->setExp(this->getExperienceCurve()(this->getLevel() + 1));
  if (this->getCurrentExp() < this->getExperienceCurve()(this->getLevel()) ||
      this->getCurrentExp() >= this->getExperienceCurve()(this->getLevel()))
    this->setCurrentExp(this->getExperienceCurve()(this->getLevel()));
}
#endif

void				ACharacter::levelUp()
{
  this->setLevel(this->getLevel() + 1);
#ifndef		CLIENT_COMPILATION
  this->setExp(this->getExperienceCurve()(this->getLevel()));
  this->setOldExp(this->getExperienceCurve()(this->getLevel() - 1));
#endif
}

Equipment const			&ACharacter::getEquipment() const
{
  return (*this->_equipment);
}

void				ACharacter::setEquipment(Equipment *equipment)
{
  this->setEquipment(*equipment);
  delete equipment;
}

void				ACharacter::setEquipment(Equipment const &equipment)
{
  if (!_equipment)
    this->_equipment = new Equipment(equipment);
  else
    *this->_equipment = equipment;
}

bool				ACharacter::addStuff(Stuff *item, Stuff *&old)
{
  return (this->_equipment->addStuff(item, old));
}

bool				ACharacter::addStuff(Stuff::eStuff const item, Stuff *&old)
{
  return (this->_equipment->addStuff(item, old));
}

bool				ACharacter::getStuff(Stuff *&old, unsigned int const item)
{
  return (this->_equipment->getStuff(old, item));
}

bool				ACharacter::isInBattle() const
{
  return (_inBattle);
}

void				ACharacter::setInBattle(bool const inBattle)
{
  _inBattle = inBattle;
}

void				ACharacter::enterBattle()
{
  this->setInBattle(true);
}

void				ACharacter::leaveBattle()
{
  this->setInBattle(false);
}
