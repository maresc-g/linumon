//
// Drop.hh for toto in /home/maitre_c/work/linumon/MMO/Common
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Mon Mar 10 14:57:05 2014 antoine maitre
// Last update Fri Mar 14 21:48:22 2014 alexis mestag
//

#ifndef				__DROP_HH__
# define			__DROP_HH__

# include			"Entities/Inventory.hh"

class				Drop : public Inventory
{
public:
  Drop();
  Drop(Drop const &rhs);
  virtual ~Drop();

  Drop				&operator=(Drop const &rhs);
};

#endif
