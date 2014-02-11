//
// Stuff.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Feb  6 15:41:47 2014 laurent ansel
// Last update Tue Feb 11 14:12:03 2014 laurent ansel
//

#ifndef 		__RESSOURCE_HH__
# define 		__RESSOURCE_HH__

# include		<functional>
# include		"Entities/AItem.hh"

class			Ressource : public AItem
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
