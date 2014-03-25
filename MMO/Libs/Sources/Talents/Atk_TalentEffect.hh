//
// Atk_TalentEffect.hh for Atk_TalentEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Mar 23 13:05:55 2014 alexis mestag
// Last update Tue Mar 25 23:02:46 2014 alexis mestag
//

#ifndef				__ATK_TALENTEFFECT_HH__
# define			__ATK_TALENTEFFECT_HH__

# include			"Effects/TalentEffect.hh"

class				Atk_TalentEffect : public TalentEffect
{
public:
  Atk_TalentEffect();
  virtual ~Atk_TalentEffect();

public:
  virtual bool			apply(Player &player, unsigned int const fromPts,
				      unsigned int const toPts);
  virtual bool			apply(Mob &mob, unsigned int const fromPts,
				      unsigned int const toPts);

};

extern				"C"
{
  Atk_TalentEffect		*getInstance() {
    return (new Atk_TalentEffect);
  }
}

#endif
