//
// CarcassSprite.cpp for 7 in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Mon Mar 24 17:04:15 2014 cyril jourdain
// Last update Tue Mar 25 15:14:05 2014 cyril jourdain
//

#include			<QMenu>		
#include			"SFML/CarcassSprite.hh"

CarcassSprite::CarcassSprite(Carcass *c, WindowManager *wman) :
  _resPtr(c), _wMan(wman)
{
}

CarcassSprite::~CarcassSprite()
{
}

void		CarcassSprite::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  if (_resPtr){
    if (_texture && _vertex) {
      states.texture = _texture;
      states.transform *= getTransform();
      target.draw(_vertex, 4, sf::Quads, states);
    }
  }
}

void		CarcassSprite::onClick(QMouseEvent *event)
{
  QMenu menu;

  menu.addAction("Loot");
  QAction *action = menu.exec(QPoint(event->globalX(), event->globalY()));
  if (action)
    {
      if (action->text() == "Loot")
	{
	  // std::cout << (**_wMan->getMainPlayer())->getJobs().getJobWithRessource(_resPtr->getName()) << std::endl;
	  Client::getInstance()->gather(_resPtr->getId(),"Trappeur",_resPtr->getId());
	  Map::getInstance()->delCarcass((**_wMan->getMainPlayer())->getZone(), _resPtr);
	}
    }
}

unsigned int	CarcassSprite::getCarcassId() const
{
  return _resPtr->getId();
}
