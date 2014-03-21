//
// TalentModel.hh for TalentModel in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Fri Jan 31 13:07:00 2014 alexis mestag
// Last update Fri Mar 21 00:36:19 2014 alexis mestag
//

#ifndef					__TALENTMODEL_HH__
# define				__TALENTMODEL_HH__

# include				<list>
# include				"Database/Persistent.hh"
# include				"Utility/Nameable.hh"
# include				"Effects/EffectLib.hh"
# include				"Utility/ISerialization.hh"

class					TalentModel : public Persistent, public Nameable, public ISerialization
{
  friend class				odb::access;

public:
  typedef unsigned int			point_type;

private:
  point_type				_maxPoints;
  EffectLib const			*_effectLib;
  TalentModel const			*_parent;
  std::list<TalentModel const *>	_talents;
  std::string				_description;

private:
  TalentModel();
  TalentModel(std::string const &name);

public:
  TalentModel(TalentModel const &rhs);
  virtual ~TalentModel();

  TalentModel				&operator=(TalentModel const &rhs);

  bool					operator==(TalentModel const &rhs) const;
  bool					operator!=(TalentModel const &rhs) const;

  point_type				getMaxPoints() const;
  void					setMaxPoints(point_type const maxPoints);

  EffectLib const			&getEffectLib() const;
  void					setEffectLib(EffectLib const &effectLib);

  void					addTalent(TalentModel const &talent);

  std::list<TalentModel const *> const	&getTalents() const;
  void					setTalents(std::list<TalentModel const *> const &talent);

  TalentModel const			*getParent() const;
  void					setParent(TalentModel const *parent);

  std::string const			&getDescription() const;
  void					setDescription(std::string const &description);

  virtual bool				serialization(Trame &trame) const;
  bool					deserializationTreeModel(Trame const &trame);
  static TalentModel			*deserialization(Trame const &trame);
};

# ifdef	ODB_COMPILER
#  pragma db object(TalentModel)
#  pragma db member(TalentModel::name) virtual(std::string) get(getName()) set(setName(?)) unique type("VARCHAR(24)")
#  pragma db member(TalentModel::_parent) inverse(_talents)
#  pragma db member(TalentModel::_talents) value_not_null
#  pragma db member(TalentModel::_effectLib) not_null
#  pragma db member(TalentModel::_description) get(getDescription()) set(setDescription(?))
# endif

#endif
