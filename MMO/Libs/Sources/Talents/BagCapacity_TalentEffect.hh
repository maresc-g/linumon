//
// BagCapacity_TalentEffect.hh for BagCapacity_TalentEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Mar 23 17:39:04 2014 alexis mestag
// Last update Sun Mar 23 17:39:50 2014 alexis mestag
//

#ifndef				__BAGCAPACITY_TALENTEFFECT_HH__
# define			__BAGCAPACITY_TALENTEFFECT_HH__

# include			"Effects/TalentEffect.hh"

class				BagCapacity_TalentEffect : public TalentEffect
{
public:
  BagCapacity_TalentEffect();
  virtual ~BagCapacity_TalentEffect();

public:
  virtual bool			apply(Player &player);
  virtual bool			apply(Mob &mob);
};

extern				"C"
{
  BagCapacity_TalentEffect		*getIntance() {
    return (new BagCapacity_TalentEffect);
  }
}

#endif
