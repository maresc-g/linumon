//
// SoundManager.cpp for  in /home/jourda_c/Documents/C++/Rtype_test/rtype/rtype
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Sat Nov 23 20:11:19 2013 cyril jourdain
// Last update Sat Mar 22 22:46:23 2014 cyril jourdain
//

#include		<stdexcept>
#include		"Sound/SoundManager.hh"
#include		"JsonFile/JsonFile.hh"

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

void			SoundManager::playSound(std::string const &name, int volume)
{
  sf::Sound		sound;

  try {
    _sound.setBuffer(*(_sounds->at(name)));
    _sound.setVolume(volume);
    _sound.play();
  } catch (std::out_of_range const &e){
    std::cout << "SoundManager::playSound - " << name << " not found" << std::endl;
  }
}

void			SoundManager::playMusic(std::string const &name)
{
  try {
    _musics->at(name)->play();
  } catch (std::out_of_range const &e){
    std::cout << "SoundManager::playMusic - " << name << " not found" << std::endl;
  }
}

void			SoundManager::pauseMusic(std::string const &name)
{
  try {
    _musics->at(name)->pause();
  } catch (std::out_of_range const &e){
  }
}

void			SoundManager::stopMusic(std::string const &name)
{
  try {
    _musics->at(name)->stop();
  } catch (std::out_of_range const &e){
  }
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

void			SoundManager::loadSoundsFromFile(std::string const &file)
{
  JsonFile		jFile;
  std::vector<std::string>		musics;
  std::vector<std::string>		sounds;

  JsonFile::readFile(jFile, file);
  musics = jFile["Musics"].getMemberNames();
  for (auto it = musics.begin(); it != musics.end(); ++it)
    {
      std::cout << *it << std::endl;
      addMusic(*it, jFile["Musics"][*it].asString());
    }
  sounds = jFile["Sounds"].getMemberNames();
  for (auto it = sounds.begin(); it != sounds.end(); ++it)
    addSound(*it, jFile["Sounds"][*it].asString());
}
