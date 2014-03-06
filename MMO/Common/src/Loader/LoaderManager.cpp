//
// LoaderManager.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Wed Mar  5 15:04:36 2014 laurent ansel
// Last update Wed Mar  5 15:37:40 2014 laurent ansel
//

#include			<functional>
#include			"Trame/Trame.hh"
#include			"Loader/LoaderManager.hh"

LoaderManager::LoaderManager():
  _mobModels(new MobModelLoader)
{

}

LoaderManager::~LoaderManager()
{
  delete _mobModels;
}

MobModelLoader			*LoaderManager::getMobModelLoader() const
{
  return (this->_mobModels);
}

bool				LoaderManager::setMobModelLoader(Trame *trame)
{
  return (_mobModels->deserialization(*trame));
}

void				LoaderManager::initReception(Protocol &protocol) const
{
  std::function<bool (Trame *)> func;

  func = std::bind1st(std::mem_fun(&LoaderManager::setMobModelLoader), this);
  protocol.addFunc("MOBMODELS", func);
}
