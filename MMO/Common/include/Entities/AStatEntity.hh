//
// AStatEntity.hh for AStatEntity in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 21:21:41 2013 alexis mestag
// Last update Tue Dec  3 13:42:08 2013 alexis mestag
//

#ifndef			__ASTATENTITY_HH__
# define		__ASTATENTITY_HH__

# include		"Entities/AEntity.hh"
# include		"Stats/Stats.hh"

class			AStatEntity : public AEntity
{
public:
  typedef enum		eStatEntity
    {
      NONE,
      CHARACTER
    }			eStatEntity;

private:
  eStatEntity		_statEntityType;
  Stats			*_stats;

protected:
  AStatEntity();
  AStatEntity(std::string const &name, eStatEntity const statEntityType);
  AStatEntity(AStatEntity const &rhs);

  AStatEntity		&operator=(AStatEntity const &rhs);

  void			setStatEntityType(eStatEntity const statEntityType);

public:
  virtual ~AStatEntity();

  eStatEntity		getStatEntityType() const;
  Stats const		*getStats() const;
  void			setStats(Stats *const stats);
};

#endif
