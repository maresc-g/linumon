//
// TalentModel.hh for TalentModel in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Fri Jan 31 13:07:00 2014 alexis mestag
// Last update Fri Mar  7 21:45:51 2014 laurent ansel
//

#ifndef				__TALENTMODEL_HH__
# define			__TALENTMODEL_HH__

# include			<list>
# include			"Database/Persistent.hh"
# include			"Utility/Nameable.hh"
# include			"Effects/EffectLib.hh"
# include			"Utility/ISerialization.hh"

class				TalentModel : public Persistent, public Nameable, public ISerialization
{
  friend class			odb::access;

private:
  int					_maxPoints;
  EffectLib const			*_effectLib;
  std::list<TalentModel *>		_talents;

private:
  TalentModel();
  TalentModel(std::string const &name);

  void				deleteTalents();
  void				setTalents(TalentModel const &talent);

public:
  TalentModel(TalentModel const &rhs);
  virtual ~TalentModel();

  TalentModel			&operator=(TalentModel const &rhs);

  int				getMaxPoints() const;
  void				setMaxPoints(int const maxPoints);

  EffectLib const		&getEffectLib() const;
  void				setEffectLib(EffectLib const &effectLib);

  void				addTalent(TalentModel const &talent);
  void				addTalent(TalentModel *talent);

  virtual bool			serialization(Trame &trame) const;
  bool				deserializationTreeModel(Trame const &trame);
  static TalentModel		*deserialization(Trame const &trame);
};

# ifdef	ODB_COMPILER
#  pragma db object(TalentModel)
# endif

#endif
