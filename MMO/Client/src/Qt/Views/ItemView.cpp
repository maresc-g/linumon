//
// ItemView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Feb  7 12:19:06 2014 guillaume marescaux
// Last update Tue Mar 11 13:46:39 2014 guillaume marescaux
//

#include			<qtooltip.h>
#include			<boost/algorithm/string.hpp>
#include			"Qt/Views/ItemView.hh"

ItemView::ItemView(QWidget *parent, WindowManager *wMan, unsigned int nb, AItem const *item):
  QWidget(parent), _wMan(wMan), _item(item), _nb(nb), _x(0), _y(0)
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
  this->setStyleSheet(std::string("ItemView QFrame#" + name + "{ border-image: url(./Res/Items/" + name + ".png); }").c_str());
}

ItemView::ItemView(QWidget *parent, WindowManager *wMan):
  QWidget(parent), _wMan(wMan), _item(NULL), _nb(0)
{
  ui.setupUi(this);
  ui.l_nb->hide();
  this->setObjectName("default");
  this->setStyleSheet("ItemView#default { border-image: ''; }");
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

void				ItemView::mousePressEvent(QMouseEvent *mEvent)
{
  if (mEvent->button() == Qt::LeftButton)
    {
      if (this->parentWidget()->objectName() != "f_craft")
	makeDrag();
    }
}

void				ItemView::mouseDoubleClickEvent(QMouseEvent *)
{
  if (_item && this->parentWidget()->objectName() == "f_items")
    static_cast<InventoryView *>(this->parentWidget()->parentWidget())->itemAction(this);
  else if (_item && this->parentWidget()->objectName() == "stuffview")
    static_cast<StuffView *>(this->parentWidget())->itemAction(this);
  else
    std::cout << "FAIL = " << this->parentWidget()->objectName().toStdString() << std::endl;
}

void				ItemView::enterEvent(QEvent *)
{
  // QToolTip::showText(this->mapToGlobal( QPoint( 0, 0 ) ), "ITEM DESCRIPTION" );
}

void				ItemView::setInfos(AItem const *item, unsigned int nb)
{
  std::cout << "ITEM VIEW SET INFOS" << std::endl;
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
      this->setStyleSheet("ItemView#default { border-image: ''; }");
    }
}

void				ItemView::resize(int x, int y)
{
  QWidget::resize(x, y);
  ui.frame->resize(x, y);
}

void				ItemView::move(int x, int y)
{
  QWidget::move(x, y);
  _x = x;
  _y = y;
}

AItem const			&ItemView::getItem() const { return (*_item); }

void				ItemView::makeDrag()
{
  // if (_item)
  //   {
  //     std::pair<AItem const *, unsigned int>	*pair = new std::pair<AItem const *, unsigned int>(_item, _nb);
  //     std::ostringstream	oss;

  //     oss << pair;
  //     QDrag			*dr = new QDrag(this);
  //     QMimeData			*data = new QMimeData;

  //     data->setText(oss.str().c_str());
  //     dr->setMimeData(data);
  //     dr->start();
  //   }
  // The data to be transferred by the drag and drop operation is contained in a QMimeData object
  QMimeData *data = new QMimeData;
  QDrag *dr = new QDrag(this);
  data->setText("This is a test");
  // Assign ownership of the QMimeData object to the QDrag object.
  dr->setMimeData(data);
  // Start the drag and drop operation
  if (dr->start(Qt::MoveAction))
    deleteLater();
}
 
void				ItemView::dragMoveEvent(QDragMoveEvent *de)
{
  de->accept();
}
 
void				ItemView::dragEnterEvent(QDragEnterEvent *event)
{
  event->acceptProposedAction();
}
 
void				ItemView::dropEvent(QDropEvent *de)
{
  qDebug("Contents: %s", de->mimeData()->text().toLatin1().data());
  // if (_item && this->parentWidget()->objectName() != "stuffview")
  //   {
  //     std::pair<AItem const *, unsigned int>	*pair =
  // 	reinterpret_cast<std::pair<AItem const *, unsigned int> *>(std::stol(de->mimeData()->text().toLatin1().data(), 0, 16));

  //     static_cast<ItemView *>(de->source())->setInfos(_item, _nb);
  //     setInfos(pair->first, pair->second);
  //   }
}
