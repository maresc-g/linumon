//
// Drop.hh for toto in /home/maitre_c/work/linumon/MMO/Common
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Mon Mar 10 14:57:05 2014 antoine maitre
// Last update Fri Mar 14 11:51:21 2014 alexis mestag
//

#ifndef				__DROP_HH__
# define			__DROP_HH__

#include			"Entities/Player.hh"
#include			"Database/Persistent.hh"

class				Drop : public Persistent, public ContainerWrapper<std::list<AItem *> >
{
  friend class			odb::access;

private:
  unsigned int			_money;
  unsigned int			_exp;

private:
  void				setMoney(int const money);
  void				setExp(int const exp);

public:
  Drop();
  virtual ~Drop();

  int				getMoney() const;
  int				getExp() const;
};

# ifdef ODB_COMPILER
#  pragma db object(Drop)
#endif

#endif
