//
// DBZone.hh for DBZone in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Feb 10 14:17:03 2014 alexis mestag
// Last update Tue Mar 11 16:27:17 2014 laurent ansel
//

#ifndef				__DBZONE_HH__
# define			__DBZONE_HH__

# include			<list>
# include			"Database/Persistent.hh"
# include			"Utility/Nameable.hh"
# include			"Utility/Wrapper.hpp"

class				Mob;
class				MobModel;

class				DBZone : public Persistent, public Nameable, public ContainerWrapper<std::list<MobModel *> >
{
  friend class			odb::access;

private:
  unsigned int			_averageLevel;

private:
  DBZone();

  void				setMobModels(std::list<MobModel *> const &mobModels);
  void				setAverageLevel(unsigned int const averageLevel);

public:
  DBZone(std::string const &name, unsigned int const averageLevel = 0);
  DBZone(DBZone const &rhs);
  virtual ~DBZone();

  DBZone			&operator=(DBZone const &rhs);

  std::list<MobModel *> const	&getMobModels() const;

  unsigned int			getAverageLevel() const;

  Mob				*getRandomMob() const;
};

# include			"Entities/Mob.hh"

# ifdef	ODB_COMPILER
#  pragma db object(DBZone)
#  pragma db member(DBZone::mobModels) virtual(DBZone::container_type) get(getContainer()) set(setContainer(?))
# endif

#endif
