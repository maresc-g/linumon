//
// LoaderManager.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Wed Mar  5 15:04:36 2014 laurent ansel
// Last update Thu Mar  6 14:39:16 2014 laurent ansel
//

#include			<functional>
#include			"Trame/Trame.hh"
#include			"Loader/LoaderManager.hh"

LoaderManager::LoaderManager():
  _mobModels(new MutexVar<MobModelLoader *>(new MobModelLoader)),
  _jobModels(new MutexVar<JobModelLoader *>(new JobModelLoader)),
  _stuffs(new MutexVar<StuffLoader *>(new StuffLoader)),
  _consumables(new MutexVar<ConsumableLoader *>(new ConsumableLoader)),
  _ressources(new MutexVar<RessourceLoader *>(new RessourceLoader)),
  _authorizedStatKeys(new MutexVar<AuthorizedStatKeyLoader *>(new AuthorizedStatKeyLoader))
{

}

LoaderManager::~LoaderManager()
{
  delete _mobModels;
  delete _jobModels;
  delete _stuffs;
  delete _consumables;
  delete _ressources;
  delete _authorizedStatKeys;
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
      item = (**getConsumableLoader())->getValue(name);
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

  func = std::bind1st(std::mem_fun(&LoaderManager::setRessourceLoader), this);
  protocol.addFunc("RESSOURCES", func);

  func = std::bind1st(std::mem_fun(&LoaderManager::setAuthorizedStatKeyLoader), this);
  protocol.addFunc("AUTHORIZEDSTATKEYSLIST", func);
}
