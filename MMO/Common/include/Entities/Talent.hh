//
// Talent.hh for Talent in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Jan 29 15:04:45 2014 alexis mestag
// Last update Wed Jan 29 15:25:09 2014 alexis mestag
//

#ifndef			__TALENT_HH__
# define		__TALENT_HH__

# include		"Database/Persistent.hh"
# include		"Utility/Id.hh"
# include		"Utility/Nameable.hh"

class			Talent : public Peristent, public Id, public Nameable
{
  friend class		odb::access;

private:
  int			_maxPoints;
  int			_currentPoints;
  int			_rank;

public:
  Talent();
  Talent(Talent const &rhs);
  virtual ~Talent();

  Talent		&operator=(Talent const &rhs);

  int			getMaxPoints() const;
  void			setMaxPoints(int const maxPoints);

  int			getCurrentPoints() const;
  void			setCurrentPoints(int const currentPoints);

  int			getRank() const;
  void			setRank(int const rank);
};

# ifdef	ODB_COMPILER
#  pragma db object(Talent)
# endif

#endif
