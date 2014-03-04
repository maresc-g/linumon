//
// Level.hh for Level in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Jan 29 13:50:49 2014 alexis mestag
// Last update Mon Mar  3 22:43:16 2014 alexis mestag
//

#ifndef			__LEVEL_HH__
# define		__LEVEL_HH__

# include		"Utility/ISerialization.hh"

class			Level : public ISerialization
{
public:
  typedef unsigned int	type;

private:
  type		_lvl;
  type		_exp;

public:
  Level();
  Level(type const lvl, type const exp = 0);
  Level(Level const &rhs);
  virtual ~Level();

  Level			&operator=(Level const &rhs);

  type			getLevel() const;
  void			setLevel(type const level);

  type			getExp() const;
  void			setExp(type const exp);

  void			levelUp();
  virtual bool		serialization(Trame &trame) const;
  static Level		*deserialization(Trame const &trame);
};

#endif
