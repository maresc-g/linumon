//
// Talent.hh for Talent in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Fri Jan 31 14:34:15 2014 alexis mestag
// Last update Mon Feb  3 12:58:31 2014 laurent ansel
//

#ifndef				__TALENT_HH__
# define			__TALENT_HH__

# include			"Database/Persistent.hh"
# include			"Stats/TalentModel.hh"
# include			"Utility/ISerialization.hh"

class				Talent : public Persistent, public ISerialization
{
  friend class			odb::access;

private:
  TalentModel const		*_model;
  int				_currentPoints;

private:
  Talent();

  Talent			&operator=(Talent const &rhs);

  void				setModel(TalentModel const &model);

public:
  Talent(Talent const &rhs);
  virtual ~Talent();

  TalentModel const		&getModel() const;

  int				getCurrentPoints() const;
  void				setCurrentPoints(int const currentPoints);

  virtual bool			serialization(Trame &trame) const;
  static Talent			*deserialization(Trame const &trame);
};

# ifdef	ODB_COMPILER
#  pragma db object(Talent)
# endif

#endif
