//
// Craft.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb  7 13:40:15 2014 laurent ansel
// Last update Fri Feb  7 14:42:28 2014 laurent ansel
//

#include			<sstream>
#include			"Entities/Craft.hh"

Craft::Craft():
  Nameable(""),
  Persistent(),
  _result(NULL)
{
}

Craft::~Craft()
{
}

Craft::Craft(Craft const &rhs):
  Nameable(""),
  Persistent(rhs)
{
  *this = rhs;
}

Craft				&Craft::operator=(Craft const &rhs)
{
  if (this != &rhs)
    {

    }
  return (*this);
}

std::list<AItem *> const	&Craft::getIngredients() const
{
  return (this->_ingredients);
}

void				Craft::setIngredients(std::list<AItem *> const &list)
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
  *this->_result = result;
}

bool				Craft::serialization(Trame &trame) const
{
  bool				ret = true;
  int				nb = 0;
  std::ostringstream		str;

  trame["CRAFT"]["INGREDIENTS"];
  this->_level.serialization(trame(trame["CRAFT"]));
  this->_result->serialization(trame(trame["CRAFT"]));
  for (auto it = this->_ingredients.begin() ; it != this->_ingredients.end() && ret; ++it)
    {
      str << "ITEM" << nb;
      ret = (*it)->serialization(trame(trame["CRAFT"]["INGREDIENTS"][str.str()]));
      str.str("");
      nb++;
    }
  return (ret);
}

Craft				*Craft::deserialization(Trame const &trame)
{
  Craft				*craft = NULL;
  int				nb = 0;
  std::ostringstream		str;
  std::list<AItem *>		*ingredients;

  if (trame.isMember("CRAFT"))
    {
      craft = new Craft;
      craft->setLevel(*Level::deserialization(trame(trame["CRAFT"])));
      craft->setResult(*AItem::deserialization(trame(trame["CRAFT"])));
      ingredients = new std::list<AItem *>;
      str << "ITEM" << nb;
      for (; !trame["CRAFT"]["INGREDIENTS"].isMember(str.str()) ; ++nb)
	{
	  ingredients->push_back(AItem::deserialization(trame(trame["CRAFT"]["INGREDIENTS"][str.str()])));
	  str.str("");
	  str << "ITEM" << nb + 1;
	}
      craft->setIngredients(*ingredients);
    }
  return (craft);
}
