//
// Digitaliser.hh for Digitaliser in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Dec 10 15:14:59 2013 alexis mestag
// Last update Sat Feb 15 20:56:53 2014 laurent ansel
//

#ifndef			__DIGITALISER_HH__
# define		__DIGITALISER_HH__

# include		<list>
# include		<odb/core.hxx>
# include		"Entities/Mob.hh"
# include		"Utility/ISerialization.hh"

class			Digitaliser : public ISerialization
{
  friend class		odb::access;

  typedef std::list<Mob *>	Mobs;

private:
  Mobs			_mobs;
  Mobs			_battleMobs;

private:
  Digitaliser(Digitaliser const &rhs);

  Digitaliser		&operator=(Digitaliser const &rhs);

public:
  Digitaliser();
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

# ifdef	ODB_COMPILER
#  pragma db value(Digitaliser)
# endif

#endif
