//
// Guild.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Tue Feb 25 12:42:29 2014 laurent ansel
// Last update Tue Mar 11 16:14:32 2014 alexis mestag
//

#ifndef 		__GUILD_HH__
# define 		__GUILD_HH__

# include		"Database/Persistent.hh"
# include		"Utility/Nameable.hh"
# include		"Utility/ISerialization.hh"

class			Guild : public Persistent, public Nameable, public ISerialization
{
  friend class		odb::access;

private:
  Guild();

public:
  Guild(std::string const &name);
  Guild(Guild const &rhs);

  Guild		&operator=(Guild const &rhs);

public:
  virtual ~Guild();
  virtual bool		serialization(Trame &trame) const;
  static Guild		*deserialization(Trame const &trame);
};

# ifdef	ODB_COMPILER
#  pragma db object(Guild)
#  pragma db member(Guild::name) virtual(std::string) get(getName()) set(setName(?)) unique type("VARCHAR(24)")
# endif

#endif
