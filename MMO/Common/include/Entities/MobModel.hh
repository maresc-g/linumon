//
// MobModel.hh for MobModel in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Fri Jan 24 18:21:00 2014 alexis mestag
// Last update Sun Jan 26 14:42:59 2014 laurent ansel
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
  Spells const		_spells;

private:
  MobModel();
  MobModel(MobModel const &rhs);

  MobModel		&operator=(MobModel const &rhs);

public:
  virtual ~MobModel();
  Type const		&getType() const;
  void			setType(Type const &type);

  Spells const		&getSpells() const;
  virtual bool		serialization(Trame &trame);
  virtual bool		deserialization(Trame const &trame);
};

# ifdef	ODB_COMPILER
#  pragma db object(MobModel)
#  pragma db member(MobModel::_type) not_null column(type_id)
#  pragma db member(MobModel::_spells)
# endif

#endif
