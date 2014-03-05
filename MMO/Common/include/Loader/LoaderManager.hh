//
// LoaderManager.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Wed Mar  5 15:08:00 2014 laurent ansel
// Last update Wed Mar  5 15:36:14 2014 laurent ansel
//

#ifndef 			__LOADERMANAGER_HH__
# define 			__LOADERMANAGER_HH__

#include			"Utility/Singleton.hpp"
#include			"Loader/MobModelLoader.hh"
#include			"Protocol/Protocol.hpp"

class				LoaderManager : public Singleton<LoaderManager>
{
  friend class			Singleton<LoaderManager>;
private:
  MobModelLoader		*_mobModels;

private:
  LoaderManager();
  virtual ~LoaderManager();

  bool				setMobModelLoader(Trame *trame);

public:
  MobModelLoader		*getMobModelLoader() const;
  void				initReception(Protocol &protocol) const;
};

#endif
