//
// MobView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Feb 28 15:44:59 2014 guillaume marescaux
// Last update Wed Mar 19 15:30:00 2014 cyril jourdain
//

#include			<QMenu>
#include			<boost/algorithm/string.hpp>
#include			"Qt/Views/MobView.hh"
#include			"Entities/Consumable.hh"

MobView::MobView(QWidget *parent, WindowManager *wMan, Mob const *mob):
  QWidget(parent), _wMan(wMan), _mob(mob)
{
  ui.setupUi(this);
  ui.l_nb->hide();
  std::string name = mob->getModel().getName();
  auto it = name.find(' ');
  while (it != std::string::npos)
    {
      name.replace(it, 1, "_");
      it = name.find(' ');
    }
  boost::algorithm::to_lower(name);
  ui.frame->setObjectName(name.c_str());
  this->setStyleSheet(std::string("MobView QFrame#" + name + "{ border-image: url(./Res/Mobs/" + name + ".png); }").c_str());
  setContextMenuPolicy(Qt::CustomContextMenu);
  connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(displayMenu(const QPoint&)));
}

MobView::MobView(QWidget *parent, WindowManager *wMan):
  QWidget(parent), _wMan(wMan), _mob(NULL)
{
  ui.setupUi(this);
  ui.l_nb->hide();
  this->setObjectName("default");
  // this->setStyleSheet("MobView#default { border-image: url(./Res/Mobs/bottes_bouftou.png); }");
}

MobView::~MobView()
{
}

void				MobView::setInfos(Mob const *mob)
{
  _mob = mob;
  ui.l_nb->hide();
  if (mob)
    {
      std::string name = mob->getModel().getName();
      auto it = name.find(' ');
      while (it != std::string::npos)
	{
	  name.replace(it, 1, "_");
	  it = name.find(' ');
	}
      boost::algorithm::to_lower(name);
      ui.frame->setObjectName(name.c_str());
      this->setStyleSheet(std::string("MobView QFrame#" + name + "{ border-image: url(./Res/Mobs/" + name + ".png); }").c_str());
      setContextMenuPolicy(Qt::CustomContextMenu);
      connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(displayMenu(const QPoint&)));
    }
  else
    this->setObjectName("default");
}

void				MobView::displayMenu(const QPoint &pos)
{
  QPoint			globalPos = this->mapToGlobal(pos);
  QMenu				myMenu;

  myMenu.addAction("Show stats");

  QAction			*selectedItem = myMenu.exec(globalPos);

  if (selectedItem)
    {
      _wMan->getSFMLView()->getStuffView()->initStuff(*_mob);
    }
}

void				MobView::paintEvent(QPaintEvent *)
{
  QStyleOption			opt;
  QPainter			p(this);

  opt.init(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void				MobView::mousePressEvent(QMouseEvent *mEvent)
{
  if (mEvent->button() == Qt::LeftButton)
    {
      if (_mob)
	emit clicked(_mob->getId());
      makeDrag();
    }
}

void				MobView::makeDrag()
{
  if (_mob)
    {
      std::ostringstream	oss;

      oss << _mob;
      QDrag			*dr = new QDrag(this);
      QMimeData			*data = new QMimeData;

      data->setText(oss.str().c_str());
      dr->setMimeData(data);
      dr->start();
    }
}

ParentInfos			*MobView::getNameFirstParent(QWidget *parent)
{
  static std::string		parentNames[] =
    {
      "inventoryview",
      "digitaliserview",
      "tradeview"
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

void				MobView::resize(int x, int y)
{
  QWidget::resize(x, y);
  ui.frame->resize(x, y);
}


void				MobView::move(int x, int y)
{
  QWidget::move(x, y);
  _x = x;
  _y = y;
}

void				MobView::dragMoveEvent(QDragMoveEvent *de)
{
  de->accept();
}
 
void				MobView::dragEnterEvent(QDragEnterEvent *event)
{
  event->acceptProposedAction();
}

void				MobView::dropEvent(QDropEvent *de)
{
  ParentInfos			*infos = getNameFirstParent(this);
  ParentInfos			*sourceInfos = getNameFirstParent(de->source());

  if (sourceInfos && sourceInfos->name == "inventoryview")
    {
      std::pair<AItem const *, unsigned int>	*pair =
	reinterpret_cast<std::pair<AItem const *, unsigned int> *>(std::stol(de->mimeData()->text().toLatin1().data(), 0, 16));

      if (pair->first->getItemType() == AItem::CONSUMABLE)
	{
	  Consumable const		*consumable = static_cast<Consumable const *>(pair->first);

	  (**_wMan->getMainPlayer())->useObject(_mob->getId(), consumable->getId());
	  Client::getInstance()->useObject(_mob->getId(), consumable->getId());
	  _wMan->getSFMLView()->getInventoryView()->initInventory();
	}
    }
  else if (sourceInfos->name == "digitaliserview" && infos->name == "tradeview")
    {      
      Mob const			*mob = reinterpret_cast<Mob const *>(std::stol(de->mimeData()->text().toLatin1().data(), 0, 16));
      static_cast<MobView *>(de->source())->setInfos(_mob);
      (**_wMan->getMainPlayer())->getAndDeleteMob(mob->getId());
      Client::getInstance()->putMob((**_wMan->getTrade())->getId(), mob->getId());
      setInfos(mob);
      _wMan->getSFMLView()->getDigitaliserView()->initDigit((**_wMan->getMainPlayer())->getDigitaliser());
    }
  else if (sourceInfos->name == "tradeview" && infos->name == "digitaliserview")
    {      
    }
  else if (sourceInfos && sourceInfos->name == "digitaliserview")
    {
      Mob const			*mob = reinterpret_cast<Mob const *>(std::stol(de->mimeData()->text().toLatin1().data(), 0, 16));
      static_cast<MobView *>(de->source())->setInfos(_mob);
      Client::getInstance()->switchMobs(_mob->getId(), mob->getId());
      setInfos(mob);
    }
  // else if (infos && sourceInfos && (infos->name == "tradeview" || sourceInfos->name == "tradeview"))
  //   _wMan->getSFMLView()->getTradeView()->handleMobChange(de->source(), this);
}
