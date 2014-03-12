//
// Stack.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Wed Mar 12 14:05:11 2014 laurent ansel
// Last update Wed Mar 12 16:14:49 2014 laurent ansel
//

#include				<sstream>
#include				"Entities/Stack.hh"
#include				"Loader/LoaderManager.hh"

Stack::Stack(unsigned int const id, AItem *item, unsigned int const nb):
  _id(id),
  _item(item),
  _nb(nb)
{

}

Stack::Stack(Stack const &rhs)
{
  *this = rhs;
}

Stack				&Stack::operator=(Stack const &rhs)
{
  if (this != &rhs)
    {
      this->setItem(rhs.getItem());
      this->setNb(rhs.getNb());
    }
  return (*this);
}

Stack::~Stack()
{

}

void				Stack::setId(unsigned int const id)
{
  _id = id;
}

unsigned int			Stack::getId() const
{
  return (_id);
}

void				Stack::setItem(AItem *item)
{
  _item = item;
}

AItem				*Stack::getItem() const
{
  return (_item);
}

void				Stack::setNb(unsigned int const nb)
{
  _nb = nb;
}

unsigned int			Stack::getNb() const
{
  return (_nb);
}

unsigned int			Stack::operator+(unsigned int const nb)
{
  return (_nb + nb);
}

unsigned int			Stack::operator-(unsigned int const nb)
{
  return (_nb - nb);
}

Stack				&Stack::operator+=(unsigned int const nb)
{
  _nb += nb;
  return (*this);
}

Stack				&Stack::operator-=(unsigned int const nb)
{
  _nb -= nb;
  return (*this);
}

Stack				&Stack::operator/=(unsigned int const nb)
{
  if (nb)
    _nb /= nb;
  return (*this);
}

bool				Stack::operator>=(unsigned int const nb) const
{
  return (_nb >= nb);
}

bool				Stack::operator<=(unsigned int const nb) const
{

  return (_nb <= nb);
}

bool				Stack::operator>(unsigned int const nb) const
{
  return (_nb > nb);
}

bool				Stack::operator<(unsigned int const nb) const
{
  return (_nb < nb);
}

bool				Stack::operator==(std::string const &name) const
{
  if (_item)
    return (_item->getName() == name);
  return (false);
}

bool				Stack::operator!=(std::string const &name) const
{
  if (_item)
    return (_item->getName() != name);
  return (true);
}

bool				Stack::operator==(unsigned int const id) const
{
  if (_item)
    return (_item->getId() == id);
  return (false);
}

bool				Stack::operator!=(unsigned int const id) const
{
  if (_item)
    return (_item->getId() != id);
  return (true);
}

bool				Stack::empty() const
{
  if (_nb == 0)
    return (true);
  return (false);
}

Stack::operator bool() const
{
  return (empty());
}

bool				Stack::serialization(Trame &trame) const
{
  bool				ret = false;
  std::ostringstream		str;

  if (_item)
    {
      str << _id;
      trame[str.str()][_item->getName()] = _nb;
      ret = true;
    }
  return (ret);
}

Stack				*Stack::deserialization(Trame const &trame)
{
  Stack				*stack = new Stack(0);
  auto				item = trame.getMemberNames();

  for (auto it = item.begin() ; it != item.end() ; ++it)
    {
      stack->setItem(LoaderManager::getInstance()->getItemLoader(*it));
      stack->setNb(trame[*it].asUInt());
    }
  return (stack);
}
