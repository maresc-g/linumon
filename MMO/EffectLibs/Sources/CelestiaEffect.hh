//
// CelestiaEffect.hh for CelestiaEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/EffectLibs
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Feb 26 13:58:03 2014 alexis mestag
// Last update Wed Mar  5 16:19:57 2014 laurent ansel
//

#ifndef				__CELESTIAEFFECT_HH__
# define			__CELESTIAEFFECT_HH__

# include			"Effects/PlayerEffect.hh"

class				CelestiaEffect : public PlayerEffect
{
public:
  CelestiaEffect();
  virtual ~CelestiaEffect();

  virtual bool			apply(Player &player);
};

extern				"C"
{
  CelestiaEffect		*getInstance() {
    return (new CelestiaEffect());
  }
}

#endif
