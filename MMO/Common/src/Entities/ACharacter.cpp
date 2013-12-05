//
// ACharacter.cpp for ACharacter in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 23:37:01 2013 alexis mestag
// Last update Tue Dec  3 13:43:12 2013 alexis mestag
//

#include			"Entities/ACharacter.hh"

ACharacter::ACharacter() :
  AStatEntity("", eStatEntity::CHARACTER), _characterType(eCharacter::NONE)
{

}

ACharacter::ACharacter(std::string const &name, ACharacter::eCharacter const characterType) :
  AStatEntity(name, eStatEntity::CHARACTER), _characterType(characterType)
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
