//
// Carcass.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Mar 14 11:04:31 2014 laurent ansel
// Last update Fri Mar 14 15:38:31 2014 laurent ansel
//

#ifndef 		__CARCASS_HH__
# define 		__CARCASS_HH__

# include		<functional>
# include		"Database/Persistent.hh"
# include		"Entities/Stack.hh"
# include		"Entities/Ressource.hh"
# include		"Zone/Coordinate.hpp"
# include		"Entities/Level.hh"
# include		"Utility/Wrapper.hpp"

class			Carcass : public Persistent, public AEntity,
				  public ContainerWrapper<std::list<Stack<Ressource> *> >,
				  public ISerialization
{
  friend class		odb::access;

public:
  typedef iCoordinate	CarcassCoordinate;

private:
  CarcassCoordinate	*_coord;

private:
  Carcass(Carcass const &rhs);
  Carcass		&operator=(Carcass const &rhs);

public:
  Carcass();
  Carcass(std::string const &name);
  virtual ~Carcass();

  CarcassCoordinate const	&getCoord() const;
  void			setCoord(CarcassCoordinate const &coord);
  CarcassCoordinate::type const	&getX() const;
  CarcassCoordinate::type const	&getY() const;
  void			setX(CarcassCoordinate::type const &x);
  void			setY(CarcassCoordinate::type const &y);

  virtual bool		serialization(Trame &trame) const;
  static Carcass	*deserialization(Trame const &trame);
};

# ifdef	ODB_COMPILER
#  pragma db object(Carcass)
#  pragma db member(Carcass::_coord) transient
# endif

#endif
