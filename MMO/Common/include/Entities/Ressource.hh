//
// Stuff.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Feb  6 15:41:47 2014 laurent ansel
// Last update Mon Feb 17 15:06:38 2014 laurent ansel
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

public:
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

  void				setCoord(RessourceCoordinate const &coord);
  RessourceCoordinate::type const	&getX() const;
  RessourceCoordinate::type const	&getY() const;
  void			setX(RessourceCoordinate::type const &x);
  void			setY(RessourceCoordinate::type const &y);
  virtual bool		serialization(Trame &trame) const;
  static Ressource	*deserialization(Trame const &trame);
};

# ifdef	ODB_COMPILER
#  pragma db object(Ressource)
#  pragma db member(Ressource::_coord) transient
#  pragma db member(Ressource::_x) virtual(Ressource::RessourceCoordinate::type) get(_coord->getX()) set(_coord->setX(?))
#  pragma db member(Ressource::_y) virtual(Ressource::RessourceCoordinate::type) get(_coord->getY()) set(_coord->setY(?))
# endif

#endif
