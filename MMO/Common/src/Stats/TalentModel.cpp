//
// TalentModel.cpp for TalentModel in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Fri Jan 31 13:18:40 2014 alexis mestag
// Last update Tue Mar 25 22:43:11 2014 alexis mestag
//

#include			<functional>
#include			"Effects/TalentEffect.hh"
#include			"Stats/TalentModel.hh"
#include			"Loader/LoaderManager.hh"

TalentModel::TalentModel() :
  Persistent(), Nameable(), _maxPoints(0), _effectLib(NULL), _parent(NULL),
  _description("")
{

}

TalentModel::TalentModel(std::string const &name) :
  Persistent(), Nameable(name), _maxPoints(0), _effectLib(NULL), _parent(NULL),
  _description("")
{

}

TalentModel::TalentModel(TalentModel const &rhs) :
  Persistent(rhs), Nameable(rhs), _effectLib(NULL), _parent(NULL)
{
  *this = rhs;
}

TalentModel::~TalentModel()
{

}

TalentModel			&TalentModel::operator=(TalentModel const &rhs)
{
  if (this != &rhs)
    {
      this->setMaxPoints(rhs.getMaxPoints());
      this->setEffectLib(rhs.getEffectLib());
      this->setTalents(rhs.getTalents());
      this->setParent(rhs.getParent());
      this->setDescription(rhs.getDescription());
    }
  return (*this);
}

bool				TalentModel::operator==(TalentModel const &rhs) const
{
  return (this == &rhs ? true : this->getName() == rhs.getName());
}

bool				TalentModel::operator!=(TalentModel const &rhs) const
{
  return (!(*this == rhs));
}

TalentModel::point_type		TalentModel::getMaxPoints() const
{
  return (_maxPoints);
}

void				TalentModel::setMaxPoints(point_type const maxPoints)
{
  _maxPoints = maxPoints;
}

EffectLib const			&TalentModel::getEffectLib() const
{
  return (*_effectLib);
}

void				TalentModel::setEffectLib(EffectLib const &effectLib)
{
  if (!_effectLib) {
    _effectLib = new EffectLib(effectLib);
  }
  else
    _effectLib = &effectLib;
}

bool				TalentModel::applyEffect(Player &player, unsigned int const fromPts,
							 unsigned int const toPts) const
{
  IEffect			*effect = this->getEffectLib().getEffect();
  TalentEffect			*tEffect = dynamic_cast<TalentEffect *>(effect);
  bool				ret = false;

  if (tEffect) {
    tEffect->apply(player, fromPts, toPts);
    ret = true;
  }
  else
    std::cerr << "Bad cast in TalentModel::applyEffect()" << std::endl;
  return (ret);
}

void				TalentModel::addTalent(TalentModel const &talent)
{
  _talents.push_back(&talent);
}

void				TalentModel::setTalents(std::list<TalentModel const *> const &talents)
{
  for (auto it = talents.begin() ; it != talents.end() ; ++it)
    this->addTalent(**it);
}

std::list<TalentModel const *> const	&TalentModel::getTalents() const
{
  return (_talents);
}

TalentModel const		*TalentModel::getParent() const
{
  return (_parent);
}

void				TalentModel::setParent(TalentModel const *parent)
{
  _parent = parent;
}

std::string const		&TalentModel::getDescription() const
{
  return (_description);
}

void				TalentModel::setDescription(std::string const &description)
{
  _description = description;
}

bool				TalentModel::serialization(Trame &trame) const
{
  bool				ret = true;
  std::ostringstream		str;
  unsigned int			nb = 0;

  trame["NAME"] = this->getName();
  trame["PTS"] = this->_maxPoints;
  if (_parent)
    trame["PARENT"] = _parent->getName();
  for (auto it = this->_talents.begin() ; it != this->_talents.end() ; ++it)
    {
      str << nb;
      trame["TALENTS"][str.str()] = (*it)->getName();
      str.str("");
      nb++;
    }
  return (ret);
}

TalentModel			*TalentModel::deserialization(Trame const &trame)
{
  TalentModel			*talentModel = NULL;
  auto				members = trame["TALENTS"].getMemberNames();

  talentModel = new TalentModel(trame["NAME"].asString());
  talentModel->setMaxPoints(trame["PTS"].asUInt());
  /*
  ** The rest of the TalentModel will be initialized by TalentModelLoader::deserialization
  */
  // TalentModel			*toAdd;
  // toAdd = (**LoaderManager::getInstance()->getTalentModelLoader())
  //   ->getValue(trame["PARENT"].asString());
  // talentModel->setParent(toAdd);
  // for (auto it = members.begin() ; it != members.end() ; ++it) {
  //   toAdd = (**LoaderManager::getInstance()->getTalentModelLoader())
  //     ->getValue(trame["TALENTS"][*it].asString());
  //   if (toAdd)
  //     talentModel->addTalent(toAdd);
  // }
  return (talentModel);
}

bool				TalentModel::deserializationTreeModel(Trame const &trame)
{
  auto				members = trame.getMemberNames();
  TalentModel			*model;

  for (auto it = members.begin() ; it != members.end() ; ++it)
    {
      if (*it != "PTS")
  	{
  	  model = (**LoaderManager::getInstance()->getTalentModelLoader())->getValue(*it);
  	  if (model)
  	    this->addTalent(*model);
  	  TalentModel::deserializationTreeModel(trame(trame[*it]));
  	}
    }
  return (true);
}
