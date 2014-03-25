//
// BattleMob_TalentEffect.hh for BattleMob_TalentEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Mar 23 17:37:47 2014 alexis mestag
// Last update Tue Mar 25 23:02:39 2014 alexis mestag
//

#ifndef				__BATTLEMOB_TALENTEFFECT_HH__
# define			__BATTLEMOB_TALENTEFFECT_HH__

# include			"Effects/TalentEffect.hh"

class				BattleMob_TalentEffect : public TalentEffect
{
public:
  BattleMob_TalentEffect();
  virtual ~BattleMob_TalentEffect();

public:
  virtual bool			apply(Player &player, unsigned int const fromPts,
				      unsigned int const toPts);
  virtual bool			apply(Mob &mob, unsigned int const fromPts,
				      unsigned int const toPts);
};

extern				"C"
{
  BattleMob_TalentEffect		*getIntance() {
    return (new BattleMob_TalentEffect);
  }
}

#endif
