//
// Ressources.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Tue Feb 18 14:39:11 2014 laurent ansel
// Last update Tue Feb 18 14:55:18 2014 laurent ansel
//

#ifndef 			__RESSOURCES_HH__
# define 			__RESSOURCES_HH__

# include			"Entities/Ressource.hh"

class				Ressources
{
private:
  std::list<Ressource *>	_ressources;

private:
  Ressources(Ressources const &rhs);
  Ressources			&operator=(Ressources const &rhs);

  std::list<Ressource *> const	&getRessources() const;
  void				setRessources(std::list<Ressource *> const &ressources);

public:
  Ressources();
  virtual ~Ressources();

  Ressource			*getRessource(std::string const &name) const;
};

#endif
