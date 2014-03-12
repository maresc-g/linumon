//
// Talents.hh for Talents in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Mar  4 00:03:52 2014 alexis mestag
// Last update Wed Mar 12 13:23:59 2014 laurent ansel
//

#ifndef				__TALENTS_HH__
# define			__TALENTS_HH__

# include			"Stats/Talent.hh"
# include			"Utility/Wrapper.hpp"
# include			"Utility/ISerialization.hh"

class				Player;

class				Talents : public ContainerWrapper<std::list<Talent *> >, public ISerialization
{
private:
  unsigned int			_currentPts;

private:
  container_type const		&getTalents() const;
  void				setTalents(container_type const &talents);

  void				deleteTalents();

public:
  Talents();
  Talents(Talents const &rhs);
  virtual ~Talents();

  unsigned int			getCurrentPts() const;
  void				setCurrentPts(unsigned int const pts);

  Talents			&operator=(Talents const &rhs);

  bool				modifyTalent(unsigned int const pts, TalentModel const &talent);
  void				apply(Player &player);

  virtual bool			serialization(Trame &trame) const;
  static Talents		*deserialization(Trame const &trame);
};

# include			"Entities/Player.hh"

#endif
