//
// Case.hh for Case in /home/maitre_c/work/linumon/MMO/Common/include/Zone
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Fri Jan 24 13:39:46 2014 antoine maitre
// Last update Thu Feb 20 12:25:31 2014 laurent ansel
//

#ifndef				__CASE_HH__
# define			__CASE_HH__


# include			<sstream>
# include			<list>
# include			"Zone/Coordinate.hpp"
# include			"Entities/Player.hh"
# include			"Entities/Ressource.hh"
# include			"Utility/ISerialization.hh"
# include			"Utility/GenericSerialization.hpp"

class				Player;

class				Case
{
private:
  std::list<AEntity *>		*_entities;
  const Coordinate<int>		_coord;
  const bool			_safe;

public:
  Case(int const x, int const y, bool const safe);
  virtual ~Case();
  bool				getSafe() const;
  void				setSafe(bool const);
  const Coordinate<int>		&getCoord() const;
  void				addAEntity(AEntity*);
  void				delAEntity(AEntity*);
  void				delAEntity(unsigned int const id);
  std::list<AEntity *>		*getEntities() const;
  virtual bool			serialization(Trame &trame) const;
  void				deserialization(Trame const &trame);
};

#endif
