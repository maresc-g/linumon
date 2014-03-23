//
// DefRock_TalentEffect.hh for DefRockTalentEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Mar 23 13:51:05 2014 alexis mestag
// Last update Sun Mar 23 14:32:29 2014 alexis mestag
//

#ifndef				__DEFROCK_TALENTEFFECT_HH__
# define			__DEFROCK_TALENTEFFECT_HH__

# include			"Effects/TalentEffect.hh"

class				DefRock_TalentEffect : public TalentEffect
{
public:
  DefRock_TalentEffect();
  virtual ~DefRock_TalentEffect();

public:
  virtual bool			apply(Player &player);
  virtual bool			apply(Mob &mob);
};

extern				"C"
{
  DefRock_TalentEffect		*getInstance() {
    return (new DefRock_TalentEffect);
  }
}

#endif
