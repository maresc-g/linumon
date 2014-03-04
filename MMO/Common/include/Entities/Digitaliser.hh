//
// Digitaliser.hh for Digitaliser in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Dec 10 15:14:59 2013 alexis mestag
// Last update Mon Mar  3 15:52:05 2014 alexis mestag
//

#ifndef			__DIGITALISER_HH__
# define		__DIGITALISER_HH__

# include		<list>
# include		"Entities/Mob.hh"
# include		"Utility/ISerialization.hh"
# include		"Utility/Wrapper.hpp"

class			Digitaliser : public ISerialization, public ContainerWrapper<std::list<Mob *>>
{
public:
  typedef container_type	Mobs;

private:
  container_type		_battleMobs;

private:
  Digitaliser(Digitaliser const &rhs);

public:
  Digitaliser();

  Digitaliser		&operator=(Digitaliser const &rhs);

  virtual ~Digitaliser();

  Mobs const		&getMobs() const;
  void			setMobs(Mobs const &mobs);

  Mobs const		&getBattleMobs() const;
  void			setBattleMobs(Mobs const &mobs);

  Mob			*getMob(unsigned int const id) const;

  void			addMob(Mob const &mob);
  void			addBattleMob(Mob const &mob);

  void			battleMobtoMob(unsigned int const id);
  void			mobtoBattleMob(unsigned int const id);

  virtual bool		serialization(Trame &trame) const;
  static Digitaliser	*deserialization(Trame const &trame);
};

#endif
