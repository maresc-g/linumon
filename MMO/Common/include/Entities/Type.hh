//
// Type.hh for Type in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Dec  5 21:03:13 2013 alexis mestag
// Last update Thu Feb 27 17:53:26 2014 alexis mestag
//

#ifndef			__TYPE_HH__
# define		__TYPE_HH__

# include		<list>
# include		"Database/Persistent.hh"
# include		"Utility/Nameable.hh"
# include		"Utility/ISerialization.hh"

class			Type;

class			TypeRelations
{
  friend class		odb::access;

public:
  struct		Link
  {
    typedef double	coeff_type;

    Type const		*type;
    coeff_type		coeff;
  };

  typedef std::list<Link>	Relations;

private:
  Relations		_relations;

private:
  void			setRelations(Relations const &relations);

public:
  TypeRelations();
  TypeRelations(TypeRelations const &rhs);
  virtual ~TypeRelations();

  TypeRelations		&operator=(TypeRelations const &rhs);

  Link::coeff_type	getCoeffOf(Type const &type) const;

  Relations const	&getRelations() const;
};

class			Type : public Persistent, public Nameable, public ISerialization
{
  friend class		odb::access;

private:
  TypeRelations		_relations;

private:
  Type();

  void			setRelations(TypeRelations const &relations);

public:
  Type(std::string const &name);
  Type(Type const &rhs);
  virtual ~Type();

  Type			&operator=(Type const &rhs);
  bool			operator==(Type const &rhs) const;
  bool			operator!=(Type const &rhs) const;

  TypeRelations const	&getRelations() const;

  TypeRelations::Link::coeff_type	getCoeffAgainst(Type const &type) const;

  virtual bool		serialization(Trame &trame) const;
  static Type		*deserialization(Trame const &trame);
};

# ifdef	ODB_COMPILER
#  pragma db value(TypeRelations::Link)
#  pragma db member(TypeRelations::Link::type) not_null column("oType_id")
#  pragma db member(TypeRelations::Link::coeff) not_null column("coeff")

#  pragma db value(TypeRelations)

#  pragma db object(Type)
# endif

#endif
