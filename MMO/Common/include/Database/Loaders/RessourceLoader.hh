//
// Ressources.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Tue Feb 18 14:39:11 2014 laurent ansel
// Last update Mon Feb 24 15:35:42 2014 alexis mestag
//

#ifndef 			__RESSOURCELOADER_HH__
# define 			__RESSOURCELOADER_HH__

# include			"Utility/Singleton.hpp"
# include			"Entities/Ressource-odb.hxx"

class				RessourceLoader : public Singleton<RessourceLoader>
{
  friend class			Singleton<RessourceLoader>;

public:
  typedef std::list<Ressource *>	container_type;

private:
  container_type		_ressources;

private:
  RessourceLoader();
  RessourceLoader(RessourceLoader const &rhs);
  RessourceLoader		&operator=(RessourceLoader const &rhs);

  void				setRessources(container_type const &ressources);

public:
  virtual ~RessourceLoader();

  Ressource const		*operator[](std::string const &name) const;

  Ressource const		*getRessource(std::string const &name) const;
  container_type const		&getRessources() const;
};

#endif
