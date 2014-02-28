//
// Craft.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb  7 13:40:15 2014 laurent ansel
// Last update Fri Feb 28 12:24:33 2014 laurent ansel
//

#include			<sstream>
#include			"Entities/Craft.hh"

Craft::Craft():
  Persistent(),
  Nameable(),
  _result(NULL)
{
}

Craft::~Craft()
{
}

Craft::Craft(Craft const &rhs):
  Persistent(rhs),
  Nameable(rhs)
{
  *this = rhs;
}

Craft				&Craft::operator=(Craft const &rhs)
{
  if (this != &rhs)
    {
      this->setLevel(rhs.getLevel());
      this->setIngredients(rhs.getIngredients());
      this->setResult(rhs.getResult());
    }
  return (*this);
}

std::list<std::pair<AItem *, unsigned int> > const	&Craft::getIngredients() const
{
  return (this->_ingredients);
}

void				Craft::setIngredients(std::list<std::pair<AItem *, unsigned int> > const &list)
{
  this->_ingredients = list;
}

Level const			&Craft::getLevel() const
{
  return (this->_level);
}

void				Craft::setLevel(Level const &level)
{
  this->_level = level;
}

AItem const			&Craft::getResult() const
{
  return (*this->_result);
}

void				Craft::setResult(AItem const &result)
{
  this->_result = &result;
}

bool				Craft::serialization(Trame &trame) const
{
  bool				ret = true;
  int				nb = 0;
  std::ostringstream		str;

  trame/*["CRAFT"]*/["NAME"] = this->getName();
  trame/*["CRAFT"]*/["INGREDIENTS"];
  this->_level.serialization(trame(trame/*["CRAFT"]*/));
  this->_result->serialization(trame(trame/*["CRAFT"]*/["RESULT"]));
  for (auto it = this->_ingredients.begin() ; it != this->_ingredients.end() && ret; ++it)
    {
      str <<  nb;
      ret = it->first->serialization(trame(trame/*["CRAFT"]*/["INGREDIENTS"][str.str()]));
      trame/*["CRAFT"]*/["INGREDIENTS"][str.str()]["NB"] = it->second;
      trame/*["CRAFT"]*/["INGREDIENTS"][str.str()].removeMember("COORDINATE");
      trame/*["CRAFT"]*/["INGREDIENTS"][str.str()].removeMember("VISIBLE");
      str.str("");
      nb++;
    }
  return (ret);
}

Craft				*Craft::deserialization(Trame const &trame, bool const client)
{
  Craft				*craft = NULL;
  std::list<std::pair<AItem *, unsigned int> >		*ingredients;
  AItem				*item;

  // if (trame.isMember("CRAFT"))
  //   {
      craft = new Craft;
      craft->setName(trame/*["CRAFT"]*/["NAME"].asString());
      craft->setLevel(*Level::deserialization(trame(trame/*["CRAFT"]*/)));
      craft->setResult(*AItem::deserialization(trame(trame/*["CRAFT"]*/["RESULT"])));
      ingredients = new std::list<std::pair<AItem *, unsigned int> >;
      auto			members = trame/*["CRAFT"]*/["INGREDIENTS"].getMemberNames();

      for (auto it = members.begin() ; it != members.end() ; ++it)
	{
	  if ((item = AItem::deserialization(trame(trame/*["CRAFT"]*/["INGREDIENTS"][*it]), client)))
	    ingredients->push_back(std::make_pair(item, trame/*["CRAFT"]*/["INGREDIENTS"][*it]["NB"].asUInt()));
	}
      craft->setIngredients(*ingredients);
    // }
  return (craft);
}
