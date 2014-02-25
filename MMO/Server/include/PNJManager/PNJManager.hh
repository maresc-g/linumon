//
// PNJManager.hh for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Tue Feb 25 14:00:20 2014 laurent ansel
// Last update Tue Feb 25 14:16:08 2014 laurent ansel
//

#ifndef 			__PNJMANAGER_HH__
# define 			__PNJMANAGER_HH__

# include			"Utility/Singleton.hpp"
# include			"Mutex/Mutex.hpp"
# include			"JsonFile/JsonFile.hh"
# include			"Entities/Heal.hh"


#define	PATH_PNJS_FILE		"Res/PNJ.json"

class				PNJManager : public Singleton<PNJManager>
{
  friend class			Singleton<PNJManager>;
private:
  std::map<std::string, std::list<PNJ *> *>	*_pnjs;
  Mutex				*_mutex;

private:
  PNJManager();
  virtual ~PNJManager();
  void				init();
};

#endif
