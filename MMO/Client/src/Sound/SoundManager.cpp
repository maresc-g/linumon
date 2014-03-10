//
// SoundManager.cpp for  in /home/jourda_c/Documents/C++/Rtype_test/rtype/rtype
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Sat Nov 23 20:11:19 2013 cyril jourdain
// Last update Sat Mar  8 02:49:36 2014 cyril jourdain
//

#include		"Sound/SoundManager.hh"

SoundManager::SoundManager() :
  _sounds(new std::map<std::string, sf::SoundBuffer *>),
  _musics(new std::map<std::string, sf::Music *>)
{
}

SoundManager::~SoundManager()
{
  for (auto it = _sounds->begin(); it != _sounds->end(); it++)
    {
      delete it->second;
      _sounds->erase(it);
    }
  for (auto it = _musics->begin(); it != _musics->end(); it++)
    {
      it->second->stop();
      delete it->second;
      _musics->erase(it);
    }
}

void			SoundManager::addSound(std::string const &name, std::string const &path)
{
  (*_sounds)[name] = new sf::SoundBuffer();
  (*_sounds)[name]->loadFromFile(path);
}

  void			SoundManager::addMusic(std::string const &name, std::string const &path,
					       bool loop, int volume)
{
  (*_musics)[name] = new sf::Music();
  (*_musics)[name]->openFromFile(path);
  (*_musics)[name]->setLoop(loop);
  (*_musics)[name]->setVolume(volume);
}

void			SoundManager::playSound(std::string const &name)
{
  sf::Sound		sound;

  if ((*_sounds)[name])
    {
      _sound.setBuffer(*(*_sounds)[name]);
      _sound.setVolume(80);
      _sound.play();
    }
}

void			SoundManager::playMusic(std::string const &name)
{
  if ((*_musics)[name])
    (*_musics)[name]->play();
}

void			SoundManager::pauseMusic(std::string const &name)
{
  if ((*_musics)[name])
    (*_musics)[name]->pause();
}

void			SoundManager::stopMusic(std::string const &name)
{
  if ((*_musics)[name])
    (*_musics)[name]->stop();
}

void			SoundManager::loadDefaultSounds()
{
  addMusic(WORLD_THEME, WORLD_THEME_RES);
  addMusic(MENU_THEME, MENU_THEME_RES);
  addSound(TO_BATTLE, TO_BATTLE_RES);
  addMusic(BATTLE_THEME, BATTLE_THEME_RES);
  // addSound(BLAST1, BLAST1_RES);
  // addMusic(LOBBY_MUSIC, LOBBY_MUSIC_RES);
  // addMusic(GAME_MUSIC, GAME_MUSIC_RES, true, 40);
}
