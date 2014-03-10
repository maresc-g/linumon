//
// SoundManager.hh for  in /home/jourda_c/Documents/C++/Rtype_test/rtype/rtype
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Sat Nov 23 19:55:36 2013 cyril jourdain
// Last update Sun Nov 24 17:44:51 2013 cyril jourdain
//

#ifndef 		__SOUNDMANAGER_HH__
# define 		__SOUNDMANAGER_HH__

#include		<SFML/Audio.hpp>
#include		<map>
#include		"Utility/Singleton.hpp"
#include		"Sound/Sounds.hh"

class			SoundManager : public Singleton<SoundManager>
{
  friend class Singleton<SoundManager>;

private:
  std::map<std::string, sf::SoundBuffer *>	*_sounds;
  std::map<std::string, sf::Music *>		*_musics;
  sf::Sound					_sound;

private:
  SoundManager();
  virtual ~SoundManager();

public:
  void			addSound(std::string const &name,std::string const &path);
  void			addMusic(std::string const &name,std::string const &path, bool loop = true,
				 int volume = 100);
  void			playSound(std::string const &name);
  void			playMusic(std::string const &name);
  void			pauseMusic(std::string const &name);
  void			stopMusic(std::string const &name);
  void			loadDefaultSounds();
};

#endif
