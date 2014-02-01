//
// TalentModel.hh for TalentModel in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Fri Jan 31 13:07:00 2014 alexis mestag
// Last update Fri Jan 31 16:41:25 2014 alexis mestag
//

#ifndef				__TALENTMODEL_HH__
# define			__TALENTMODEL_HH__

# include			<list>
# include			"Database/Persistent.hh"
# include			"Utility/Nameable.hh"
# include			"Effects/EffectLib.hh"

class				TalentModel : public Persistent, public Nameable
{
  friend class			odb::access;

private:
  int					_maxPoints;
  EffectLib const			*_effectLib;
  std::list<TalentModel const *>	_talents;

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
};

# ifdef	ODB_COMPILER
#  pragma db object(TalentModel)
# endif

#endif
