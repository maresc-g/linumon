//
// SuperPotionEffect.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Wed Mar  5 16:20:39 2014 laurent ansel
// Last update Wed Mar  5 16:21:00 2014 laurent ansel
//

#ifndef 			__SUPERPOTIONEFFECT_HH__
# define 			__SUPERPOTIONEFFECT_HH__

# include			"Effects/MobEffect.hh"

class				SuperPotionEffect : public MobEffect
{
public:
  SuperPotionEffect();
  virtual ~SuperPotionEffect();

  virtual bool			apply(Mob &mob);
};

extern				"C"
{
  SuperPotionEffect		*getInstance() {
    return (new SuperPotionEffect());
  }
}

#endif
