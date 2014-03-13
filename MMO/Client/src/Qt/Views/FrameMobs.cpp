//
// FrameMobs.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Wed Mar 12 14:45:37 2014 guillaume marescaux
// Last update Thu Mar 13 14:24:38 2014 guillaume marescaux
//

#include			"Qt/Views/FrameMobs.hh"

FrameMobs::FrameMobs(QWidget *parent, WindowManager *wMan):
  QFrame(parent), _wMan(wMan)
{
  setAcceptDrops(true);
}

FrameMobs::~FrameMobs() {}

void				FrameMobs::paintEvent(QPaintEvent *)
{
  QStyleOption			opt;
  QPainter			p(this);

  opt.init(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

ParentInfos			*FrameMobs::getNameFirstParent(QWidget *parent)
{
  static std::string		parentNames[] =
    {
      "scrollPerso",
      "f_battleMobs"
    };
  static unsigned int		size = sizeof(parentNames) / sizeof(std::string);
  unsigned int			i;

  while ((parent = parent->parentWidget()))
    {
      i = 0;
      while (i < size)
	{
	  if (parentNames[i] == parent->objectName().toStdString())
	    {
	      ParentInfos	*infos = new ParentInfos;

	      infos->name = parentNames[i];
	      infos->parent = parent;
	      return (infos);
	    }
	  i++;
	}
    }
  return (NULL);
}

void				FrameMobs::dragMoveEvent(QDragMoveEvent *de)
{
  de->accept();
}
 
void				FrameMobs::dragEnterEvent(QDragEnterEvent *event)
{
  event->acceptProposedAction();
}

void				FrameMobs::dropEvent(QDropEvent *de)
{
  ParentInfos			*sourceInfos = getNameFirstParent(de->source());

  std::cout << "SOURCE NAME = " << sourceInfos->name << " AND OBJECT NAME = " << objectName().toStdString() << std::endl;
  if (sourceInfos->name == "f_battleMobs" && objectName() != "f_battleMobs")
    {
      Mob const			*_mob = reinterpret_cast<Mob const *>(std::stol(de->mimeData()->text().toLatin1().data(), 0, 16));
      if ((**_wMan->getMainPlayer())->battleMobtoMob(_mob->getId()))
	Client::getInstance()->battleMobtoMob(_mob->getId());
    }
  else if (sourceInfos->name == "scrollPerso" && objectName() != "scrollPerso")
    {
      Mob const			*_mob = reinterpret_cast<Mob const *>(std::stol(de->mimeData()->text().toLatin1().data(), 0, 16));
      if ((**_wMan->getMainPlayer())->mobtoBattleMob(_mob->getId()))
	Client::getInstance()->mobtoBattleMob(_mob->getId());
    }
  _wMan->getSFMLView()->getDigitaliserView()->initDigit((**_wMan->getMainPlayer())->getDigitaliser());
  // if (infos && infos->name != "stuffview" && sourceInfos->name != "stuffview")
  //   {
  //     std::pair<AItem const *, unsigned int>	*pair =
  // 	reinterpret_cast<std::pair<AItem const *, unsigned int> *>(std::stol(de->mimeData()->text().toLatin1().data(), 0, 16));
  //     static_cast<FrameMobs *>(de->source())->setInfos(_item, _nb);
  //     setInfos(pair->first, pair->second);
  //   }
}
