//
// LoaderManager.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Wed Mar  5 15:04:36 2014 laurent ansel
// Last update Fri Mar 14 22:42:38 2014 laurent ansel
//

#include			<functional>
#include			"Trame/Trame.hh"
#include			"Loader/LoaderManager.hh"

LoaderManager::LoaderManager():
  _spells(new MutexVar<SpellLoader *>(NULL)),
  _stuffs(new MutexVar<StuffLoader *>(NULL)),
  _consumables(new MutexVar<ConsumableLoader *>(NULL)),
  _ressources(new MutexVar<RessourceLoader *>(NULL)),
  _authorizedStatKeys(new MutexVar<AuthorizedStatKeyLoader *>(NULL)),
  _heals(new MutexVar<HealLoader *>(NULL)),
  _talentModels(new MutexVar<TalentModelLoader *>(NULL)),
  _jobModels(new MutexVar<JobModelLoader *>(NULL)),
  _mobModels(new MutexVar<MobModelLoader *>(NULL))

{

}

LoaderManager::~LoaderManager()
{
  delete _spells;
  delete _mobModels;
  delete _jobModels;
  delete _stuffs;
  delete _consumables;
  delete _talentModels;
  delete _heals;
  delete _ressources;
  delete _authorizedStatKeys;
}

void				LoaderManager::init()
{
  _spells->setVar(new SpellLoader);
  _stuffs->setVar(new StuffLoader);
  _consumables->setVar(new ConsumableLoader);
  _heals->setVar(new HealLoader);
  _ressources->setVar(new RessourceLoader);
  _authorizedStatKeys->setVar(new AuthorizedStatKeyLoader);
  _talentModels->setVar(new TalentModelLoader);
  _jobModels->setVar(new JobModelLoader);
  _mobModels->setVar(new MobModelLoader);
}

MutexVar<MobModelLoader *>	*LoaderManager::getMobModelLoader() const
{
  return (this->_mobModels);
}

MutexVar<JobModelLoader *>	*LoaderManager::getJobModelLoader() const
{
  return (this->_jobModels);
}

MutexVar<StuffLoader *>		*LoaderManager::getStuffLoader() const
{
  return (this->_stuffs);
}

MutexVar<ConsumableLoader *>	*LoaderManager::getConsumableLoader() const
{
  return (this->_consumables);
}

MutexVar<SpellLoader *>		*LoaderManager::getSpellLoader() const
{
  return (this->_spells);
}

MutexVar<TalentModelLoader *>	*LoaderManager::getTalentModelLoader() const
{
  return (this->_talentModels);
}

MutexVar<HealLoader *>		*LoaderManager::getHealLoader() const
{
  return (this->_heals);
}

MutexVar<RessourceLoader *>	*LoaderManager::getRessourceLoader() const
{
  return (this->_ressources);
}

MutexVar<AuthorizedStatKeyLoader *>	*LoaderManager::getAuthorizedStatKeyLoader() const
{
  return (this->_authorizedStatKeys);
}

AItem				*LoaderManager::getItemLoader(std::string const &name) const
{
  AItem				*item;

  if (!(item = (**getStuffLoader())->getValue(name)))
    if (!(item = (**getConsumableLoader())->getValue(name)))
      item = (**getRessourceLoader())->getValue(name);
  return (item);
}

bool				LoaderManager::setMobModelLoader(Trame *trame)
{
  return ((**_mobModels)->deserialization(*trame));
}

bool				LoaderManager::setJobModelLoader(Trame *trame)
{
  return ((**_jobModels)->deserialization(*trame));
}

bool				LoaderManager::setStuffLoader(Trame *trame)
{
  return ((**_stuffs)->deserialization(*trame));
}

bool				LoaderManager::setConsumableLoader(Trame *trame)
{
  return ((**_consumables)->deserialization(*trame));
}

bool				LoaderManager::setSpellLoader(Trame *trame)
{
  return ((**_spells)->deserialization(*trame));
}

bool				LoaderManager::setTalentModelLoader(Trame *trame)
{
  return ((**_talentModels)->deserialization(*trame));
}

bool				LoaderManager::setHealLoader(Trame *trame)
{
  return ((**_heals)->deserialization(*trame));
}

bool				LoaderManager::setRessourceLoader(Trame *trame)
{
  return ((**_ressources)->deserialization(*trame));
}

bool				LoaderManager::setAuthorizedStatKeyLoader(Trame *trame)
{
  return ((**_authorizedStatKeys)->deserialization(*trame));
}

void				LoaderManager::initReception(Protocol &protocol) const
{
  std::function<bool (Trame *)> func;

  func = std::bind1st(std::mem_fun(&LoaderManager::setMobModelLoader), this);
  protocol.addFunc("MOBMODELS", func);

  func = std::bind1st(std::mem_fun(&LoaderManager::setJobModelLoader), this);
  protocol.addFunc("JOBMODELS", func);

  func = std::bind1st(std::mem_fun(&LoaderManager::setStuffLoader), this);
  protocol.addFunc("STUFFS", func);

  func = std::bind1st(std::mem_fun(&LoaderManager::setConsumableLoader), this);
  protocol.addFunc("CONSUMABLES", func);

  func = std::bind1st(std::mem_fun(&LoaderManager::setSpellLoader), this);
  protocol.addFunc("SPELLSLIST", func);

  func = std::bind1st(std::mem_fun(&LoaderManager::setTalentModelLoader), this);
  protocol.addFunc("TALENTMODELS", func);

  func = std::bind1st(std::mem_fun(&LoaderManager::setRessourceLoader), this);
  protocol.addFunc("RESSOURCES", func);

  func = std::bind1st(std::mem_fun(&LoaderManager::setHealLoader), this);
  protocol.addFunc("HEALS", func);

  func = std::bind1st(std::mem_fun(&LoaderManager::setAuthorizedStatKeyLoader), this);
  protocol.addFunc("AUTHORIZEDSTATKEYSLIST", func);
}
