//
// LoaderManager.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Wed Mar  5 15:08:00 2014 laurent ansel
// Last update Wed Mar 19 14:59:21 2014 alexis mestag
//

#ifndef 			__LOADERMANAGER_HH__
# define 			__LOADERMANAGER_HH__

#include			"Utility/Singleton.hpp"
#include			"Loader/MobModelLoader.hh"
#include			"Loader/JobModelLoader.hh"
#include			"Loader/StuffLoader.hh"
#include			"Loader/ConsumableLoader.hh"
#include			"Loader/SpellLoader.hh"
#include			"Loader/TalentModelLoader.hh"
#include			"Loader/HealLoader.hh"
#include			"Loader/AuthorizedStatKeysLoader.hh"
#include			"Loader/RessourceLoader.hh"
#include			"Loader/TalentTreeLoader.hh"
#include			"Protocol/Protocol.hpp"
#include			"Mutex/Mutex.hpp"

class				LoaderManager : public Singleton<LoaderManager>
{
  friend class			Singleton<LoaderManager>;
private:
  MutexVar<SpellLoader *>	*_spells;
  MutexVar<StuffLoader *>	*_stuffs;
  MutexVar<ConsumableLoader *>	*_consumables;
  MutexVar<RessourceLoader *>	*_ressources;
  MutexVar<AuthorizedStatKeyLoader *>	*_authorizedStatKeys;
  MutexVar<HealLoader *>		*_heals;
  MutexVar<TalentModelLoader *>	*_talentModels;
  MutexVar<JobModelLoader *>	*_jobModels;
  MutexVar<MobModelLoader *>	*_mobModels;
  MutexVar<TalentTreeLoader *>	*_talentTrees;

private:
  LoaderManager();
  virtual ~LoaderManager();

public:
  MutexVar<MobModelLoader *>	*getMobModelLoader() const;
  MutexVar<JobModelLoader *>	*getJobModelLoader() const;
  MutexVar<StuffLoader *>	*getStuffLoader() const;
  MutexVar<ConsumableLoader *>	*getConsumableLoader() const;
  MutexVar<SpellLoader *>	*getSpellLoader() const;
  MutexVar<TalentModelLoader *>	*getTalentModelLoader() const;
  MutexVar<HealLoader *>		*getHealLoader() const;
  MutexVar<RessourceLoader *>	*getRessourceLoader() const;
  MutexVar<AuthorizedStatKeyLoader *>	*getAuthorizedStatKeyLoader() const;
  MutexVar<TalentTreeLoader *>	*getTalentTreeLoader() const;

  AItem				*getItemLoader(std::string const &name) const;

  bool				setMobModelLoader(Trame *trame);
  bool				setJobModelLoader(Trame *trame);
  bool				setStuffLoader(Trame *trame);
  bool				setConsumableLoader(Trame *trame);
  bool				setSpellLoader(Trame *trame);
  bool				setTalentModelLoader(Trame *trame);
  bool				setHealLoader(Trame *trame);
  bool				setRessourceLoader(Trame *trame);
  bool				setAuthorizedStatKeyLoader(Trame *trame);
  bool				setTalentTreeLoader(Trame *trame);

  void				initReception(Protocol &protocol) const;
  void				init();
};

#endif
