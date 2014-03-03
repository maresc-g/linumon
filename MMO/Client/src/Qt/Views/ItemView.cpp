//
// ItemView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Feb  7 12:19:06 2014 guillaume marescaux
// Last update Fri Feb 28 15:52:58 2014 guillaume marescaux
//

#include			<qtooltip.h>
#include			<boost/algorithm/string.hpp>
#include			"Qt/Views/ItemView.hh"

ItemView::ItemView(QWidget *parent, WindowManager *wMan, unsigned int nb, AItem *item):
  QWidget(parent), _wMan(wMan), _item(item), _nb(nb)
{
  ui.setupUi(this);
  if (nb > 0)
    {
      ui.l_nb->setText(std::to_string(nb).c_str());
      ui.l_nb->move(ITEM_SIZE - 20, ITEM_SIZE - 20);
      ui.l_nb->show();
    }
  else
    ui.l_nb->hide();
  std::string name = item->getName();
  auto it = name.find(' ');
  while (it != std::string::npos)
    {
      name.replace(it, 1, "_");
      it = name.find(' ');
    }
  boost::algorithm::to_lower(name);
  ui.frame->setObjectName(name.c_str());
  std::cout << "NAME = " << name << std::endl;
  this->setStyleSheet(std::string("ItemView QFrame#" + name + "{ border-image: url(./Res/Items/" + name + ".png); }").c_str());
}

ItemView::ItemView(QWidget *parent, WindowManager *wMan):
  QWidget(parent), _wMan(wMan), _item(NULL), _nb(0)
{
  ui.setupUi(this);
  ui.l_nb->hide();
  this->setObjectName("default");
  // this->setStyleSheet("ItemView#default { border-image: url(./Res/Items/bottes_bouftou.png); }");
}

ItemView::~ItemView()
{
}

void				ItemView::paintEvent(QPaintEvent *)
{
  QStyleOption			opt;
  QPainter			p(this);

  opt.init(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void				ItemView::mouseDoubleClickEvent(QMouseEvent *)
{
  if (_item && this->parentWidget()->objectName() == "f_items")
    static_cast<InventoryView *>(this->parentWidget())->itemAction(this);
  else
    std::cout << "FAIL = " << this->parentWidget()->objectName().toStdString() << std::endl;
}

void				ItemView::enterEvent(QEvent *)
{
  QToolTip::showText(this->mapToGlobal( QPoint( 0, 0 ) ), "ITEM DESCRIPTION" );
}

void				ItemView::setInfos(AItem *item, unsigned int nb)
{
  _item = item;
  _nb = nb;
  if (nb > 0)
    {
      ui.l_nb->setText(std::to_string(nb).c_str());
      ui.l_nb->move(ITEM_SIZE - 20, ITEM_SIZE - 20);
      ui.l_nb->show();
    }
  else
    ui.l_nb->hide();
  if (item)
    {
      std::string name = item->getName();
      auto it = name.find(' ');
      while (it != std::string::npos)
	{
	  name.replace(it, 1, "_");
	  it = name.find(' ');
	}
      boost::algorithm::to_lower(name);
      ui.frame->setObjectName(name.c_str());
      this->setStyleSheet(std::string("ItemView QFrame#" + name + "{ border-image: url(./Res/Items/" + name + ".png); }").c_str());
    }
  else
    {
      this->setObjectName("default");
      // this->setStyleSheet("ItemView#default { border-image: url(./Res/Items/bottes_bouftou.png); }");
    }
}

void				ItemView::resize(int x, int y)
{
  QWidget::resize(x, y);
  ui.frame->resize(x, y);
}

AItem const			&ItemView::getItem() const { return (*_item); }

// void				ItemView::makeDrag()
// {
//   Trame				trame;

//   if (_item)
//     {
//       _item->serialization(trame(trame["ITEM"]));
//       trame["NB"] = _nb;
//       std::cout << trame.toString() << std::endl;
//       QDrag *dr = new QDrag(this);
//       // The data to be transferred by the drag and drop operation is contained in a QMimeData object
//       QMimeData *data = new QMimeData;
//       data->setText(trame.toString().c_str());
//       // Assign ownership of the QMimeData object to the QDrag object.
//       dr->setMimeData(data);
//       // Start the drag and drop operation
//       dr->start();
//     }
// }
 
// void				ItemView::dragMoveEvent(QDragMoveEvent *de)
// {
//   de->accept();
// }
 
// void				ItemView::dragEnterEvent(QDragEnterEvent *event)
// {
//   event->acceptProposedAction();
// }
 
// void				ItemView::dropEvent(QDropEvent *de)
// {
//   static_cast<ItemView *>(de->source())->setInfos(_item, _nb);
//   Trame				trame(de->mimeData()->text().toLatin1().data(), true);
//   setInfos(AItem::deserialization(trame(trame["ITEM"]), false), trame["NB"].asUInt());
//   std::cout << "TEST = " << trame.toString() << std::endl;
// }
 
