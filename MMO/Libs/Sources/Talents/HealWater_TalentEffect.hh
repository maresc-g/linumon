//
// HealWater_TalentEffect.hh for HealWater_TalentEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Mar 23 13:53:45 2014 alexis mestag
// Last update Sun Mar 23 14:33:08 2014 alexis mestag
//

#ifndef				__HEALGRASS_TALENTEFFECT_HH__
# define			__HEALGRASS_TALENTEFFECT_HH__

# include			"Effects/TalentEffect.hh"

class				HealWater_TalentEffect : public TalentEffect
{
public:
  HealWater_TalentEffect();
  virtual ~HealWater_TalentEffect();

public:
  virtual bool			apply(Player &player);
  virtual bool			apply(Mob &mob);
};

extern				"C"
{
  HealWater_TalentEffect	*getInstance() {
    return (new HealWater_TalentEffect);
  }
}

#endif
