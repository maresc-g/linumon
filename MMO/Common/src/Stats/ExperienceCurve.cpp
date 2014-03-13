//
// ExperienceCurve.cpp for ExperienceCurve in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Mar 12 14:16:09 2014 alexis mestag
// Last update Wed Mar 12 22:00:04 2014 alexis mestag
//

#include				<stdexcept>
#include				"DynamicLibrary/DynamicLibrary.hh"
#include				"Mutex/Mutex.hpp"
#include				"Stats/ExperienceCurve.hh"

ExperienceCurve::ExperienceCurve() :
  Persistent(), Nameable(), _dl(new DynamicLibrary("")), _f(NULL), _mtx(new Mutex)
{
  _mtx->init();
}

ExperienceCurve::ExperienceCurve(std::string const &name, std::string const &path) :
  Persistent(), Nameable(name), _dl(new DynamicLibrary("")), _f(NULL), _mtx(new Mutex)
{
  _mtx->init();
  this->setPath(path);
}

ExperienceCurve::ExperienceCurve(ExperienceCurve const &rhs) :
  Persistent(rhs), Nameable(rhs), _dl(new DynamicLibrary("")), _f(NULL), _mtx(new Mutex)
{
  _mtx->init();
  *this = rhs;
}

ExperienceCurve::~ExperienceCurve()
{
  _mtx->destroy();
  delete _mtx;
  delete _f;
  delete _dl;
}

ExperienceCurve				&ExperienceCurve::operator=(ExperienceCurve const &rhs)
{
  if (this != &rhs)
    {
      this->setPath(rhs.getPath());
    }
  return (*this);
}

Level::type				ExperienceCurve::operator()(Level::type const level) const
{
  return (this->getExperienceFunction()(level));
}

std::string const			&ExperienceCurve::getPath() const
{
  return (_dl->getPath());
}

void					ExperienceCurve::setPath(std::string const &path)
{
  if (this->getPath() != path) {
    _mtx->lock();
    _dl->setPath(path);
    IExperienceFunction		*(*symbol)() = NULL;

    if (_dl->load()) {
      symbol = reinterpret_cast<IExperienceFunction *(*)()>(_dl->getSymbol("getInstance"));
      if (symbol)
	_f = symbol();
    }
    else if (!symbol)
      throw std::runtime_error("Cannot load or get symbol from " + this->getPath());
    _mtx->unlock();
  }
}

IExperienceFunction const		&ExperienceCurve::getExperienceFunction() const
{
  if (!_f)
    throw std::runtime_error("Cannot load or get symbol from " + this->getPath());
  return (*_f);
}
