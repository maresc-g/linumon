//
// NormalCartridgex10.hh for NormalCartridgex10 in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Mar 26 09:04:38 2014 alexis mestag
// Last update Wed Mar 26 09:12:32 2014 alexis mestag
//

#ifndef				__NORMALCARTRIDGEEFFECT_HH__
# define			__NORMALCARTRIDGEEFFECT_HH__

# include			"Effects/PlayerEffect.hh"

class				NormalCartridgeEffect : public PlayerEffect
{
public:
  NormalCartridgeEffect();
  virtual ~NormalCartridgeEffect();

public:
  virtual bool			apply(Player &player);
};

extern				"C"
{
  NormalCartridgeEffect		*getInstance() {
    return (new NormalCartridgeEffect);
  }
}

#endif
