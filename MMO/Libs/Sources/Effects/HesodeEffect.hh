//
// HesodeEffect.hh for HesodeEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/EffectLibs
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Feb 26 13:54:30 2014 alexis mestag
// Last update Wed Feb 26 14:41:49 2014 alexis mestag
//

#ifndef				__HESODEEFFECT_HH__
# define			__HESODEEFFECT_HH__

# include			"Effects/PlayerEffect.hh"

class				HesodeEffect : public PlayerEffect
{
public:
  HesodeEffect();
  virtual ~HesodeEffect();

  virtual bool			apply(Player &player);
};

extern				"C"
{
  HesodeEffect			*getInstance() {
    return (new HesodeEffect());
  }
}

#endif
