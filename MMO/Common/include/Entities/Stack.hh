//
// Stack.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Wed Mar 12 13:49:57 2014 laurent ansel
// Last update Wed Mar 12 23:23:24 2014 laurent ansel
//

#ifndef 			__STACK_HH__
# define 			__STACK_HH__

# include			"Utility/ISerialization.hh"
# include			"Entities/AItem.hh"
# include			"Utility/ISerialization.hh"

class				Stack : public ISerialization
{
private:
  unsigned int			_id;
  AItem				*_item;
  unsigned int			_nb;

private:
  Stack(Stack const &rhs);
  Stack				&operator=(Stack const &rhs);

public:
  Stack(unsigned int const id, AItem *item = NULL, unsigned int const nb = 1);
  Stack(unsigned int const id, AItem const *item, unsigned int const nb = 1);
  virtual ~Stack();

  unsigned int			getId() const;
  void				setId(unsigned int const id);

  void				setItem(AItem *item);
  AItem				*getItem() const;

  void				setNb(unsigned int const nb);
  unsigned int			getNb() const;

  unsigned int			operator+(unsigned int const nb);
  unsigned int			operator-(unsigned int const nb);

  Stack				&operator+=(unsigned int const nb);
  Stack				&operator-=(unsigned int const nb);
  Stack				&operator/=(unsigned int const nb);

  bool				operator<=(unsigned int const nb) const;
  bool				operator>=(unsigned int const nb) const;
  bool				operator<(unsigned int const nb) const;
  bool				operator>(unsigned int const nb) const;

  bool				operator==(std::string const &name) const;
  bool				operator!=(std::string const &name) const;

  bool				operator==(unsigned int const id) const;
  bool				operator!=(unsigned int const id) const;

  operator bool() const;

  bool				empty() const;

  bool				serialization(Trame &trame) const;
  static Stack			*deserialization(Trame const &trame);
};

#endif
