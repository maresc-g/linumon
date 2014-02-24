//
// ACharacter.hh for ACharacter in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 23:33:45 2013 alexis mestag
// Last update Mon Feb 24 14:33:36 2014 alexis mestag
//

#ifndef			__ACHARACTER_HH__
# define		__ACHARACTER_HH__

# include		"Entities/AStatEntity.hh"
# include		"Entities/Level.hh"
# include		"Entities/Equipment.hh"

class			ACharacter : public AStatEntity
{
  friend class		odb::access;

public:
  typedef enum		eCharacter
    {
      NONE,
      PLAYER,
      MOB
    }			eCharacter;

private:
  eCharacter		_characterType;
  int			_currentExp;
  Level			_level;
  Equipment		_equipment;

protected:
  ACharacter();
  ACharacter(std::string const &name, eCharacter const characterType);
  ACharacter(ACharacter const &rhs);

  ACharacter		&operator=(ACharacter const &rhs);

  void			setCharacterType(eCharacter const characterType);

public:
  virtual ~ACharacter();

  eCharacter		getCharacterType() const;

  int			getCurrentExp() const;
  void			setCurrentExp(int const currentExp);

  Level const		&getLevel() const;
  void			setLevel(Level const &level);
  void			levelUp();

  Equipment const	&getEquipment() const;
  void			setEquipment(Equipment const &equipment);
  void			setEquipment(Equipment *equipment);

  bool 			addStuff(Stuff *item, Stuff *&old);
  bool 			addStuff(Stuff::eStuff const item, Stuff *&old);
  bool 			getStuff(Stuff *&old, unsigned int const item);
};

# ifdef	ODB_COMPILER
#  pragma db object(ACharacter) abstract
#  pragma db member(ACharacter::_characterType) transient
#  pragma db member(ACharacter::_equipment)
# endif

#endif
