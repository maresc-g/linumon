//
// Level.hh for Level in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Jan 29 13:50:49 2014 alexis mestag
// Last update Mon Feb 10 16:06:08 2014 alexis mestag
//

#ifndef			__LEVEL_HH__
# define		__LEVEL_HH__

# include		"Database/Persistent.hh"
# include		"Utility/ISerialization.hh"

class			Level : public ISerialization
{
  friend class		odb::access;

private:
  unsigned int		_lvl;
  unsigned int		_exp;

public:
  Level();
  Level(unsigned int const lvl, unsigned int const exp = 0);
  Level(Level const &rhs);
  virtual ~Level();

  Level			&operator=(Level const &rhs);

  unsigned int		getLevel() const;
  void			setLevel(unsigned int const level);

  unsigned int		getExp() const;
  void			setExp(unsigned int const exp);

  void			levelUp();
  virtual bool		serialization(Trame &trame) const;
  static Level		*deserialization(Trame const &trame);
};

# ifdef	ODB_COMPILER
#  pragma db value(Level)
# endif

#endif
