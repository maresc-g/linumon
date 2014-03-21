//
// MobModel.hh for MobModel in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Fri Jan 24 18:21:00 2014 alexis mestag
// Last update Thu Mar 20 13:56:52 2014 alexis mestag
//

#ifndef			__MOBMODEL_HH__
# define		__MOBMODEL_HH__

# include		"Database/Persistent.hh"
# include		"Entities/AStatEntity.hh"
# include		"Entities/Carcass.hh"
# include		"Entities/Drop.hh"
# include		"Entities/Spells.hh"
# include		"Entities/Type.hh"
# include		"Stats/ExperienceCurve.hh"
# include		"Utility/ISerialization.hh"

class			MobModel : public Persistent, public AStatEntity, public ISerialization
{
  friend class		odb::access;

private:
  Type const		*_type;
  Spells 		*_spells;
  Carcass		*_carcass;
  unsigned int		_expSeed;
  std::string		_dropPath;
  Drop			*_drop;
  unsigned int		_catchRate;
#ifndef		CLIENT_COMPILATION
  ExperienceCurve const	*_expCurve;
#endif

private:
  MobModel();
  MobModel(MobModel const &rhs);

  MobModel		&operator=(MobModel const &rhs);

  void			setDrop(Drop const &drop);

public:
  virtual ~MobModel();

  Type const		&getType() const;
  void			setType(Type const &type);

  Carcass const		&getCarcass() const;
  void			setCarcass(Carcass const &carcass);
  Carcass		*getNewCarcass() const;

  Spells const		&getSpells() const;
  void			setSpells(Spells const &spells);

#ifndef		CLIENT_COMPILATION
  ExperienceCurve const	&getExperienceCurve() const;
  void			setExperienceCurve(ExperienceCurve const &expCurve);
#endif

  unsigned int		getExpSeed() const;
  void			setExpSeed(unsigned int const expSeed);

  std::string const	&getDropPath() const;
  void			setDropPath(std::string const &dropPath);
  bool			loadDrop();

  unsigned int		getCatchRate() const;
  void			setCatchRate(unsigned int const catchRate);

  Drop const		&getDrop() const;

  virtual bool		serialization(Trame &trame) const;
  static MobModel	*deserialization(Trame const &trame);
};

# ifdef	ODB_COMPILER
#  pragma db object(MobModel)
#  pragma db member(MobModel::_spells) transient
#  pragma db member(MobModel::_carcass) transient
#  pragma db member(MobModel::_drop) transient
#  pragma db member(MobModel::name) virtual(std::string) get(getName()) set(setName(?)) unique type("VARCHAR(24)")
#  pragma db member(MobModel::_type) not_null
#  pragma db member(MobModel::spells) virtual(Spells::container_type) get(_spells->getContainer()) set(_spells->setContainer(?)) value_not_null
#  pragma db member(MobModel::_expCurve) not_null
#  pragma db member(MobModel::carcass) virtual(Carcass::container_type) get(_carcass->getContainer()) set(_carcass->setContainer(?)) value_not_null value_column("") unordered
#  pragma db member(MobModel::_expSeed) get(getExpSeed()) set(setExpSeed(?))
#  pragma db member(MobModel::_dropPath) get(getDropPath()) set(setDropPath(?))
#  pragma db member(MobModel::_catchRate) get(getCatchRate()) set(setCatchRate(?))
# endif

#endif
