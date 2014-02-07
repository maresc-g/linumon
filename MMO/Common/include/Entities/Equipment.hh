//
// Equipment.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Feb  6 16:26:08 2014 laurent ansel
// Last update Thu Feb  6 16:37:25 2014 laurent ansel
//

#ifndef 			__EQUIPMENT_HH__
# define 			__EQUIPMENT_HH__

#include			<list>
#include			"Entities/Stuff.hh"
#include			"Utility/ISerialization.hh"

class				Equipment : public ISerialization
{
private:
  std::list<Stuff *>		*_stuffs;

public:
  Equipment();
  virtual ~Equipment();

  Equipment(Equipment const &rhs);

  Equipment		&operator=(Equipment const &rhs);

  std::list<Stuff *> const	&getStuffs() const;

  void			setStuffs(std::list<Stuff *> const &);

  virtual bool		serialization(Trame &trame) const;
  static Equipment	*deserialization(Trame const &trame);
};

#endif
