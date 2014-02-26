//
// AStatEntity.hh for AStatEntity in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 21:21:41 2013 alexis mestag
// Last update Wed Feb 26 01:25:31 2014 alexis mestag
//

#ifndef			__ASTATENTITY_HH__
# define		__ASTATENTITY_HH__

# include		"Entities/AEntity.hh"
# include		"Stats/Stats.hh"

class			AStatEntity : public AEntity
{
  friend class		odb::access;

public:
  typedef enum		eStatEntity
    {
      NONE,
      CHARACTER,
      MOBMODEL
    }			eStatEntity;

private:
  eStatEntity			_statEntityType;
  AuthorizedStatKeys const	*_authKeys;
  Stats				_stats;
  Stats				_tmpStats;
  bool				_inBattle;

protected:
  AStatEntity();
  AStatEntity(std::string const &name, eStatEntity const statEntityType);
  AStatEntity(AStatEntity const &rhs);

  AStatEntity		&operator=(AStatEntity const &rhs);

  void			setStatEntityType(eStatEntity const statEntityType);

public:
  virtual ~AStatEntity();

  eStatEntity		getStatEntityType() const;

  Stats const		&getStats() const;
  void			setStats(Stats const &stats);

  Stats const		&getTmpStats() const;
  void			setTmpStats(Stats const &stats);

  AuthorizedStatKeys const	&getStatKeys() const;
  void				setStatKeys(AuthorizedStatKeys const &keys);

  bool			isInBattle() const;

  void			enterBattle();
  void			leaveBattle();

private:
  void			initTmpStats();
  void			endTmpStats();

  void			setInBattle(bool const inBattle);
};

# ifdef	ODB_COMPILER
#  pragma db object(AStatEntity) abstract
#  pragma db member(AStatEntity::_statEntityType) transient
#  pragma db member(AStatEntity::_stats)// get(getStats()) set(setStats(?))
#  pragma db member(AStatEntity::_tmpStats)
#  pragma db member(AStatEntity::_inBattle) transient
# endif

#endif
