//
// Capture_TalentEffect.hh for Capture_TalentEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Mar 23 17:32:19 2014 alexis mestag
// Last update Tue Mar 25 23:02:35 2014 alexis mestag
//

#ifndef				__CAPTURE_TALENTEFFECT_HH__
# define			__CAPTURE_TALENTEFFECT_HH__

# include			"Effects/TalentEffect.hh"

class				Capture_TalentEffect : public TalentEffect
{
public:
  Capture_TalentEffect();
  virtual ~Capture_TalentEffect();

public:
  virtual bool			apply(Player &player, unsigned int const fromPts,
				      unsigned int const toPts);
  virtual bool			apply(Mob &mob, unsigned int const fromPts,
				      unsigned int const toPts);
};

extern				"C"
{
  Capture_TalentEffect		*getIntance() {
    return (new Capture_TalentEffect);
  }
}

#endif
