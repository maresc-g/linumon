//
// Stat.hh for Stat in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 23:00:16 2013 alexis mestag
// Last update Fri Feb 28 16:00:11 2014 alexis mestag
//

#ifndef			__STAT_HH__
# define		__STAT_HH__

# include		"Database/Persistent.hh"
# include		"Utility/ISerialization.hh"
# include		"Stats/StatKey.hh"

class			Stat : public Persistent, public ISerialization
{
  friend class		odb::access;

public:
  typedef unsigned int	value_type;

private:
  StatKey const		*_key;
  value_type		_value;

private:
  Stat();

public:
  Stat(StatKey const &key, value_type const value = 0);
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

  value_type		getValue() const;
  void			setValue(value_type const value);

  bool			isShortLived() const;

  virtual bool		serialization(Trame &trame) const;
  static Stat		*deserialization(Trame const &trame);
};

# ifdef	ODB_COMPILER
#  pragma db object(Stat)
# endif

#endif
