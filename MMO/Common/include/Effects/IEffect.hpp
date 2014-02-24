//
// AEffect.hh for AEffect in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Jan 29 16:06:44 2014 alexis mestag
// Last update Sun Feb 23 23:00:40 2014 alexis mestag
//

#ifndef			__IEFFECT_HPP__
# define		__IEFFECT_HPP__

# include		"Entities/ACharacter.hh"

namespace		Effect
{
  enum			eType
    {
      NONE,
      MOB
    };
}

class			IEffect
{
protected:
  virtual ~IEffect() {}

public:
  virtual Effect::eType	getType() const = 0;
};

template<typename T>
class			AEffect : public IEffect
{
private:
  Effect::eType		_type;

private:
  void			setType(Effect::eType const type) { _type = type; }

protected:
  AEffect(Effect::eType const type = Effect::eType::NONE) : _type(type) {}

public:
  virtual ~AEffect() {}
  Effect::eType		getType() const { return (_type); }
  virtual bool		apply(T &character) = 0;
};

#endif
