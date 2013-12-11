//
// Type.hh for Type in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Dec  5 21:03:13 2013 alexis mestag
// Last update Tue Dec 10 14:49:03 2013 alexis mestag
//

#ifndef			__TYPE_HH__
# define		__TYPE_HH__

# include		<list>
# include		"Database/Persistent.hh"
# include		"Utility/Nameable.hh"

class			TypeRelations;

class			Type : public Persistent, public Nameable
{
  friend class		odb::access;

public:
  struct		Link
  {
    Type const		*type;
    double		coeff;
  };

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
  // bool			operator>(Type const &rhs) const;
  // bool			operator<(Type const &rhs) const;
  // bool			operator>=(Type const &rhs) const;
  // bool			operator<=(Type const &rhs) const;

  TypeRelations const	&getRelations() const;
};

class			TypeRelations
{
  friend class		odb::access;

  typedef std::list<Type::Link>	Relations;

private:
  Relations		*_relations;

private:
  void			setRelations(Relations const &relations);

public:
  TypeRelations();
  TypeRelations(TypeRelations const &rhs);
  virtual ~TypeRelations();

  TypeRelations		&operator=(TypeRelations const &rhs);

  Relations const	&getRelations() const;
};

# ifdef	ODB_COMPILER
#  pragma db value(Type::Link)
#  pragma db member(Type::Link::type) not_null column("oType_id")
#  pragma db member(Type::Link::coeff) not_null column("coeff")

#  pragma db object(Type)
#  pragma db member(Type::_relations) value_not_null unordered id_column("type_id") value_column("link")
# endif

#endif
