//
// KeyDelayer.cpp for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Mon Feb 17 13:29:14 2014 cyril jourdain
// Last update Fri Mar 14 11:41:53 2014 cyril jourdain
//

#include		<stdexcept>
#include		"SFML/KeyDelayer.hh"
#include <iostream>

KeyDelayer::KeyDelayer() :
  _values(new std::map<Qt::Key, float>())
{
}

KeyDelayer::~KeyDelayer()
{
}

void			KeyDelayer::addWatcher(Qt::Key const key, float delay)
{
  (*_values)[key] = delay;
}

void			KeyDelayer::update(sf::Clock const *clock)
{
  float time = clock->getElapsedTime().asMicroseconds();

  for (auto it = _values->begin(); it != _values->end(); ++it)
    {
      if (it->second > 0)
	it->second -= time;
      else
	it->second = 0;
    }
}

bool			KeyDelayer::isAvailable(Qt::Key const key) const
{
  try
    {
      if (_values->at(key) == 0)
	return (true);
      return (false);
    }
  catch (std::out_of_range const &e)
    {
      return (true);
    }
}
