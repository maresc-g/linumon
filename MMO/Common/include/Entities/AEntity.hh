//
// AEntity.hh for AEntity in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 19:48:29 2013 alexis mestag
// Last update Fri Mar 14 13:58:22 2014 laurent ansel
//

#ifndef			__AENTITY_HH__
# define		__AENTITY_HH__

# include		<functional>
# include		"Utility/Id.hh"
# include		"Utility/Nameable.hh"
# include		"Utility/ISerialization.hh"

class			AEntity : public Id, public Nameable
{
public:
  typedef enum		eEntity
    {
      NONE,
      ITEM,
      STATENTITY,
      PNJ,
      RESSOURCE,
      CARCASS
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

  virtual bool		serialization(Trame &trame) const = 0;
  static AEntity	*deserialization(Trame const &trame);
};

// # ifdef	ODB_COMPILER
// #  pragma db object(AEntity) abstract
// #  pragma db member(AEntity::_entityType) transient
// # endif

#endif
