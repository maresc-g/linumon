//
// EffectLib.cpp for EffectLib in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Jan 30 12:41:57 2014 alexis mestag
// Last update Thu Jan 30 14:00:42 2014 alexis mestag
//

#include			"Effects/EffectLib.hh"

EffectLib::EffectLib() :
  Persistent(), Nameable(), _file(new FileSystem::File(""))
{

}

EffectLib::EffectLib(EffectLib const &rhs) :
  Persistent(rhs), Nameable(rhs), _file(new FileSystem::File(""))
{
  *this = rhs;
}

EffectLib::~EffectLib()
{
  delete _file;
}

EffectLib			&EffectLib::operator=(EffectLib const &rhs)
{
  if (this != &rhs)
    {
      this->setFile(rhs.getFile());
    }
  return (*this);
}

FileSystem::File const		&EffectLib::getFile() const
{
  return (*_file);
}

void				EffectLib::setFile(FileSystem::File const &file)
{
  *_file = file;
}
