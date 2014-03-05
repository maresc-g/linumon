//
// SpriteManager.cpp for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Tue Feb  4 11:04:13 2014 cyril jourdain
// Last update Wed Mar  5 12:40:00 2014 cyril jourdain
//

#include		<stdexcept>
#include		"SFML/Sprite/SpriteManager.hh"
#include		"JsonFile/JsonFile.hh"

SpriteManager::SpriteManager() :
  _textures(new std::map<std::string, sf::Texture *>),
  _anims(new std::map<std::string, Sprite*>),
  _textureLoaded(false)
{
}

SpriteManager::~SpriteManager()
{
}

void		SpriteManager::loadTextures(std::string const &path)
{
  JsonFile	file;
  std::string	name;

  JsonFile::readFile(file, path);
  for (unsigned int i = 0; i < file.getMemberNames().size();i++)
    {
      name = file.getMemberNames()[i];
      _textures->insert(std::pair<std::string, sf::Texture *>(name, new sf::Texture()));
      (*_textures)[name]->loadFromFile(file[name].asString());
    }
  _textureLoaded = true;
}

void		SpriteManager::loadAnimations(std::string const &jsonPath)
{
  JsonFile	jFile;
  int		size = 0;
  Json::Value	sprites;
  std::string	id;
  std::string	iName;
  std::string	numSprite;

  JsonFile::readFile(jFile, jsonPath);
  size = jFile["info"]["size"].asInt();

  for (unsigned int i = 0; i < jFile["sprites"].getMemberNames().size();i++)
    {
      id = jFile["sprites"].getMemberNames()[i]; // Name of global sprite
      std::cout << "Adding anim : " << id << std::endl;
      (*_anims)[id] = new Sprite();
      (*_anims)[id]->setTexture((*_textures)[jFile["info"]["texture"].asString()]);
      for (unsigned int j = 0; j < jFile["sprites"][id].getMemberNames().size(); j++)
	{
	  iName = jFile["sprites"][id].getMemberNames()[j];
	  std::cout << "\t" << iName << std::endl;
	  (*_anims)[id]->addAnim(iName);
	  for (unsigned int k = 0; k < jFile["sprites"][id][iName].getMemberNames().size(); k++)
	    {
	      numSprite = jFile["sprites"][id][iName].getMemberNames()[k];
	      (*(*_anims)[id])[iName]->
		addSprite(sf::IntRect(jFile["sprites"][id][iName][numSprite]["x"].asInt(),
				      jFile["sprites"][id][iName][numSprite]["y"].asInt(),
				      size,
				      size));
	      std::cout << "\t\t" << k << std::endl;
	    }
	}
    }
}

Sprite		*SpriteManager::getSprite(std::string const &anim) const
{
  try {
    return _anims->at(anim);
  } catch (std::out_of_range const &e) {
    std::cerr << "Sprite *getSprite in SpriteManager: No animation named " << anim << std::endl;
    return NULL;
  }
}

Sprite		*SpriteManager::copySprite(std::string const &anim)
{
  try {
    return new Sprite(*(_anims->at(anim)));
  } catch (std::out_of_range const &e) {
    std::cerr << "Sprite *copySprite in SpriteManager: No animation named " << anim << std::endl;
    return NULL;
  }
}

void		SpriteManager::copySprite(std::string const &anim, Sprite &dest)
{
  try {
    dest = (*(_anims->at(anim)));
  } catch (std::out_of_range const &e) {
    std::cerr << "void copySprite in SpriteManager: No animation named " << anim << std::endl;
  }
}
