//
// MobModel.hh for MobModel in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Fri Jan 24 18:21:00 2014 alexis mestag
// Last update Tue Mar 11 21:42:18 2014 alexis mestag
//

#ifndef			__MOBMODEL_HH__
# define		__MOBMODEL_HH__

# include		"Database/Persistent.hh"
# include		"Entities/AStatEntity.hh"
# include		"Entities/Spells.hh"
# include		"Entities/Type.hh"
# include		"Utility/ISerialization.hh"

class			MobModel : public Persistent, public AStatEntity, public ISerialization
{
  friend class		odb::access;

private:
  Type const		*_type;
  Spells 		*_spells;

private:
  MobModel();
  MobModel(MobModel const &rhs);

  MobModel		&operator=(MobModel const &rhs);


public:
  virtual ~MobModel();

  Type const		&getType() const;
  void			setType(Type const &type);

  Spells const		&getSpells() const;
  void			setSpells(Spells const &spells);

  virtual bool		serialization(Trame &trame) const;
  static MobModel	*deserialization(Trame const &trame);
};

# ifdef	ODB_COMPILER
#  pragma db object(MobModel)
#  pragma db member(MobModel::_spells) transient
#  pragma db member(MobModel::name) virtual(std::string) get(getName()) set(setName(?)) unique type("VARCHAR(24)")
#  pragma db member(MobModel::_type) not_null
#  pragma db member(MobModel::spells) virtual(Spells::container_type) get(_spells->getContainer()) set(_spells->setContainer(?)) value_not_null
# endif

#endif
