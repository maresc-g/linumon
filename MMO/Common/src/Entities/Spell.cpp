//
// Spell.cpp for Spell in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Dec  5 22:54:34 2013 alexis mestag
// Last update Wed Mar  5 16:59:42 2014 laurent ansel
//

#include			"Entities/Spell.hh"
#include			"Effects/SpellEffect.hh"

Spell::Spell() :
  Persistent(), Nameable(""), _type(NULL), _power(0)
{

}

Spell::Spell(Spell const &rhs) :
  Persistent(rhs), Nameable(rhs)
{
  *this = rhs;
}

Spell::~Spell()
{

}

Spell				&Spell::operator=(Spell const &rhs)
{
  if (this != &rhs)
    {
      this->setType(rhs.getType());
      this->setPower(rhs.getPower());
    }
  return (*this);
}

void				Spell::operator()(Mob &caster, Mob &target)
{
#ifndef			CLIENT_COMPILATION

  static std::vector<std::type_info const *> const	typeTab = {
    &typeid(Mob),
  };
  IEffect			*effect = _effectLib->getEffect();
  SpellEffect			*sEffect = dynamic_cast<SpellEffect *>(effect);

  if (!sEffect) {
    std::cerr << "Bad cast in Spell::operator()" << std::endl;
    return ;
  }

  sEffect->initialize(caster, *this, target);
  sEffect->apply(target);

  delete effect;

#endif
  (void)caster;
  (void)target;
}

Type const			&Spell::getType() const
{
  return (*_type);
}

void				Spell::setType(Type const &type)
{
  _type = &type;
}

Spell::power_type		Spell::getPower() const
{
  return (_power);
}

void				Spell::setPower(Spell::power_type const power)
{
  _power = power;
}

int				Spell::getUseLimit() const
{
  return (_useLimit);
}

void				Spell::setUseLimit(int const useLimit)
{
  _useLimit = useLimit;
}

bool				Spell::serialization(Trame &trame) const
{
  bool				ret = true;

  //  trame["NAME"] = this->getName();
  this->_type->serialization(trame(trame[this->getName()]));
  trame[this->getName()]["POW"] = this->_power;
  return (ret);
}

Spell				*Spell::deserialization(Trame const &trame)
{
  Spell				*spell = new Spell;

  spell->setType(*Type::deserialization(trame));
  //  spell->setName(trame["NAME"].asString());
  spell->setPower(trame["POW"].asInt());
  return (spell);
}
