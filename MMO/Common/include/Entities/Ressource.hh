//
// Stuff.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Feb  6 15:41:47 2014 laurent ansel
// Last update Tue Mar 18 23:48:26 2014 alexis mestag
//

#ifndef 		__RESSOURCE_HH__
# define 		__RESSOURCE_HH__

# include		<functional>
# include		"Database/Persistent.hh"
# include		"Entities/AItem.hh"
# include		"Zone/Coordinate.hpp"
# include		"Entities/Levelable.hh"

class			Ressource : public Persistent, public AItem
{
  friend class		odb::access;

public:
  typedef iCoordinate	RessourceCoordinate;

private:
  RessourceCoordinate	*_coord;
  Levelable::type	_level;
  Levelable::type	_exp;
  bool			_visible;
  bool			_gather;

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

  Levelable::type	getLevel() const;
  void			setLevel(Levelable::type const level);

  Levelable::type	getExp() const;
  void			setExp(Levelable::type const exp);

  bool			isVisible() const;
  void			setVisible(bool const visible);

  bool			isGather() const;
  void			setGather(bool const gather);

  virtual bool		serialization(Trame &trame) const;
  static Ressource	*deserialization(Trame const &trame, bool const client = true);
};

# ifdef	ODB_COMPILER
#  pragma db object(Ressource)
#  pragma db member(Ressource::_coord) transient
#  pragma db member(Ressource::_level) transient
#  pragma db member(Ressource::_exp) transient
#  pragma db member(Ressource::_visible) transient
#  pragma db member(Ressource::name) virtual(std::string) get(getName()) set(setName(?)) unique type("VARCHAR(24)")
#  pragma db member(Ressource::level) virtual(Levelable::type) get(getLevel()) set(setLevel(?))
#  pragma db member(Ressource::exp) virtual(Levelable::type) get(getExp()) set(setExp(?))
# endif

#endif
