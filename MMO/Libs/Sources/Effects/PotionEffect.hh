//
// PotionEffect.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Wed Mar  5 16:19:51 2014 laurent ansel
// Last update Wed Mar  5 16:20:45 2014 laurent ansel
//

#ifndef 			__POTIONEFFECT_HH__
# define 			__POTIONEFFECT_HH__

# include			"Effects/MobEffect.hh"

class				PotionEffect : public MobEffect
{
public:
  PotionEffect();
  virtual ~PotionEffect();

  virtual bool			apply(Mob &mob);
};

extern				"C"
{
  PotionEffect		*getInstance() {
    return (new PotionEffect());
  }
}

#endif
