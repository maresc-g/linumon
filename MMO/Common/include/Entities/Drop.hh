//
// Drop.hh for toto in /home/maitre_c/work/linumon/MMO/Common
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Mon Mar 10 14:57:05 2014 antoine maitre
// Last update Tue Mar 11 21:38:14 2014 alexis mestag
//

#ifndef				__DROP_HH__
# define			__DROP_HH__

#include			"Entities/Player.hh"
#include			"Database/Persistent.hh"

class				Drop : public Persistent, public ContainerWrapper<std::list<AItem *>>
{
  friend class			odb::access;

 private:
  int				_money;
  int				_exp;

public:
  Drop();
  ~Drop();

  void				setMoney(int const);
  void				setExp(int const);
  int				getMoney() const;
  int				getExp() const;
};

# ifdef ODB_COMPILER
#  pragma db object(Drop)
#endif

#endif
