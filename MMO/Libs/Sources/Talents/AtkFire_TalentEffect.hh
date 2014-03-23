//
// AtkFire_TalentEffect.hh for AtkFire_TalentEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Mar 23 13:15:03 2014 alexis mestag
// Last update Sun Mar 23 13:48:49 2014 alexis mestag
//

#ifndef				__ATKFIRE_TALENTEFFECT_HH__
# define			__ATKFIRE_TALENTEFFECT_HH__

# include			"Effects/TalentEffect.hh"

class				AtkFire_TalentEffect : public TalentEffect
{
public:
  AtkFire_TalentEffect();
  virtual AtkFire_TalentEffect();

public:
  virtual bool			apply(Player &player);
  virtual bool			apply(Mob &mob);
};

extern				"C"
{
  AtkFire_TalentEffect		*getInstance() {
    return (new AtkFire_TalentEffect);
  }
}

#endif
