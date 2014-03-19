//
// Carcass.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Mar 14 11:04:31 2014 laurent ansel
// Last update Wed Mar 19 19:03:45 2014 laurent ansel
//

#ifndef 		__CARCASS_HH__
# define 		__CARCASS_HH__

# include		<functional>
# include		"Entities/Stack.hh"
# include		"Entities/Ressource.hh"
# include		"Zone/Coordinate.hpp"
// # include		"Entities/Levelable.hh"
# include		"Utility/Wrapper.hpp"

typedef Stack<Ressource>		StackRessource;
typedef std::list<StackRessource>	RessourceStackList;

class			Carcass : public AEntity,
				  public ContainerWrapper<RessourceStackList>,
				  public ISerialization
{
public:
  typedef iCoordinate	CarcassCoordinate;

private:
  CarcassCoordinate	*_coord;

public:
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

  bool			empty() const;

  Ressource		*getRessource(unsigned int const id) const;

  virtual bool		serialization(Trame &trame) const;
  static Carcass	*deserialization(Trame const &trame);
};

typedef Ressource *	Ressource_pointer;

# ifdef	ODB_COMPILER
#  pragma db value(StackRessource)
#  pragma db member(StackRessource::_id) transient
#  pragma db member(StackRessource::_nb) get(getNb()) set(setNb(?))
#  pragma db member(StackRessource::_item) get(getItem()) set(setItem(?)) not_null column("ressource")
# endif

#endif
