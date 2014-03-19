//
// TalentModel.hh for TalentModel in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Fri Jan 31 13:07:00 2014 alexis mestag
// Last update Mon Mar 17 22:52:23 2014 guillaume marescaux
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
  std::list<TalentModel *>		_talents;

private:
  TalentModel();
  TalentModel(std::string const &name);

  void					deleteTalents();
  void					setTalents(TalentModel const &talent);

public:
  TalentModel(TalentModel const &rhs);
  virtual ~TalentModel();

  TalentModel				&operator=(TalentModel const &rhs);

  point_type				getMaxPoints() const;
  void					setMaxPoints(point_type const maxPoints);

  EffectLib const			&getEffectLib() const;
  void					setEffectLib(EffectLib const &effectLib);

  void					addTalent(TalentModel const &talent);
  void					addTalent(TalentModel *talent);

  std::list<TalentModel *> const	&getTalents(void) const;

  virtual bool				serialization(Trame &trame) const;
  bool					deserializationTreeModel(Trame const &trame);
  static TalentModel			*deserialization(Trame const &trame);
};

# ifdef	ODB_COMPILER
#  pragma db object(TalentModel)
#  pragma db member(TalentModel::name) virtual(std::string) get(getName()) set(setName(?)) unique type("VARCHAR(24)")
#  pragma db member(TalentModel::_effectLib) not_null
# endif

#endif
