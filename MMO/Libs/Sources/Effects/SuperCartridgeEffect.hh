//
// SuperCartridgeEffect.hh for SuperCartridgeEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Mar 26 09:07:21 2014 alexis mestag
// Last update Wed Mar 26 09:08:53 2014 alexis mestag
//

#ifndef				__SUPERCARTRIDGEEFFECT_HH__
# define			__SUPERCARTRIDGEEFFECT_HH__

# include			"Effects/PlayerEffect.hh"

class				SuperCartridgeEffect : public PlayerEffect
{
public:
  SuperCartridgeEffect();
  virtual ~SuperCartridgeEffect();

public:
  virtual bool			apply(Player &player);
};

extern				"C"
{
  SuperCartridgeEffect		*getInstance() {
    return (new SuperCartridgeEffect);
  }
}

#endif
