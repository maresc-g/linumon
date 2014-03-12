//
// Heal.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb 21 12:49:18 2014 laurent ansel
// Last update Tue Mar 11 16:14:41 2014 alexis mestag
//

#ifndef 		__HEAL_HH__
# define		__HEAL_HH__

# include		"Database/Persistent.hh"
# include		"Entities/PNJ.hh"
# include		"Utility/ISerialization.hh"
# include		"Entities/Digitaliser.hh"

class			Heal : public Persistent, public PNJ
{
  friend class		odb::access;

private:
  Heal();

  bool			heal(Digitaliser const &digitaliser) const;

public:
  Heal(Heal const &rhs);
  virtual ~Heal();

  Heal			&operator=(Heal const &rhs);

  virtual bool		action(Player *player);

  virtual bool		serialization(Trame &trame) const;
  static Heal		*deserialization(Trame const &trame, bool const client = true);
};

# ifdef	ODB_COMPILER
#  pragma db object(Heal)
#  pragma db member(Heal::name) virtual(std::string) get(getName()) set(setName(?)) unique type("VARCHAR(24)")
#endif

#endif
