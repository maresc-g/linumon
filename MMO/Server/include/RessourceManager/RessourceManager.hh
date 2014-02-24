//
// RessourceManager.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Mon Feb 17 14:25:54 2014 laurent ansel
// Last update Mon Feb 24 16:18:51 2014 laurent ansel
//

#ifndef 			__RESSOURCEMANAGER_HH__
# define 			__RESSOURCEMANAGER_HH__

# include			<list>
# include			"Thread/Thread.hpp"
# include			"Utility/Singleton.hpp"
# include			"Mutex/Mutex.hpp"
# include			"JsonFile/JsonFile.hh"
# include			"Entities/Ressource.hh"
# include			"Database/Loaders/RessourceLoader.hh"

#define	PATH_RESSOURCES_FILE	"Res/ressources.json"
#define	DEFAULT_TIME		10000000
#define	DEFAULT_ACTION		100

struct				RessourcePop
{
public:
  std::string			name;
  double			time;
  std::string			zone;
  Ressource			*ressource;

public:
  RessourcePop();
  virtual ~RessourcePop();
  void				clear();
};

class				RessourceManager : public Thread, public Singleton<RessourceManager>
{
  friend class			Singleton<RessourceManager>;

private:
  std::map<std::string, std::list<Ressource *> *>	*_ressources;
  std::list<std::pair<bool, RessourcePop *> >	*_action;
  Mutex				*_mutex;
  bool				_quit;

private:
  RessourceManager();
  virtual ~RessourceManager();
  void				init();
  double			setRessource(std::list<std::pair<bool, RessourcePop *> >::iterator &it);
  void				newTime(double const microsecond);


public:
  void				run();
  void				setQuit(bool const quit);
  void				needRessource(std::string const &name, Ressource::RessourceCoordinate const &coord, std::string const &zone);

};

void				*runRessourceManager(void *data);

#endif
