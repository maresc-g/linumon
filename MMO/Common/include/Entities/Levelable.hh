//
// Levelable.hh for Levelable in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Mar 18 17:02:50 2014 alexis mestag
// Last update Mon Mar 24 16:11:27 2014 alexis mestag
//

#ifndef				__LEVELABLE_HH__
# define			__LEVELABLE_HH__

class				Levelable
{
public:
  typedef unsigned int		type;

private:
  type				_currentExp;
  type				_level;
  type				_exp;
  type				_oldExp;

public:
  Levelable();
  Levelable(type const currentExp, type const level, type const exp);
  Levelable(Levelable const &rhs);
  virtual ~Levelable();

  Levelable			&operator=(Levelable const &rhs);

public:
  type				getCurrentExp() const;
  unsigned int			setCurrentExp(type const currentExp, bool const check = true);
  unsigned int			incCurrentExp(type const inc, bool const check = true);

  type				getLevel() const;
  void				setLevel(type const level);

  type				getExp() const;
  void				setExp(type const exp);

  type				getOldExp() const;
  void				setOldExp(type const oldExp);

  virtual void			levelUp() = 0;

private:
  unsigned int			checkLevelUp();
};

#endif
