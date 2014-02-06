//
// AItem.hh for AItem in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 19:59:30 2013 alexis mestag
// Last update Thu Feb  6 16:20:57 2014 laurent ansel
//

#ifndef			__AITEM_HH__
# define		__AITEM_HH__

# include		<functional>
# include		"Entities/AEntity.hh"

class			AItem : public AEntity
{
  friend class		odb::access;

public:
  typedef enum		eItem
    {
      NONE,
      STUFF
    }			eItem;
private:
  eItem			_itemType;

protected:
  AItem();
  AItem(std::string const &name, AItem::eItem const type);
  AItem(AItem const &rhs);
  virtual ~AItem();

  AItem			&operator=(AItem const &rhs);

  AItem::eItem		getItemType() const;
  void			setItemType(AItem::eItem const type);
};

# ifdef	ODB_COMPILER
// #  pragma db object(AItem) abstract
// #  pragma db member(AItem::_itemType) transient
# endif


#endif
