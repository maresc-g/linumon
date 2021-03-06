//
// Stat.hh for Stat in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 23:00:16 2013 alexis mestag
// Last update Fri Mar 21 19:52:44 2014 alexis mestag
//

#ifndef			__STAT_HH__
# define		__STAT_HH__

# include		"Database/Persistent.hh"
# include		"Utility/ISerialization.hh"
# include		"Stats/StatKey.hh"

class			Stat : public ISerialization
{
  friend class		odb::access;

public:
  typedef unsigned int	value_type;
  typedef int		bonus_type;

private:
  StatKey const		*_key;
  value_type		_rawValue;
  bonus_type		_bonus;

private:
  Stat();

public:
  Stat(StatKey const &key, value_type const value = 0, bonus_type const bonus = 0);
  Stat(Stat const &rhs);
  virtual ~Stat();

  Stat			&operator=(Stat const &rhs);
  bool			operator==(Stat const &rhs) const;
  bool			operator!=(Stat const &rhs) const;

  void			add(Stat const &rhs);
  void			sub(Stat const &rhs);
  Stat			operator+(Stat const &rhs) const;
  Stat			operator-(Stat const &rhs) const;
  Stat			&operator+=(Stat const &rhs);
  Stat			&operator-=(Stat const &rhs);

  StatKey const		&getKey() const;
  void			setKey(StatKey const &key);

  value_type		getRawValue() const;
  void			setRawValue(value_type const rawValue);

  bonus_type		getBonus() const;
  void			setBonus(bonus_type const bonus);

  value_type		getValue() const;

  bool			isShortLived() const;

  virtual bool		serialization(Trame &trame) const;
  static Stat		*deserialization(Trame const &trame);
};

# ifdef	ODB_COMPILER
#  pragma db value(Stat)
#  pragma db member(Stat::_key) not_null
#  pragma db member(Stat::_rawValue) get(getRawValue()) set(setRawValue(?)) column("value")
#  pragma db member(Stat::_bonus) get(getBonus()) set(setBonus(?))
# endif

#endif
