//
// Stuff.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Feb  6 15:41:47 2014 laurent ansel
// Last update Tue Feb 11 16:07:55 2014 alexis mestag
//

#ifndef 		__STUFF_HH__
# define 		__STUFF_HH__

# include		<functional>
# include		"Database/Persistent.hh"
# include		"Entities/AItem.hh"

class			Stuff : public Persistent, public AItem
{
  friend class		odb::access;

public:
  typedef enum		eStuff
    {
      NONE,
      HELMET,
      SHOULDERS,
      RING,
      NECKLACE,
      BOOTS,
      CLOAK,
      BREASTPLATE,
      BELT
    }			eStuff;
private:
  eStuff		_stuffType;

protected:
  Stuff();
  Stuff(std::string const &name, eStuff const stuffType);
  Stuff(Stuff const &rhs);

  Stuff			&operator=(Stuff const &rhs);

  Stuff::eStuff		getStuffType() const;
  void			setStuffType(eStuff const stuffType);

public:
  virtual ~Stuff();

  virtual bool		serialization(Trame &trame) const;
  static Stuff		*deserialization(Trame const &trame);
};

# ifdef	ODB_COMPILER
#  pragma db object(Stuff)
# endif

#endif
