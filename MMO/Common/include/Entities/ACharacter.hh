//
// ACharacter.hh for ACharacter in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Nov 28 23:33:45 2013 alexis mestag
// Last update Wed Mar 19 00:20:39 2014 alexis mestag
//

#ifndef			__ACHARACTER_HH__
# define		__ACHARACTER_HH__

# include		"Entities/AStatEntity.hh"
# include		"Entities/Levelable.hh"
# include		"Entities/Equipment.hh"
# include		"Stats/ExperienceCurve.hh"

class			ACharacter : public AStatEntity, public Levelable
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
  Equipment		*_equipment;
  bool			_inBattle;

private:
  void			setInBattle(bool const inBattle);

protected:
  ACharacter();
  ACharacter(std::string const &name, eCharacter const characterType);
  ACharacter(ACharacter const &rhs);

  ACharacter		&operator=(ACharacter const &rhs);

  void			setCharacterType(eCharacter const characterType);

public:
  virtual ~ACharacter();

  eCharacter		getCharacterType() const;

  void			resetExp(); // Will be useful only once

  /*
  ** Useful methods to level up
  */
#ifndef		CLIENT_COMPILATION
  virtual ExperienceCurve const	&getExperienceCurve() const = 0;
#endif
  virtual void			levelUp();

  Equipment const	&getEquipment() const;
  void			setEquipment(Equipment const &equipment);
  void			setEquipment(Equipment *equipment);

  bool 			addStuff(Stuff *item, Stuff *&old);
  bool 			addStuff(Stuff::eStuff const item, Stuff *&old);
  bool 			getStuff(Stuff *&old, unsigned int const item);

  /*
  ** Battle management
  */
  bool			isInBattle() const;
  virtual void		enterBattle();
  virtual void		leaveBattle();
};

# ifdef	ODB_COMPILER
#  pragma db object(ACharacter) abstract
#  pragma db member(ACharacter::_characterType) transient
#  pragma db member(ACharacter::_equipment) transient
#  pragma db member(ACharacter::_inBattle) transient
#  pragma db member(ACharacter::currentExp) virtual (Levelable::type) get(getCurrentExp()) set(setCurrentExp((?), false))
#  pragma db member(ACharacter::level) virtual(Levelable::type) get(getLevel()) set(setLevel(?))
#  pragma db member(ACharacter::exp) virtual(Levelable::type) get(getExp()) set(setExp(?))
#  pragma db member(ACharacter::equipment) virtual(Equipment::container_type) get(_equipment->getContainer()) set(_equipment->setContainer(?))
# endif

#endif
