//
// Heal_TalentEffect.hh for Heal_TalentEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Mar 23 13:10:32 2014 alexis mestag
// Last update Tue Mar 25 23:02:14 2014 alexis mestag
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
  virtual bool			apply(Player &player, unsigned int const fromPts,
				      unsigned int const toPts);
  virtual bool			apply(Mob &mob, unsigned int const fromPts,
				      unsigned int const toPts);
};

extern				"C"
{
  Heal_TalentEffect		*getInstance() {
    return (new Heal_TalentEffect);
  }
}

#endif
