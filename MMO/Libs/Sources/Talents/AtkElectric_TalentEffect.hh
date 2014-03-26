//
// AtkElectric_TalentEffect.hh for AtkElectric_TalentEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Mar 23 13:48:44 2014 alexis mestag
// Last update Tue Mar 25 23:00:55 2014 alexis mestag
//

#ifndef				__ATKELECTRIC_TALENTEFFECT_HH__
# define			__ATKELECTRIC_TALENTEFFECT_HH__

# include			"Effects/TalentEffect.hh"

class				AtkElectric_TalentEffect : public TalentEffect
{
public:
  AtkElectric_TalentEffect();
  virtual ~AtkElectric_TalentEffect();

public:
  virtual bool			apply(Player &player, unsigned int const fromPts,
				      unsigned int const toPts);
  virtual bool			apply(Mob &mob, unsigned int const fromPts,
				      unsigned int const toPts);
};

extern				"C"
{
  AtkElectric_TalentEffect		*getInstance() {
    return (new AtkElectric_TalentEffect);
  }
}

#endif
