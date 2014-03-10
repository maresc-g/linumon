//
// SpriteManager.hh for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Mon Feb  3 14:02:47 2014 cyril jourdain
// Last update Fri Mar  7 11:47:07 2014 cyril jourdain
//

#ifndef 		__SPRITEMANAGER_HH__
# define 		__SPRITEMANAGER_HH__

#include		<map>
#include		<iostream>
#include		<SFML/Graphics.hpp>

#include		"SFML/Sprite/Sprite.hh"

class			SpriteManager
{
private:
  std::map<std::string, sf::Texture*>	*_textures;
  std::map<std::string, Sprite*>	*_anims;
  bool					_textureLoaded;

public:
  SpriteManager();
  virtual ~SpriteManager();

public:
  void			loadTextures(std::string const &filePath);
  void			loadAnimations(std::string const &jsonPath);
  Sprite		*getSprite(std::string const &name) const;
  Sprite		*copySprite(std::string const &name);
  bool			copySprite(std::string const &name, Sprite &);
};

#endif
