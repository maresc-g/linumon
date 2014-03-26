//
// Digitaliser.hh for Digitaliser in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Dec 10 15:14:59 2013 alexis mestag
// Last update Wed Mar 26 02:37:21 2014 alexis mestag
//

#ifndef			__DIGITALISER_HH__
# define		__DIGITALISER_HH__

# include		<list>
# include		"Entities/CartridgeClip.hh"
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
  double		_efficiency;
  CartridgeClip		*_cartridgeClip;

private:
  Digitaliser(Digitaliser const &rhs);

  void			deleteMobs(container_type &c);

public:
  Digitaliser(Player const *player);

  Digitaliser		&operator=(Digitaliser const &rhs);

  virtual ~Digitaliser();

  Mobs const		&getMobs() const;
  void			setMobs(Mobs const &mobs);

  Mobs const		&getBattleMobs() const;
  Mobs			&getBattleMobs();
  void			setBattleMobs(Mobs const &mobs);

  void			setPlayer(Player const *player);
  Player const		*getPlayer() const;

  double		getEfficiency() const;
  void			setEfficiency(double const efficiency);

  CartridgeClip const	&getCartridgeClip() const;
  void			setCartridgeClip(CartridgeClip const &c);
  void			setCartridgeClip(CartridgeClip::summary_type const &c);
  void			addCartridge(Cartridge const &cartridge);
  Cartridge		*getNextCartridge();

  unsigned int		getLimit() const;

  Mob			*getMob(unsigned int const id) const;

  void			addBattleMob(Mob &mob);

  void			addMob(Mob &mob);
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
