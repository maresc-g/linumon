//
// AItem.hh for AItem in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 19:59:30 2013 alexis mestag
// Last update Mon Mar 10 14:05:26 2014 laurent ansel
//

#ifndef			__AITEM_HH__
# define		__AITEM_HH__

# include		<functional>
# include		"Entities/AEntity.hh"
# include		"Utility/ISerialization.hh"

class			AItem : public AEntity, public ISerialization
{
  friend class		odb::access;

public:
  typedef enum		eItem
    {
      NONE,
      STUFF,
      RESSOURCE,
      CONSUMABLE
    }			eItem;
private:
  eItem			_itemType;

protected:
  AItem();
  AItem(std::string const &name, AItem::eItem const type);
  AItem(std::string const &name, AItem::eItem const type, AEntity::eEntity const entity);
  AItem(AItem const &rhs);

  void			setItemType(AItem::eItem const type);

public:
  virtual ~AItem();

  AItem			&operator=(AItem const &rhs);
  AItem::eItem		getItemType() const;

  virtual bool		serialization(Trame &trame) const = 0;
  static AItem		*deserialization(Trame const &trame, bool const client = true);
  static AItem		*createCopy(AItem *rhs);
  static AItem		*createCopy(AItem const *rhs);
};

# ifdef	ODB_COMPILER
#  pragma db object(AItem) abstract
#  pragma db member(AItem::_itemType) transient
# endif


#endif
