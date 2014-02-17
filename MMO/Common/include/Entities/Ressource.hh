//
// Stuff.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Feb  6 15:41:47 2014 laurent ansel
// Last update Mon Feb 17 14:47:43 2014 antoine maitre
//

#ifndef 		__RESSOURCE_HH__
# define 		__RESSOURCE_HH__

# include		<functional>
# include		"Database/Persistent.hh"
# include		"Entities/AItem.hh"
# include		"Zone/Coordinate.hpp"

class			Ressource : public Persistent, public AItem
{
  friend class		odb::access;

  typedef iCoordinate	RessourceCoordinate;
private:

  RessourceCoordinate	*_coord;
protected:
  Ressource();
  Ressource(std::string const &name);
  Ressource(Ressource const &rhs);
  
  Ressource		&operator=(Ressource const &rhs);


public:
  virtual ~Ressource();

  int			getX() const;
  int			getY() const;
  void			setX(int const);
  void			setY(int const);
  virtual bool		serialization(Trame &trame) const;
  static Ressource	*deserialization(Trame const &trame);
};

# ifdef	ODB_COMPILER
#  pragma db object(Ressource)
#  pragma db member(Ressource::_coord) transient
# endif

#endif
