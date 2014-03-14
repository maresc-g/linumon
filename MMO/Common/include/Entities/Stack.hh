//
// Stack.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Wed Mar 12 13:49:57 2014 laurent ansel
// Last update Fri Mar 14 21:58:56 2014 laurent ansel
//

#ifndef 			__STACK_HH__
# define 			__STACK_HH__

#include			<sstream>
# include			"Entities/AItem.hh"
# include			"Utility/ISerialization.hh"

AItem				*getItemLoader(std::string const &name);

template <typename T = AItem>
class				Stack : public ISerialization
{
private:
  unsigned int			_id;
  T				*_item;
  unsigned int			_nb;

private:
  Stack(Stack<T> const &rhs)
  {
    *this = rhs;
  }

  Stack<T>			&operator=(Stack<T> const &rhs)
  {
    if (this != &rhs)
      {
	this->setItem(rhs.getItem());
	this->setNb(rhs.getNb());
      }
    return (*this);
  }

public:
  Stack(unsigned int const id, T *item = NULL, unsigned int const nb = 0):
    _id(id),
    _item(item),
    _nb(nb)
  {
  }

  Stack(unsigned int const id, T const *item, unsigned int const nb = 0):
    _id(id),
    _item(const_cast<AItem *>(item)),
    _nb(nb)
  {
  }

  virtual ~Stack()
  {
  }

  unsigned int			getId() const
  {
    return (_id);
  }

  void				setId(unsigned int const id)
  {
    _id = id;
  }

  void				setItem(T *item)
  {
    _item = item;
  }

  T				*getItem() const
  {
    return (_item);
  }


  void				setNb(unsigned int const nb)
  {
    _nb = nb;
  }

  unsigned int			getNb() const
  {
    return (_nb);
  }

  unsigned int			operator+(unsigned int const nb)
  {
    return (_nb + nb);
  }

  unsigned int			operator-(unsigned int const nb)
  {
    return (_nb - nb);
  }

  Stack<T>			&operator+=(unsigned int const nb)
  {
    _nb += nb;
    return (*this);
  }

  Stack<T>			&operator-=(unsigned int const nb)
  {
    _nb -= nb;
    return (*this);
  }

  Stack<T>			&operator/=(unsigned int const nb)
  {
    if (nb)
      _nb /= nb;
    return (*this);
  }

  bool				operator<=(unsigned int const nb) const
  {
    return (_nb <= nb);
  }

  bool				operator>=(unsigned int const nb) const
  {
    return (_nb >= nb);
  }

  bool				operator<(unsigned int const nb) const
  {
    return (_nb < nb);
  }

  bool				operator>(unsigned int const nb) const
  {
    return (_nb > nb);
  }

  bool				operator==(std::string const &name) const
  {
    if (_item)
      return (_item->getName() == name);
    return (false);
  }

  bool				operator!=(std::string const &name) const
  {
    if (_item)
      return (_item->getName() != name);
    return (true);
  }

  bool				operator==(unsigned int const id) const
  {
    if (_item)
      return (_item->getId() == id);
    return (false);
  }

  bool				operator!=(unsigned int const id) const
  {
    if (_item)
      return (_item->getId() != id);
    return (true);
  }

  operator bool() const
  {
    return (empty());
  }

  bool				empty() const
  {
    if (_nb == 0)
      return (true);
    return (false);
  }


  bool				serialization(Trame &trame) const
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

  static Stack<T>		*deserialization(Trame const &trame)
  {
    Stack<T>			*stack = new Stack<T>(0);
    auto			item = trame.getMemberNames();

    for (auto it = item.begin() ; it != item.end() ; ++it)
      {
	stack->setItem(getItemLoader(*it));
	stack->setNb(trame[*it].asUInt());
      }
    return (stack);
  }
};

// # ifdef	ODB_COMPILER
// #  pragma db object(Stack)
// #  pragma db member(StackRessource::_type) transient
// # endif

#endif
