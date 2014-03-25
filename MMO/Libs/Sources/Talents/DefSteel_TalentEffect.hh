//
// DefSteel_TalentEffect.hh for DefSteel_TalentEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Mar 23 13:51:50 2014 alexis mestag
// Last update Tue Mar 25 23:02:27 2014 alexis mestag
//

#ifndef				__DEFSTEEL_TALENTEFFECT_HH__
# define			__DEFSTEEL_TALENTEFFECT_HH__

# include			"Effects/TalentEffect.hh"

class				DefSteel_TalentEffect : public TalentEffect
{
public:
  DefSteel_TalentEffect();
  virtual ~DefSteel_TalentEffect();

public:
  virtual bool			apply(Player &player, unsigned int const fromPts,
				      unsigned int const toPts);
  virtual bool			apply(Mob &mob, unsigned int const fromPts,
				      unsigned int const toPts);
};

extern				"C"
{
  DefSteel_TalentEffect		*getInstance() {
    return (new DefSteel_TalentEffect);
  }
}

#endif
