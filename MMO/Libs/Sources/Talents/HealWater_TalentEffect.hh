//
// HealWater_TalentEffect.hh for HealWater_TalentEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Mar 23 13:53:45 2014 alexis mestag
// Last update Tue Mar 25 23:02:09 2014 alexis mestag
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
  virtual bool			apply(Player &player, unsigned int const fromPts,
				      unsigned int const toPts);
  virtual bool			apply(Mob &mob, unsigned int const fromPts,
				      unsigned int const toPts);
};

extern				"C"
{
  HealWater_TalentEffect	*getInstance() {
    return (new HealWater_TalentEffect);
  }
}

#endif
