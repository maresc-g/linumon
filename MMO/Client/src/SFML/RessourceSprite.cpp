//
// RessourceSprite.cpp for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Wed Feb 26 14:58:57 2014 cyril jourdain
// Last update Fri Mar 14 15:30:14 2014 cyril jourdain
//

#include		"SFML/RessourceSprite.hh"
#include		"Map/Map.hh"

RessourceSprite::RessourceSprite(Ressource *ptr) :
  Sprite(), _resPtr(ptr)
{
}

RessourceSprite::~RessourceSprite()
{
}


void		RessourceSprite::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  Map::getInstance()->lock();
  if (_resPtr && _resPtr->isVisible()){
    if (_texture && _vertex) {
      states.texture = _texture;
      states.transform *= getTransform();
      target.draw(_vertex, 4, sf::Quads, states);
    }
  }
  Map::getInstance()->unlock();
}

void		RessourceSprite::onClick(QMouseEvent *)
{
  std::cout << "Ressource Clicked" << std::endl;
}

bool		RessourceSprite::isVisible()
{
  Map::getInstance()->lock();
  if (_resPtr && _resPtr->isVisible()){
    Map::getInstance()->unlock();
    return true;
  }
  Map::getInstance()->unlock();
  return false;
}
