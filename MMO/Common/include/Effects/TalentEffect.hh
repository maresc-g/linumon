//
// TalentEffect.hh for TalentEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Fri Mar 21 15:07:51 2014 alexis mestag
// Last update Tue Mar 25 23:30:38 2014 alexis mestag
//

#ifndef				__TALENTEFFECT_HH__
# define			__TALENTEFFECT_HH__

# include			"Effects/PlayerEffect.hh"
# include			"Effects/MobEffect.hh"
# include			"Stats/Talent.hh"

class				TalentEffect : public PlayerEffect
{
private:
  // Talent const			*_talent;
  bool				_forMob;

private:
  TalentEffect();

protected:
  TalentEffect(bool const isForMob);
public:
  virtual ~TalentEffect();

protected:
  void				setForMob(bool const isForMob);
  void				applyToAllMobs(Player &player, unsigned int const, unsigned int const);

public:
  // void				initialize(Talent const *talent);
  // Talent const			*getTalent() const;

  bool				isForMob() const;

  virtual bool			apply(Player &player, unsigned int const fromPts,
				      unsigned int const toPts) = 0;
  virtual bool			apply(Mob &mob, unsigned int const fromPts,
				      unsigned int const toPts) = 0;

  virtual bool			apply(Player &player); // Do not use this one !
};

#endif
