//
// EffectLib.cpp for EffectLib in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Jan 30 12:41:57 2014 alexis mestag
// Last update Wed Feb  5 13:48:24 2014 alexis mestag
//

#include			"Effects/EffectLib.hh"

EffectLib::EffectLib() :
  Persistent(), Nameable(), _dl(new DynamicLibrary(""))
{

}

EffectLib::EffectLib(std::string const &name, std::string const &path) :
  Persistent(), Nameable(name), _dl(new DynamicLibrary(path))
{

}

EffectLib::EffectLib(EffectLib const &rhs) :
  Persistent(rhs), Nameable(rhs), _dl(new DynamicLibrary(""))
{
  *this = rhs;
}

EffectLib::~EffectLib()
{
  delete _dl;
}

EffectLib			&EffectLib::operator=(EffectLib const &rhs)
{
  if (this != &rhs)
    {
      this->setPath(rhs.getPath());
    }
  return (*this);
}

std::string const		&EffectLib::getPath() const
{
  return (_dl->getPath());
}

void				EffectLib::setPath(std::string const &path)
{
  _dl->setPath(path);
}

IEffect				*EffectLib::getEffect()
{
  static IEffect		*(*symbol)() = NULL;
  IEffect			*ret = NULL;

  if (!symbol || !_dl->isLoaded())
    {
      if (_dl->load())
	symbol = reinterpret_cast<IEffect *(*)()>(_dl->getSymbol(""));
    }
  if (symbol)
    ret = symbol();
  return (ret);
}
