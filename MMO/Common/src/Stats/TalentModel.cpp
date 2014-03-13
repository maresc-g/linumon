//
// TalentModel.cpp for TalentModel in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Fri Jan 31 13:18:40 2014 alexis mestag
// Last update Wed Mar 12 13:45:24 2014 alexis mestag
//

#include			<functional>
#include			"Stats/TalentModel.hh"
#include			"Loader/LoaderManager.hh"

TalentModel::TalentModel() :
  Persistent(), Nameable(), _maxPoints(0), _effectLib(NULL)
{

}

TalentModel::TalentModel(std::string const &name) :
  Persistent(), Nameable(name), _maxPoints(0), _effectLib(NULL)
{

}

TalentModel::TalentModel(TalentModel const &rhs) :
  Persistent(rhs), Nameable(rhs), _effectLib(NULL)
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
    }
  return (*this);
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

void				TalentModel::deleteTalents()
{
  static std::function<bool(TalentModel *)>	talentsDeleter = [](TalentModel *t) -> bool {
    delete t;
    return (true);
  };

  _talents.remove_if(talentsDeleter);
}

void				TalentModel::addTalent(TalentModel const &talent)
{
  _talents.push_back(new TalentModel(talent));
}

void				TalentModel::addTalent(TalentModel *talent)
{
  _talents.push_back(talent);
}

void				TalentModel::setTalents(TalentModel const &talent)
{
  for (auto it = talent._talents.begin() ; it != talent._talents.end() ; ++it)
    {
      this->addTalent(**it);
    }
}

bool				TalentModel::serialization(Trame &trame) const
{
  bool				ret = true;

  trame["PTS"] = this->_maxPoints;
  for (auto it = this->_talents.begin() ; it != this->_talents.end() ; ++it)
    (*it)->serialization(trame(trame[(*it)->getName()]));
  return (ret);
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
  	    this->addTalent(model);
  	  TalentModel::deserializationTreeModel(trame(trame[*it]));
  	}
    }
  return (true);
}

TalentModel			*TalentModel::deserialization(Trame const &trame)
{
  TalentModel			*talentModel = NULL;

  talentModel = new TalentModel;
  talentModel->setMaxPoints(trame["PTS"].asUInt());

  // auto			otherMembers = trame.getMemberNames();

  // for (auto other = otherMembers.begin() ; other != otherMembers.end() ; ++other)
  //   {
  //     if (*other != "PTS")
  // 	{
  // 	  model = (**LoaderManager::getInstance()->getTalentModelLoader())->getValue(trame[*other].asString());
  // 	  if (model)
  // 	    talentModel->addTalent(*model);
  // 	  TalentModel::deserialization(trame(trame[*other]));
  // 	}
  //   }
  return (talentModel);
}
