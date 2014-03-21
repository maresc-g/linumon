//
// Type.hh for Type in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Dec  5 21:03:13 2013 alexis mestag
// Last update Thu Mar 20 19:10:40 2014 alexis mestag
//

#ifndef			__TYPE_HH__
# define		__TYPE_HH__

# include		<list>
# include		"Database/Persistent.hh"
# include		"Utility/Nameable.hh"
# include		"Utility/ISerialization.hh"
# include		"Utility/Wrapper.hpp"

class			Type;

struct			Link
{
  typedef double	coeff_type;

  Type const		*type;
  coeff_type		coeff;
};

class			TypeRelations : public ContainerWrapper<std::list<Link>>
{
  friend class		odb::access;

private:
  void			setRelations(container_type const &relations);

public:
  TypeRelations();
  TypeRelations(TypeRelations const &rhs);
  virtual ~TypeRelations();

  TypeRelations		&operator=(TypeRelations const &rhs);

  Link::coeff_type	getCoeffOf(Type const &type) const;

  container_type const	&getRelations() const;
};

class			Type : public Persistent, public Nameable, public ISerialization
{
  friend class		odb::access;

private:
  TypeRelations		*_relations;

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

  Link::coeff_type	getCoeffAgainst(Type const &type) const;

  virtual bool		serialization(Trame &trame) const;
  static Type		*deserialization(Trame const &trame);
};

# ifdef	ODB_COMPILER
#  pragma db value(Link)
#  pragma db member(Link::type) not_null column("oType_id")
#  pragma db member(Link::coeff) not_null

#  pragma db object(Type)
#  pragma db member(Type::_relations) transient
#  pragma db member(Type::name) virtual(std::string) get(getName()) set(setName(?)) unique type("VARCHAR(24)")
#  pragma db member(Type::relations) virtual(TypeRelations::container_type) get(_relations->getContainer()) set(_relations->setContainer(?)) value_not_null unordered
# endif

#endif
