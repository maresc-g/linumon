//
// TalentModel.cpp for TalentModel in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Fri Jan 31 13:18:40 2014 alexis mestag
// Last update Mon Feb 10 14:53:38 2014 laurent ansel
//

#include			<functional>
#include			"Stats/TalentModel.hh"

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
  delete _effectLib;
  this->deleteTalents();
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

int				TalentModel::getMaxPoints() const
{
  return (_maxPoints);
}

void				TalentModel::setMaxPoints(int const maxPoints)
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

  trame[this->getName()]["PTS"] = this->_maxPoints;
  this->_effectLib->serialization(trame(trame[this->getName()]));
  for (auto it = this->_talents.begin() ; it != this->_talents.end() ; ++it)
    (*it)->serialization(trame(trame[this->getName()]));
  return (ret);
}

TalentModel			*TalentModel::deserialization(Trame const &trame)
{
  TalentModel			*talentModel = NULL;
  auto				members = trame.getMemberNames();

  for (auto it = members.begin() ; it != members.end() ; ++it)
    {
      talentModel = new TalentModel;
      talentModel->setName(*it);
      talentModel->setMaxPoints(trame[*it]["PTS"].asInt());
      talentModel->setEffectLib(*EffectLib::deserialization(trame(trame[*it])));

      auto			otherMembers = trame[(*it)].getMemberNames();

      for (auto other = otherMembers.begin() ; other != otherMembers.end() ; ++other)
	talentModel->addTalent(*TalentModel::deserialization(trame(trame[*it])));
    }
  return (talentModel);
}
