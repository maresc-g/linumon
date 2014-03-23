//
// Atk_TalentEffect.hh for Atk_TalentEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Mar 23 13:05:55 2014 alexis mestag
// Last update Sun Mar 23 13:12:37 2014 alexis mestag
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
  virtual bool			apply(Player &player);
  virtual bool			apply(Mob &mob);
};

extern				"C"
{
  Atk_TalentEffect		*getInstance() {
    return (new Atk_TalentEffect);
  }
}

#endif
