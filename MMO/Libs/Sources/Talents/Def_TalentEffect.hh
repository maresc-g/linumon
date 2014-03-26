//
// Def_TalentEffect.hh for Def_TalentEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Mar 23 13:09:52 2014 alexis mestag
// Last update Tue Mar 25 23:02:24 2014 alexis mestag
//

#ifndef				__DEF_TALENTEFFECT_HH__
# define			__DEF_TALENTEFFECT_HH__

# include			"Effects/TalentEffect.hh"

class				Def_TalentEffect : public TalentEffect
{
public:
  Def_TalentEffect();
  virtual ~Def_TalentEffect();

public:
  virtual bool			apply(Player &player, unsigned int const fromPts,
				      unsigned int const toPts);
  virtual bool			apply(Mob &mob, unsigned int const fromPts,
				      unsigned int const toPts);
};

extern				"C"
{
  Def_TalentEffect		*getInstance() {
    return (new Def_TalentEffect);
  }
}

#endif
