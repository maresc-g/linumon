//
// AEntity.hh for AEntity in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 19:48:29 2013 alexis mestag
// Last update Thu Dec  5 16:45:08 2013 alexis mestag
//

#ifndef			__AENTITY_HH__
# define		__AENTITY_HH__

# include		"Utility/Id.hh"
# include		"Utility/Nameable.hh"

class			AEntity : public Id, public Nameable
{
public:
  typedef enum		eEntity
    {
      NONE,
      ITEM,
      STATENTITY
    }			eEntity;

private:
  eEntity		_entityType;

protected:
  AEntity();
  AEntity(std::string const &name, eEntity const entityType);
  AEntity(AEntity const &rhs);

  AEntity		&operator=(AEntity const &rhs);

  void			setEntityType(eEntity const entityType);

public:
  virtual ~AEntity();

  eEntity		getEntityType() const;
};

# ifdef	ODB_COMPILER
#  pragma db object(AEntity) abstract
#  pragma db member(AEntity::_entityType) transient
# endif

#endif
