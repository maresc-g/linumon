//
// StackView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Feb  7 12:19:06 2014 guillaume marescaux
// Last update Thu Mar 13 14:04:50 2014 guillaume marescaux
//

#include			<qtooltip.h>
#include			<boost/algorithm/string.hpp>
#include			"Qt/Views/StackView.hh"

StackView::StackView(QWidget *parent, WindowManager *wMan, Stack const *stack):
  QWidget(parent), _wMan(wMan), _stack(stack), _x(0), _y(0)
{
  ui.setupUi(this);
  if (stack->getNb() > 0)
    {
      ui.l_nb->setText(std::to_string(stack->getNb()).c_str());
      ui.l_nb->move(ITEM_SIZE - 20, ITEM_SIZE - 20);
      ui.l_nb->show();
    }
  else
    ui.l_nb->hide();
  std::string name = stack->getItem()->getName();
  auto it = name.find(' ');
  while (it != std::string::npos)
    {
      name.replace(it, 1, "_");
      it = name.find(' ');
    }
  boost::algorithm::to_lower(name);
  ui.frame->setObjectName(name.c_str());
  this->setStyleSheet(std::string("StackView QFrame#" + name + "{ border-image: url(./Res/Items/" + name + ".png); }").c_str());
}

StackView::StackView(QWidget *parent, WindowManager *wMan):
  QWidget(parent), _wMan(wMan), _stack(NULL)
{
  ui.setupUi(this);
  ui.l_nb->hide();
  this->setObjectName("default");
  this->setStyleSheet("StackView#default { border-image: ''; }");
}

StackView::~StackView()
{
}

void				StackView::paintEvent(QPaintEvent *)
{
  QStyleOption			opt;
  QPainter			p(this);

  opt.init(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void				StackView::mousePressEvent(QMouseEvent *mEvent)
{
  if (mEvent->button() == Qt::LeftButton)
    {
      if (this->parentWidget()->objectName() != "f_craft")
	makeDrag();
    }
}

void				StackView::mouseDoubleClickEvent(QMouseEvent *)
{
  ParentInfos			*infos = getNameFirstParent(this);

  if (_stack && infos->name == "inventoryview")
    static_cast<InventoryView *>(infos->parent)->stackAction(this);
  else if (_stack && infos->name == "stuffview")
    static_cast<StuffView *>(infos->parent)->stackAction(this);
  else
    std::cout << "FAIL = " << this->parentWidget()->objectName().toStdString() << std::endl;
}

void				StackView::enterEvent(QEvent *)
{
  // QToolTip::showText(this->mapToGlobal( QPoint( 0, 0 ) ), "STACK DESCRIPTION" );
}

void				StackView::setInfos(Stack const *stack)
{
  _stack = stack;
  if (stack)
    {
      std::string name = stack->getItem()->getName();
      auto it = name.find(' ');
      while (it != std::string::npos)
	{
	  name.replace(it, 1, "_");
	  it = name.find(' ');
	}
      boost::algorithm::to_lower(name);
      ui.frame->setObjectName(name.c_str());
      this->setStyleSheet(std::string("StackView QFrame#" + name + "{ border-image: url(./Res/Items/" + name + ".png); }").c_str());
    }
  else
    {
      ui.l_nb->hide();
      this->setObjectName("default");
      this->setStyleSheet("StackView#default { border-image: ''; }");
    }
}

void				StackView::resize(int x, int y)
{
  QWidget::resize(x, y);
  ui.frame->resize(x, y);
}

void				StackView::move(int x, int y)
{
  QWidget::move(x, y);
  _x = x;
  _y = y;
}

Stack const			&StackView::getStack() const { return (*_stack); }

void				StackView::makeDrag()
{
  if (_stack)
    {
      std::ostringstream	oss;

      oss << _stack;
      QDrag			*dr = new QDrag(this);
      QMimeData			*data = new QMimeData;

      data->setText(oss.str().c_str());
      dr->setMimeData(data);
      dr->start();
    }
}
 
void				StackView::dragMoveEvent(QDragMoveEvent *de)
{
  de->accept();
}
 
void				StackView::dragEnterEvent(QDragEnterEvent *event)
{
  event->acceptProposedAction();
}

ParentInfos			*StackView::getNameFirstParent(QWidget *parent)
{
  static std::string		parentNames[] =
    {
      "stuffview",
      "tradeview",
      "inventoryview"
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
 
void				StackView::dropEvent(QDropEvent *de)
{
  ParentInfos			*infos = getNameFirstParent(this);
  ParentInfos			*sourceInfos = getNameFirstParent(de->source());
  Stack const			*stack = reinterpret_cast<Stack const *>(std::stol(de->mimeData()->text().toLatin1().data(), 0, 16));

  std::cout << "NAME OF THE PARENT I SEEK = '" << infos->name << "'" << std::endl;
  if (infos && sourceInfos && (infos->name == "tradeview" || sourceInfos->name == "tradeview"))
    ;
   // _wMan->getSFMLView()->getTradeView()->handleStackChange(de->source(), this);
  else if (infos->name == "inventoryview" && sourceInfos->name == "inventoryview" && (!_stack || _stack->getNb() == 0))
    {
      _wMan->getSFMLView()->getSplitStackView()->setInfos(stack);
      _wMan->getSFMLView()->getSplitStackView()->show();
    }
  else if (infos->name == "inventoryview" && sourceInfos->name == "inventoryview" &&
	   _stack->getItem()->getName() == stack->getItem()->getName())
    {
      (**_wMan->getMainPlayer())->mergeStack(stack->getId(), _stack->getId());
      Client::getInstance()->merge(stack->getId(), _stack->getId());
    }
  else if (infos && infos->name != "stuffview" && sourceInfos->name != "stuffview")
    setInfos(stack);
}
