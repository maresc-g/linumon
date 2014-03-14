//
// KeyDelayer.hh for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Mon Feb 17 13:06:18 2014 cyril jourdain
// Last update Fri Mar 14 11:43:18 2014 cyril jourdain
//

#ifndef 		__KEYDELAYER_HH__
# define 		__KEYDELAYER_HH__

#include		<map>
#include		<SFML/Window.hpp>
#include		<QKeyEvent>

class			KeyDelayer
{
public:
  std::map<Qt::Key, float>	*_values;

public:
  KeyDelayer();
  virtual ~KeyDelayer();

public:
  void			addWatcher(Qt::Key const, float delay);
  void			update(sf::Clock const *);
  bool			isAvailable(Qt::Key const) const;
};

#endif
