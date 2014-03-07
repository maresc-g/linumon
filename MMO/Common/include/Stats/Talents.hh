//
// Talents.hh for Talents in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Mar  4 00:03:52 2014 alexis mestag
// Last update Fri Mar  7 16:19:39 2014 laurent ansel
//

#ifndef				__TALENTS_HH__
# define			__TALENTS_HH__

# include			"Stats/Talent.hh"
# include			"Utility/Wrapper.hpp"
# include			"Utility/ISerialization.hh"

class				Talents : public ContainerWrapper<std::list<Talent *> >, public ISerialization
{
private:
  container_type const		&getTalents() const;
  void				setTalents(container_type const &talents);

  void				deleteTalents();

public:
  Talents();
  Talents(Talents const &rhs);
  virtual ~Talents();

  Talents			&operator=(Talents const &rhs);

  virtual bool			serialization(Trame &trame) const;
  static Talents		*deserialization(Trame const &trame);
};

#endif
