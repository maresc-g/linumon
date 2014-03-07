//
// TalentModelLoader.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Mar  7 15:55:43 2014 laurent ansel
// Last update Fri Mar  7 18:09:46 2014 laurent ansel
//

#ifndef 			__TALENTMODELLOADER_HH__
# define 			__TALENTMODELLOADER_HH__

#include			<list>
#include			"Trame/Trame.hh"
#include			"Loader/ILoader.hh"
#include			"Stats/TalentModel.hh"

class				TalentModels
{
public:
  typedef TalentModel		value;

private:
  void				setTalentModels(std::list<TalentModel *> const &talentModels);

private:
  std::list<TalentModel *>	*_talentModels;

public:
  TalentModels();
  virtual ~TalentModels();

  std::list<TalentModel *> const	&getTalentModels() const;

  void				addTalentModel(TalentModel *talentModel);

  TalentModel			*getTalentModel(std::string const &name) const;
  TalentModel			*getTalentModel(unsigned int const id) const;
};

class				TalentModelLoader : public ILoader<TalentModels>
{
private:
  TalentModels			*_talentModels;

private:
  bool				deserializationTreeModel(Trame &trame);

public:
  TalentModelLoader();
  virtual ~TalentModelLoader();
  virtual bool			serialization(Trame &trame) const;
  virtual bool			deserialization(Trame &trame);
  virtual TalentModels const	&getLoaderContent() const;
  virtual TalentModels::value	*getValue(std::string const &name) const;
  virtual TalentModels::value	*getValue(unsigned int const id) const;
};

#endif
