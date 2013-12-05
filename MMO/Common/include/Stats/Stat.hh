//
// Stat.hh for Stat in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 23:00:16 2013 alexis mestag
// Last update Tue Dec  3 13:08:38 2013 alexis mestag
//

#ifndef			__STAT_HH__
# define		__STAT_HH__

class			Stat
{
public:
  typedef enum		eStat
    {
      NONE,
      HP,
      SPEED,
      DODGE,
      CRITIC,
      PARADE,
      ATTACK,
      DEFENSE,
      PRECISION,
      CAPTURE,
      LIMIT_MOB,
      SPE_ATTACK,
      SPE_DEFENSE
    }			eStat;

private:
  eStat			_statType;
  int			_value;

public:
  Stat();
  Stat(eStat const statType, int const value = 0);
  Stat(Stat const &rhs);
  virtual ~Stat();

  Stat			&operator=(Stat const &rhs);

  int			getValue() const;
  void			setValue(int const value);
  eStat			getStatType() const;
  void			setStatType(eStat const statType);
};

#endif
