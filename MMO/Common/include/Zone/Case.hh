//
// Case.hh for Case in /home/maitre_c/work/linumon/MMO/Common/include/Zone
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Fri Jan 24 13:39:46 2014 antoine maitre
// Last update Wed Feb  5 14:56:41 2014 antoine maitre
//

#ifndef				__CASE_HH__
# define			__CASE_HH__


# include			<sstream>
# include			<list>
# include			"Coordinate.hpp"
# include			"Entities/Player.hh"
# include			"Utility/ISerialization.hh"

class				Player;

class				Case
{
private:
  std::list<AEntity *>		*_entities;
  const Coordinate<int>		*_coord;
  const bool			_safe;

public:
  Case(int const x, int const y, bool const safe);
  virtual ~Case();
  bool				getSafe() const;
  void				setSafe(bool const);
  const Coordinate<int>		&getCoord() const;
  void				addAEntity(AEntity*);
  void				delAEntity(AEntity*);
  std::list<AEntity *>		*getEntities() const;
  virtual bool			serialization(Trame &trame) const;
  static Case			*deserialization(Trame const &trame);
};

#endif
