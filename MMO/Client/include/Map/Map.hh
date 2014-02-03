//
// Map.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Mon Feb  3 11:11:28 2014 guillaume marescaux
// Last update Mon Feb  3 12:43:11 2014 guillaume marescaux
//

#ifndef 		__MAP_HH__
# define 		__MAP_HH__

#include		"Utility/Singleton.hpp"
#include		"Mutex/Mutex.hpp"
#include		"Zone/Zone.hh"

class			Map : public Singleton<Map>
{
  friend class		Singleton<Map>;

private:

  // Ctor / Dtor
  Map();
  virtual ~Map();
  Map(Map const &);
  Map			&operator=(Map const &);

  // Attributes
  Mutex			*_mutex;
  Zone			*_zone;

public:

  // Methods
  void			lock();
  void			unlock();
  Zone const		&getZone(void) const;
  void			setZone(Zone *zone);
};

#endif
