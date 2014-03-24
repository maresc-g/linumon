//
// HP_TalentEffect.hh for HP_TalentEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat Mar 22 18:32:00 2014 alexis mestag
// Last update Sun Mar 23 13:11:51 2014 alexis mestag
//

#ifndef				__HP_TALENTEFFECT_HH__
# define			__HP_TALENTEFFECT_HH__

# include			"Effects/TalentEffect.hh"

class				HP_TalentEffect : public TalentEffect
{
public:
  HP_TalentEffect();
  virtual ~HP_TalentEffect();

public:
  virtual bool			apply(Player &player);
  virtual bool			apply(Mob &mob);
};

extern				"C"
{
  HP_TalentEffect		*getInstance() {
    return (new HP_TalentEffect);
  }
}

#endif
