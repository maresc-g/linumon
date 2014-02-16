//
// ACharacter.cpp for ACharacter in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 23:37:01 2013 alexis mestag
// Last update Sat Feb 15 20:47:09 2014 laurent ansel
//

#include			"Entities/ACharacter.hh"

ACharacter::ACharacter() :
  AStatEntity("", eStatEntity::CHARACTER), _characterType(eCharacter::NONE),
  _currentExp(0), _equipment(NULL)
{

}

ACharacter::ACharacter(std::string const &name, ACharacter::eCharacter const characterType) :
  AStatEntity(name, eStatEntity::CHARACTER), _characterType(characterType), _currentExp(0),
  _equipment(NULL)
{

}

ACharacter::ACharacter(ACharacter const &rhs) :
  AStatEntity(rhs)
{
  *this = rhs;
}

ACharacter::~ACharacter()
{

}

ACharacter			&ACharacter::operator=(ACharacter const &rhs)
{
  if (this != &rhs)
    {
      this->setCharacterType(rhs.getCharacterType());
      this->setCurrentExp(rhs.getCurrentExp());
      this->setLevel(rhs.getLevel());
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

int				ACharacter::getCurrentExp() const
{
  return (_currentExp);
}

void				ACharacter::setCurrentExp(int const currentExp)
{
  _currentExp = currentExp;
}

Level const			&ACharacter::getLevel() const
{
  return (_level);
}

void				ACharacter::setLevel(Level const &level)
{
  _level = level;
}

void				ACharacter::levelUp()
{
  _level.levelUp();
}

Equipment const			&ACharacter::getEquipment() const
{
  return (*this->_equipment);
}

void				ACharacter::setEquipment(Equipment *equipment)
{
  this->_equipment = equipment;
}

bool				ACharacter::addStuff(Stuff *item, Stuff *&old) const
{
  return (this->_equipment->addStuff(item, old));
}

bool				ACharacter::addStuff(Stuff::eStuff const item, Stuff *&old) const
{
  return (this->_equipment->addStuff(item, old));
}

bool				ACharacter::getStuff(Stuff *&old, unsigned int const item) const
{
  return (this->_equipment->getStuff(old, item));
}
