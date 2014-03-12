//
// SpriteManager.cpp for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Tue Feb  4 11:04:13 2014 cyril jourdain
// Last update Tue Mar 11 23:20:33 2014 cyril jourdain
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

void		SpriteManager::loadSprites(std::string const &filePath)
{
  JsonFile	file;
  std::string	name;

  JsonFile::readFile(file, filePath);
  for (unsigned int i = 0; i < file.getMemberNames().size();i++)
    {
      name = file[file.getMemberNames()[i]].asString();
      loadAnimations(name);
    }
}

void		SpriteManager::loadAnimations(std::string const &jsonPath)
{
  JsonFile	jFile;
  int		size = 0;
  sf::Vector2i	customSize;
  Json::Value	sprites;
  std::string	id;
  std::string	iName;
  std::string	numSprite;

  JsonFile::readFile(jFile, jsonPath);
  size = jFile["info"]["size"].asInt();

  for (unsigned int i = 0; i < jFile["sprites"].getMemberNames().size();i++)
    {
      id = jFile["sprites"].getMemberNames()[i]; // Name of global sprite
      // std::cout << "Adding anim : " << id << std::endl;
      (*_anims)[id] = new Sprite();
      (*_anims)[id]->setName(id);
      (*_anims)[id]->setTexture((*_textures)[jFile["info"]["texture"].asString()]);
      for (unsigned int j = 0; j < jFile["sprites"][id].getMemberNames().size(); j++)
	{
	  iName = jFile["sprites"][id].getMemberNames()[j];
	  // std::cout << "\t" << iName << std::endl;
	  (*_anims)[id]->addAnim(iName);
	  for (unsigned int k = 0; k < jFile["sprites"][id][iName].getMemberNames().size(); k++)
	    {
	      numSprite = jFile["sprites"][id][iName].getMemberNames()[k];
	      if (jFile["sprites"][id][iName][numSprite]["sx"].asInt() != 0 &&
		  jFile["sprites"][id][iName][numSprite]["sy"].asInt() != 0)
		{
		  customSize.x = jFile["sprites"][id][iName][numSprite]["sx"].asInt();
		  customSize.y = jFile["sprites"][id][iName][numSprite]["sy"].asInt();
		}
	      else
		{
		  customSize.x = size;
		  customSize.y = size;
		}
		
	      (*(*_anims)[id])[iName]->
		addSprite(sf::IntRect(jFile["sprites"][id][iName][numSprite]["x"].asInt(),
				      jFile["sprites"][id][iName][numSprite]["y"].asInt(),
				      customSize.x,
				      customSize.y),
			  sf::Vector2f(jFile["sprites"][id][iName][numSprite]["ox"].asInt(),
				       jFile["sprites"][id][iName][numSprite]["oy"].asInt()));
	      // std::cout << "\t\t" << k << std::endl;
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
  Sprite *tmp = NULL;
  try {
    tmp = _anims->at(anim);
    return new Sprite(*tmp);
  } catch (std::out_of_range const &e) {
    std::cerr << "Sprite *copySprite in SpriteManager: No animation named " << anim << std::endl;
    return NULL;
  }
}

bool		SpriteManager::copySprite(std::string const &anim, Sprite &dest)
{
  try {
    dest = (*(_anims->at(anim)));
    return true;
  } catch (std::out_of_range const &e) {
    std::cerr << "void copySprite in SpriteManager: No animation named " << anim << std::endl;
    return false;
  }
}
