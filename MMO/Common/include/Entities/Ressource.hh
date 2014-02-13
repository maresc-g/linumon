//
// Stuff.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Feb  6 15:41:47 2014 laurent ansel
// Last update Tue Feb 11 16:07:41 2014 alexis mestag
//

#ifndef 		__RESSOURCE_HH__
# define 		__RESSOURCE_HH__

# include		<functional>
# include		"Database/Persistent.hh"
# include		"Entities/AItem.hh"

class			Ressource : public Persistent, public AItem
{
  friend class		odb::access;

private:


protected:
  Ressource();
  Ressource(std::string const &name);
  Ressource(Ressource const &rhs);

  Ressource		&operator=(Ressource const &rhs);


public:
  virtual ~Ressource();

  virtual bool		serialization(Trame &trame) const;
  static Ressource	*deserialization(Trame const &trame);
};

# ifdef	ODB_COMPILER
#  pragma db object(Ressource)
# endif

#endif
