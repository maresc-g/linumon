//
// RessourceLoader.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Mar  6 13:15:25 2014 laurent ansel
// Last update Thu Mar  6 15:07:04 2014 laurent ansel
//

#ifndef 			__RESSOURCELOADER_HH__
# define 			__RESSOURCELOADER_HH__

#include			<list>
#include			"Trame/Trame.hh"
#include			"Loader/ILoader.hh"
#include			"Entities/Ressource.hh"

class				Ressources
{
public:
  typedef Ressource		value;

private:
  void				setRessources(std::list<Ressource *> const &ressources);

private:
  std::list<Ressource *>	*_ressources;

public:
  Ressources();
  virtual ~Ressources();

  std::list<Ressource *> const	&getRessources() const;

  void				addRessource(Ressource *ressource);

  Ressource			*getRessource(std::string const &name) const;
  Ressource			*getRessource(unsigned int const id) const;
};

class				RessourceLoader : public ILoader<Ressources>
{
private:
  Ressources			*_ressources;

public:
  RessourceLoader();
  virtual ~RessourceLoader();
  virtual bool			serialization(Trame &trame) const;
  virtual bool			deserialization(Trame &trame);
  virtual Ressources const	&getLoaderContent() const;
  virtual Ressources::value	*getValue(std::string const &name) const;
  virtual Ressources::value	*getValue(unsigned int const id) const;
};

#endif
