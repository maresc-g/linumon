//
// Level.hh for Level in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Jan 29 13:50:49 2014 alexis mestag
// Last update Wed Jan 29 14:35:13 2014 alexis mestag
//

#ifndef			__LEVEL_HH__
# define		__LEVEL_HH__

# include		"Database/Persistent.hh"

class			Level
{
  friend class		odb::access;

private:
  int			_lvl;
  int			_exp;

public:
  Level();
  Level(Level const &rhs);
  virtual ~Level();

  Level			&operator=(Level const &rhs);

  int			getLevel() const;
  void			setLevel(int const level);

  int			getExp() const;
  void			setExp(int const exp);

  void			levelUp();
};

# ifdef	ODB_COMPILER
#  pragma db value(Level)
# endif

#endif
