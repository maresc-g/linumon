//
// DefSteel_TalentEffect.hh for DefSteel_TalentEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Mar 23 13:51:50 2014 alexis mestag
// Last update Sun Mar 23 13:52:08 2014 alexis mestag
//

#ifndef				__DEFSTEEL_TALENTEFFECT_HH__
# define			__DEFSTEEL_TALENTEFFECT_HH__

# include			"Effects/TalentEffect.hh"

class				DefSteel_TalentEffect : public TalentEffect
{
public:
  DefSteel_TalentEffect();
  virtual DefSteel_TalentEffect();

public:
  virtual bool			apply(Player &player);
  virtual bool			apply(Mob &mob);
};

extern				"C"
{
  DefSteel_TalentEffect		*getInstance() {
    return (new DefSteel_TalentEffect);
  }
}

#endif
