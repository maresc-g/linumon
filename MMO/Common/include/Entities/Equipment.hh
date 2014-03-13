//
// Equipment.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Feb  6 16:26:08 2014 laurent ansel
// Last update Wed Mar 12 23:14:33 2014 laurent ansel
//

#ifndef 			__EQUIPMENT_HH__
# define 			__EQUIPMENT_HH__

# include			<map>
# include			"Utility/ISerialization.hh"
# include			"Utility/Wrapper.hpp"
# include			"Entities/Stuff.hh"

class				Equipment : public ISerialization,
					    public ContainerWrapper<std::map<Stuff::eStuff, Stuff *> >
{
public:
  Equipment();
  Equipment(Equipment const &rhs);

  virtual ~Equipment();

  Equipment		&operator=(Equipment const &rhs);

  container_type const	&getStuffs() const;
  void			setStuffs(container_type const &);
  bool			addStuff(Stuff *newStuff, Stuff *&oldStuff);
  bool			addStuff(Stuff::eStuff const type, Stuff *&oldStuff);
  bool			getStuff(Stuff *&oldStuff, unsigned int const idItem);
  Stuff const		&getStuff(Stuff::eStuff const type) const;
  bool			stuffExists(Stuff::eStuff const type) const;

  virtual bool		serialization(Trame &trame) const;
  static Equipment	*deserialization(Trame const &trame);
};


#endif
