//
// Heal.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb 21 12:49:18 2014 laurent ansel
// Last update Tue Feb 25 13:33:24 2014 laurent ansel
//

#ifndef 		__HEAL_HH__
# define		__HEAL_HH__

# include		"Database/Persistent.hh"
# include		"Entities/AEntity.hh"
# include		"Utility/ISerialization.hh"
# include		"Zone/Coordinate.hpp"
# include		"Utility/Id.hh"
# include		"Entities/Digitaliser.hh"

class			Heal : public AEntity, public ISerialization
{
public:
  typedef iCoordinate	HealCoordinate;

private:
  HealCoordinate	*_coord;

private:
  Heal();

public:
  Heal(Heal const &rhs);
  virtual ~Heal();

  Heal			&operator=(Heal const &rhs);

  HealCoordinate const	&getCoord() const;
  void				setCoord(HealCoordinate const &coord);
  HealCoordinate::type const	&getX() const;
  HealCoordinate::type const	&getY() const;
  void			setX(HealCoordinate::type const &x);
  void			setY(HealCoordinate::type const &y);

  void			heal(Digitaliser const &digitaliser) const;

  virtual bool		serialization(Trame &trame) const;
  static Heal		*deserialization(Trame const &trame);
};

#endif
