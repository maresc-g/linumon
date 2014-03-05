//
// ModModelLoader.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Wed Mar  5 12:04:25 2014 laurent ansel
// Last update Wed Mar  5 14:29:04 2014 laurent ansel
//

#ifndef 			__MOBMODELLOADER_HH__
# define 			__MOBMODELLOADER_HH__

#include			<list>
#include			"Trame/Trame.hh"
#include			"Loader/ILoader.hh"
#include			"Entities/MobModel.hh"

class				MobModels
{
public:
  typedef MobModel		value;

private:
  void				setMobModels(std::list<MobModel *> const &mobModels);

private:
  std::list<MobModel *>		*_mobModels;

public:
  MobModels();
  virtual ~MobModels();

  std::list<MobModel *> const	&getMobModels() const;

  void				addMobModel(MobModel *mob);

  MobModel			*getMobModel(std::string const &name) const;
  MobModel			*getMobModel(unsigned int const id) const;
};

class				MobModelLoader : public ILoader<MobModels>
{
private:
  MobModels			*_mobModels;
public:
  MobModelLoader();
  virtual ~MobModelLoader();
  virtual bool			serialization(Trame &trame) const;
  virtual bool			deserialization(Trame &trame);
  virtual MobModels const	&getLoaderContent() const;
  virtual MobModels::value	*getValue(std::string const &name) const;
  virtual MobModels::value	*getValue(unsigned int const id) const;
};

#endif
