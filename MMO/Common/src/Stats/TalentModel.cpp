//
// TalentModel.cpp for TalentModel in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Fri Jan 31 13:18:40 2014 alexis mestag
// Last update Sat Feb  1 16:48:42 2014 alexis mestag
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
