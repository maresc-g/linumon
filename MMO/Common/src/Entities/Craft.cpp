//
// Craft.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Feb  7 13:40:15 2014 laurent ansel
// Last update Fri Mar 14 12:51:27 2014 laurent ansel
//

#include			<sstream>
#include			"Entities/Craft.hh"
#include			"Loader/LoaderManager.hh"

Craft::Craft():
  Persistent(),
  Nameable(),
  ContainerWrapper<container_type>(),
  _level(new Level),
  _result(NULL)
{
}

Craft::~Craft()
{
  delete _level;
}

Craft::Craft(Craft const &rhs):
  Persistent(rhs),
  Nameable(rhs),
  ContainerWrapper<container_type>(),
  _level(new Level),
  _result(NULL)
{
  *this = rhs;
}

Craft				&Craft::operator=(Craft const &rhs)
{
  if (this != &rhs)
    {
      this->setLevelObject(rhs.getLevelObject());
      this->setIngredients(rhs.getIngredients());
      this->setResult(rhs.getResult());
    }
  return (*this);
}

Craft::container_type const	&Craft::getIngredients() const
{
  return (this->getContainer());
}

void				Craft::setIngredients(container_type const &list)
{
  this->setContainer(list);
}

Level const			&Craft::getLevelObject() const
{
  return (*this->_level);
}

void				Craft::setLevelObject(Level const &level)
{
  if (!_level)
    this->_level = new Level(level);
  else
    *this->_level = level;
}

Level::type			Craft::getLevel() const
{
  return (_level->getLevel());
}

void				Craft::setLevel(Level::type const level)
{
  _level->setLevel(level);
}

Level::type			Craft::getExp() const
{
  return (_level->getExp());
}

void				Craft::setExp(Level::type const exp)
{
  _level->setExp(exp);
}

Stack<AItem> const		&Craft::getResult() const
{
  return (*this->_result);
}

void				Craft::setResult(Stack<AItem> const &result)
{
  this->_result = &result;
}

bool				Craft::serialization(Trame &trame) const
{
  bool				ret = true;
  // int				nb = 0;
  // std::ostringstream		str;

  trame["NAME"] = this->getName();
  trame["INGS"];
  this->_level->serialization(trame);
  // this->_result->serialization(trame(trame["RES"]));
  trame["RES"] = this->_result->getItem()->getName();
  for (auto it = this->begin() ; it != this->end() && ret; ++it)
    {
      trame["INGS"][(*it)->getItem()->getName()] = (*it)->getNb();
      // str <<  nb;
      // ret = it->first->serialization(trame(trame["INGS"][str.str()]));
      // trame["INGS"][str.str()]["NB"] = it->second;
      // trame["INGS"][str.str()].removeMember("COORDINATE");
      // trame["INGS"][str.str()].removeMember("VIS");
      // str.str("");
      // nb++;
    }
  return (ret);
}

Craft				*Craft::deserialization(Trame const &trame, bool const)
{
  Craft				*craft = NULL;
  container_type		*ingredients;
  AItem				*item;

  craft = new Craft;
  craft->setName(trame["NAME"].asString());
  craft->setLevelObject(*Level::deserialization(trame(trame)));
  item = LoaderManager::getInstance()->getItemLoader(trame["RES"].asString());
  if (item)
    craft->setResult(*new Stack<AItem>(0, item, 1));
  // craft->setResult(*AItem::deserialization(trame(trame["RES"]), client));
  ingredients = new container_type;
  auto			members = trame["INGS"].getMemberNames();

  for (auto it = members.begin() ; it != members.end() ; ++it)
    {
      item = LoaderManager::getInstance()->getItemLoader(*it);
      if (item)
	ingredients->push_back(new Stack<AItem>(0, item, trame["INGS"][*it].asUInt()));
      // if ((item = AItem::deserialization(trame(trame["INGS"][*it]), client)))
      // 	ingredients->push_back(std::make_pair(item, trame["INGS"][*it]["NB"].asUInt()));
    }
   craft->setIngredients(*ingredients);
  return (craft);
}
