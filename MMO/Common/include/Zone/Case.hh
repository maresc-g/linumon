//
// Case.hh for Case in /home/maitre_c/work/linumon/MMO/Common/include/Zone
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Fri Jan 24 13:39:46 2014 antoine maitre
// Last update Tue Jan 28 14:45:36 2014 laurent ansel
//

#ifndef				__CASE_HH__
# define			__CASE_HH__


# include			<list>
# include			"Coordinate.hpp"
# include			"Entities/AEntity.hh"

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
};

#endif
