//
// MobView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Feb 28 15:44:59 2014 guillaume marescaux
// Last update Mon Mar 10 16:22:23 2014 guillaume marescaux
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
  std::string name = mob->getName();
  auto it = name.find(' ');
  while (it != std::string::npos)
    {
      name.replace(it, 1, "_");
      it = name.find(' ');
    }
  boost::algorithm::to_lower(name);
  ui.frame->setObjectName(name.c_str());
  std::cout << "NAME = " << name << std::endl;
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
  std::string name = mob->getName();
  auto it = name.find(' ');
  while (it != std::string::npos)
    {
      name.replace(it, 1, "_");
      it = name.find(' ');
    }
  boost::algorithm::to_lower(name);
  ui.frame->setObjectName(name.c_str());
  std::cout << "NAME = " << name << std::endl;
  this->setStyleSheet(std::string("MobView QFrame#" + name + "{ border-image: url(./Res/Mobs/" + name + ".png); }").c_str());
  setContextMenuPolicy(Qt::CustomContextMenu);
  connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(displayMenu(const QPoint&)));
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
  std::pair<AItem const *, unsigned int>	*pair =
    reinterpret_cast<std::pair<AItem const *, unsigned int> *>(std::stol(de->mimeData()->text().toLatin1().data(), 0, 16));

  if (pair->first->getItemType() == AItem::CONSUMABLE)
    {
      Consumable const		*consumable = static_cast<Consumable const *>(pair->first);
      bool			ret;

      std::cout << "I WILL USE THE OBJECT " << consumable->getName() << " ON " << _mob->getName() << std::endl;
      (**_wMan->getMainPlayer())->useObject(_mob->getId(), consumable->getId());
      Client::getInstance()->useObject(_mob->getId(), consumable->getId());
      _wMan->getSFMLView()->getInventoryView()->initInventory();
    }
}
