//
// ACharacter.cpp for ACharacter in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 23:37:01 2013 alexis mestag
// Last update Mon Mar  3 20:57:20 2014 alexis mestag
//

#include			"Entities/ACharacter.hh"

ACharacter::ACharacter() :
  AStatEntity("", eStatEntity::CHARACTER), _characterType(eCharacter::NONE),
  _currentExp(0), _level(new Level), _equipment(new Equipment)
{

}

ACharacter::ACharacter(std::string const &name, ACharacter::eCharacter const characterType) :
  AStatEntity(name, eStatEntity::CHARACTER), _characterType(characterType),
  _currentExp(0), _level(new Level), _equipment(new Equipment)
{

}

ACharacter::ACharacter(ACharacter const &rhs) :
  AStatEntity(rhs), _level(new Level), _equipment(new Equipment)
{
  *this = rhs;
}

ACharacter::~ACharacter()
{
  delete _level;
  delete _equipment;
}

ACharacter			&ACharacter::operator=(ACharacter const &rhs)
{
  if (this != &rhs)
    {
      this->setCharacterType(rhs.getCharacterType());
      this->setCurrentExp(rhs.getCurrentExp());
      this->setLevelObject(rhs.getLevelObject());
      this->setEquipment(rhs.getEquipment());
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

Level::type			ACharacter::getCurrentExp() const
{
  return (_currentExp);
}

void				ACharacter::setCurrentExp(Level::type const currentExp)
{
  _currentExp = currentExp;
}

Level::type			ACharacter::getLevel() const
{
  return (_level->getLevel());
}

void				ACharacter::setLevel(Level::type const level)
{
  _level->setLevel(level);
}

Level::type			ACharacter::getExp() const
{
  return (_level->getExp());
}

void				ACharacter::setExp(Level::type const exp)
{
  _level->setExp(exp);
}

Level const			&ACharacter::getLevelObject() const
{
  return (*_level);
}

void				ACharacter::setLevelObject(Level const &level)
{
  if (!_level)
    _level = new Level(level);
  else
    *_level = level;
}

void				ACharacter::levelUp()
{
  _level->levelUp();
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
