//
// Equipment.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Feb  6 16:26:08 2014 laurent ansel
// Last update Sat Feb 15 20:42:24 2014 laurent ansel
//

#ifndef 			__EQUIPMENT_HH__
# define 			__EQUIPMENT_HH__

#include			<map>
#include			"Entities/Stuff.hh"
#include			"Utility/ISerialization.hh"

class				Equipment : public ISerialization
{
private:
  std::map<Stuff::eStuff, Stuff *>	_stuffs;

public:
  Equipment();
  virtual ~Equipment();

  Equipment(Equipment const &rhs);

  Equipment		&operator=(Equipment const &rhs);

  std::map<Stuff::eStuff, Stuff *> const	&getStuffs() const;
  void			setStuffs(std::map<Stuff::eStuff, Stuff *> const &);
  bool			addStuff(Stuff *newStuff, Stuff *&oldStuff);
  bool			addStuff(Stuff::eStuff const type, Stuff *&oldStuff);
  bool			getStuff(Stuff *&oldStuff, unsigned int const idItem);

  virtual bool		serialization(Trame &trame) const;
  static Equipment	*deserialization(Trame const &trame);
};

#endif
