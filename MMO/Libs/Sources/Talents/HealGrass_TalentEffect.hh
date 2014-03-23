//
// HealGrass_TalentEffect.hh for HealGrass_TalentEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Mar 23 13:52:32 2014 alexis mestag
// Last update Sun Mar 23 13:56:11 2014 alexis mestag
//

#ifndef				__HEALGRASS_TALENTEFFECT_HH__
# define			__HEALGRASS_TALENTEFFECT_HH__

# include			"Effects/TalentEffect.hh"

class				HealGrass_TalentEffect : public TalentEffect
{
public:
  HealGrass_TalentEffect();
  virtual HealGrass_TalentEffect();

public:
  virtual bool			apply(Player &player);
  virtual bool			apply(Mob &mob);
};

extern				"C"
{
  HealGrass_TalentEffect	*getInstance() {
    return (new HealGrass_TalentEffect);
  }
}

#endif
