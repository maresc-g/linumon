//
// Digitaliser.hh for Digitaliser in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Dec 10 15:14:59 2013 alexis mestag
// Last update Thu Mar 13 18:08:02 2014 laurent ansel
//

#ifndef			__DIGITALISER_HH__
# define		__DIGITALISER_HH__

# include		<list>
# include		"Utility/ISerialization.hh"
# include		"Utility/Wrapper.hpp"

class			Mob;
class			Player;

class			Digitaliser : public ISerialization, public ContainerWrapper<std::list<Mob *> >
{
public:
  typedef container_type	Mobs;

private:
  container_type	_battleMobs;
  Player const		*_player;

private:
  Digitaliser(Digitaliser const &rhs);

  void			deleteMobs();

public:
  Digitaliser(Player const *player);

  Digitaliser		&operator=(Digitaliser const &rhs);

  virtual ~Digitaliser();

  Mobs const		&getMobs() const;
  void			setMobs(Mobs const &mobs);

  Mobs const		&getBattleMobs() const;
  void			setBattleMobs(Mobs const &mobs);

  void			setPlayer(Player const *player);
  Player const		*getPlayer() const;

  unsigned int		getLimit() const;

  Mob			*getMob(unsigned int const id) const;

  void			addMob(Mob const &mob);
  void			addBattleMob(Mob const &mob);

  void			addMob(Mob  *mob);
  Mob			*getAndDeleteMob(unsigned int const mob);

  bool			battleMobtoMob(unsigned int const id);
  bool			mobtoBattleMob(unsigned int const id);

  bool			switchMobs(unsigned int const mob1, unsigned int const id2);

  virtual bool		serialization(Trame &trame) const;
  static Digitaliser	*deserialization(Trame const &trame);
};

# include		"Entities/Player.hh"
# include		"Entities/Mob.hh"

#endif
