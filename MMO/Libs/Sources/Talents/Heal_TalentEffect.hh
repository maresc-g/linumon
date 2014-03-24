//
// Heal_TalentEffect.hh for Heal_TalentEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Mar 23 13:10:32 2014 alexis mestag
// Last update Sun Mar 23 13:12:02 2014 alexis mestag
//

#ifndef				__HEAL_TALENTEFFECT_HH__
# define			__HEAL_TALENTEFFECT_HH__

# include			"Effects/TalentEffect.hh"

class				Heal_TalentEffect : public TalentEffect
{
public:
  Heal_TalentEffect();
  virtual ~Heal_TalentEffect();

public:
  virtual bool			apply(Player &player);
  virtual bool			apply(Mob &mob);
};

extern				"C"
{
  Heal_TalentEffect		*getInstance() {
    return (new Heal_TalentEffect);
  }
}

#endif
