//
// AItem.hh for AItem in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 19:59:30 2013 alexis mestag
// Last update Thu Nov 28 21:17:49 2013 alexis mestag
//

#ifndef			__AITEM_HH__
# define		__AITEM_HH__

# include		"Entities/AEntity.hh"

class			AItem : public AEntity
{
public:
  AItem();
  AItem(std::string const &name);
  AItem(AItem const &rhs);
  virtual ~AItem();

  AItem			&operator=(AItem const &rhs);
};

#endif
