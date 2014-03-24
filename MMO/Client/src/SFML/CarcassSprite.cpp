//
// CarcassSprite.cpp for 7 in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Mon Mar 24 17:04:15 2014 cyril jourdain
// Last update Mon Mar 24 18:22:41 2014 cyril jourdain
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
      std::cout << "Drawing carcass" << std::endl;
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
	  // std::cout << (**_wMan->getMainPlayer())->getJobs().getJobWithRessource(_resPtr->getName())->getJobModel().getName() << std::endl;
	  Client::getInstance()->gather(0,"",_resPtr->getId());
	}
    }
}

unsigned int	CarcassSprite::getCarcassId() const
{
  return _resPtr->getId();
}
