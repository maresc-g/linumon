//
// Stuff.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Feb  6 15:41:47 2014 laurent ansel
// Last update Mon Feb 24 19:51:57 2014 laurent ansel
//

#ifndef 		__RESSOURCE_HH__
# define 		__RESSOURCE_HH__

# include		<functional>
# include		"Database/Persistent.hh"
# include		"Entities/AItem.hh"
# include		"Zone/Coordinate.hpp"
# include		"Entities/Level.hh"

class			Ressource : public Persistent, public AItem
{
  friend class		odb::access;

public:
  typedef iCoordinate	RessourceCoordinate;

private:
  RessourceCoordinate	*_coord;
  Level			_level;

protected:
  Ressource(std::string const &name);

public:
  Ressource();

  Ressource(Ressource const &rhs);

  virtual ~Ressource();

  Ressource		&operator=(Ressource const &rhs);

  RessourceCoordinate const	&getCoord() const;
  void				setCoord(RessourceCoordinate const &coord);
  RessourceCoordinate::type const	&getX() const;
  RessourceCoordinate::type const	&getY() const;
  void			setX(RessourceCoordinate::type const &x);
  void			setY(RessourceCoordinate::type const &y);


  void			setLevel(Level const &level);
  Level const		&getLevel() const;

  virtual bool		serialization(Trame &trame) const;
  static Ressource	*deserialization(Trame const &trame, bool const client = true);
};

# ifdef	ODB_COMPILER
#  pragma db object(Ressource)
#  pragma db member(Ressource::_coord) transient
# endif

#endif
