//
// FactionEffect.hh for FactionEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/EffectLibs/Sources
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Feb 26 13:27:00 2014 alexis mestag
// Last update Fri Mar 21 15:01:37 2014 alexis mestag
//

#ifndef				__FACTIONEFFECT_HH__
# define			__FACTIONEFFECT_HH__

# include			"Effects/IEffect.hpp"
# include			"Entities/Faction.hh"

class				FactionEffect : public AEffect<Faction>
{
protected:
  FactionEffect();

public:
  virtual ~FactionEffect();
};

#endif
