//
// LoaderManager.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Wed Mar  5 15:08:00 2014 laurent ansel
// Last update Wed Mar  5 23:29:08 2014 laurent ansel
//

#ifndef 			__LOADERMANAGER_HH__
# define 			__LOADERMANAGER_HH__

#include			"Utility/Singleton.hpp"
#include			"Loader/MobModelLoader.hh"
#include			"Loader/JobModelLoader.hh"
#include			"Protocol/Protocol.hpp"
#include			"Mutex/Mutex.hpp"

class				LoaderManager : public Singleton<LoaderManager>
{
  friend class			Singleton<LoaderManager>;
private:
  MutexVar<MobModelLoader *>	*_mobModels;
  MutexVar<JobModelLoader *>	*_jobModels;

private:
  LoaderManager();
  virtual ~LoaderManager();

public:
  MutexVar<MobModelLoader *>	*getMobModelLoader() const;
  MutexVar<JobModelLoader *>	*getJobModelLoader() const;

  bool				setMobModelLoader(Trame *trame);
  bool				setJobModelLoader(Trame *trame);

  void				initReception(Protocol &protocol) const;
};

#endif
