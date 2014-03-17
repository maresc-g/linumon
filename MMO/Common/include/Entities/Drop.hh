//
// Drop.hh for toto in /home/maitre_c/work/linumon/MMO/Common
// 
// Made by antoine maitre
// Login   <maitre_c@epitech.net>
// 
// Started on  Mon Mar 10 14:57:05 2014 antoine maitre
// Last update Sun Mar 16 18:20:40 2014 alexis mestag
//

#ifndef				__DROP_HH__
# define			__DROP_HH__

# include			"Entities/AItem.hh"
# include			"Entities/Stack.hh"
# include			"Utility/Wrapper.hpp"

class				Drop : public ContainerWrapper<std::list<Stack<AItem> > >
{
public:
  Drop();
  Drop(Drop const &rhs);
  virtual ~Drop();

  Drop				&operator=(Drop const &rhs);

public:
  void				clear();
  void				addItem(AItem *item, unsigned int const nb);
};

#endif
