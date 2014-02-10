//
// Stuff.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Feb  6 15:41:47 2014 laurent ansel
// Last update Fri Feb  7 13:12:05 2014 laurent ansel
//

#ifndef 		__STUFF_HH__
# define 		__STUFF_HH__

# include		<functional>
# include		"Entities/AItem.hh"

class			Stuff : public AItem
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
      BREATSPLATE,
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

# endif

#endif
