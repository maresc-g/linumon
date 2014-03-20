//
// MobModel.cpp for MobModel in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Fri Jan 24 18:39:45 2014 alexis mestag
// Last update Thu Mar 20 14:03:14 2014 alexis mestag
//

#include			"Entities/MobModel.hh"
#include			"Loader/LoaderManager.hh"
#include			"ObjectPool/ObjectPoolManager.hpp"

MobModel::MobModel() :
  Persistent(), AStatEntity("", eStatEntity::MOBMODEL),
  _spells(new Spells), _carcass(new Carcass),
  _expSeed(0), _dropPath(""), _drop(new Drop),
  _catchRate(0)
#ifndef		CLIENT_COMPILATION
  , _expCurve(NULL)
#endif
{

}

MobModel::MobModel(MobModel const &rhs) :
  Persistent(rhs), AStatEntity(rhs),
  _spells(new Spells), _carcass(new Carcass),
  _expSeed(0), _dropPath(""), _drop(new Drop),
  _catchRate(0)
#ifndef		CLIENT_COMPILATION
  , _expCurve(NULL)
#endif
{
  *this = rhs;
}

MobModel::~MobModel()
{
  delete _spells;
  delete _carcass;
  delete _drop;
}

MobModel			&MobModel::operator=(MobModel const &rhs)
{
  if (this != &rhs)
    {
      this->setType(rhs.getType());
      this->setSpells(rhs.getSpells());
      this->setCarcass(rhs.getCarcass());
      this->setExpSeed(rhs.getExpSeed());
      this->setDropPath(rhs.getDropPath());
      /* Useless to set this->_drop : it will be initialiazed when setting the Drop path (see above) */
      this->setCatchRate(rhs.getCatchRate());
#ifndef		CLIENT_COMPILATION
      this->setExperienceCurve(rhs.getExperienceCurve());
#endif
    }
  return (*this);
}

Type const			&MobModel::getType() const
{
  return (*_type);
}

void				MobModel::setType(Type const &type)
{
  _type = &type;
}

Carcass const			&MobModel::getCarcass() const
{
  return (*_carcass);
}

void				MobModel::setCarcass(Carcass const &carcass)
{
  *_carcass = carcass;
}

Carcass				*MobModel::getNewCarcass() const
{
  return (new Carcass(this->getCarcass()));
}

Spells const			&MobModel::getSpells() const
{
  return (*_spells);
}

void				MobModel::setSpells(Spells const &spells)
{
  *this->_spells = spells;
}

#ifndef		CLIENT_COMPILATION
ExperienceCurve const		&MobModel::getExperienceCurve() const
{
  return (*_expCurve);
}

void				MobModel::setExperienceCurve(ExperienceCurve const &expCurve)
{
  _expCurve = &expCurve;
}
#endif

unsigned int			MobModel::getExpSeed() const
{
  return (_expSeed);
}

void				MobModel::setExpSeed(unsigned int const expSeed)
{
  _expSeed = expSeed;
}

std::string const		&MobModel::getDropPath() const
{
  return (_dropPath);
}

void				MobModel::setDropPath(std::string const &dropPath)
{
  _dropPath = dropPath;
  this->loadDrop();
}

bool				MobModel::loadDrop()
{
  Trame				*file;
  bool				ret = false;

  ObjectPoolManager::getInstance()->setObject(file, "trame");
  if (JsonFile::readFile(*file, this->getDropPath())) {
      _drop->clear();

      auto			membersNb = file->getMemberNames();
      AItem			*item;

      for (auto nbt = membersNb.begin() ; nbt != membersNb.end() ; ++nbt) {
	auto			members = (*file)[*nbt].getMemberNames();

	for (auto it = members.begin() ; it != members.end() ; ++it) {
	  item = LoaderManager::getInstance()->getItemLoader(*it);
	  if (item)
	    _drop->addItem(item, (*file)[*nbt][*it].asUInt());
	}
      }
      ret = true;
    }
  return (ret);
}

Drop const			&MobModel::getDrop() const
{
  return (*_drop);
}

void				MobModel::setDrop(Drop const &drop)
{
  *_drop = drop;
}

unsigned int			MobModel::getCatchRate() const
{
  return (_catchRate);
}

void				MobModel::setCatchRate(unsigned int const catchRate)
{
  _catchRate = catchRate;
}

bool				MobModel::serialization(Trame &trame) const
{
  bool				ret = true;

  this->getType().serialization(trame(trame));
  this->getStats().serialization(trame(trame["STATS"]));
  this->getSpells().serialization(trame(trame));
  trame["KEY"] = this->getAuthorizedStatKeys().getName();
  this->_carcass->serialization(trame(trame["CAR"]));
  trame["CATCHRATE"] = this->getCatchRate();
  return (ret);
}

MobModel			*MobModel::deserialization(Trame const &trame)
{
  MobModel			*model = NULL;

  model = new MobModel;
  if (trame.isMember("KEY"))
    model->setAuthorizedStatKeys(*(**LoaderManager::getInstance()->getAuthorizedStatKeyLoader())->getValue(trame["KEY"].asString()));

  if (trame.isMember("CAR"))
    {
      Carcass			*carcass = Carcass::deserialization(trame(trame["CAR"]));
      if (carcass)
	  model->setCarcass(*carcass);
    }
  model->setCatchRate(trame["CATCHRATE"].asUInt());
  model->setType(*Type::deserialization(trame(trame)));
  model->setSpells(*Spells::deserialization(trame(trame)));
  model->setStats(*Stats::deserialization(trame(trame["STATS"])));
  return (model);
}
