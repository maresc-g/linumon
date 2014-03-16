//
// SplitStackView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Wed Mar 12 13:59:24 2014 guillaume marescaux
// Last update Sun Mar 16 16:05:36 2014 guillaume marescaux
//

#include			<QValidator>
#include			"Qt/Views/SplitStackView.hh"

SplitStackView::SplitStackView(QWidget *parent, WindowManager *wMan):
  QWidget(parent), _wMan(wMan), _source(NULL), _dest(NULL)
{
  ui.setupUi(this);
}

SplitStackView::~SplitStackView()
{
}

void				SplitStackView::paintEvent(QPaintEvent *)
{
  QStyleOption			opt;
  QPainter			p(this);

  opt.init(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

ParentInfos			*SplitStackView::getNameFirstParent(QWidget *parent)
{
  static std::string		parentNames[] =
    {
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

void				SplitStackView::on_b_accept_clicked()
{
  unsigned int			nb = ui.sb_nb->value();
  ParentInfos			*destInfos = getNameFirstParent(_dest);
  ParentInfos			*sourceInfos = getNameFirstParent(_source);
  Stack<AItem>			*stack = NULL;
  unsigned int			idStack = 0;

  if (!(destInfos->name == "tradeview" && sourceInfos->name == "tradeview"))
    {
      if (sourceInfos->name != "tradeview")
	{
	  idStack = (**_wMan->getMainPlayer())->newStack(_source->getStack().getId(), nb);
	  Client::getInstance()->newStack(_source->getStack().getId(), nb);
	  stack = (**_wMan->getMainPlayer())->getInventory().getStack(idStack);
	}
      if (destInfos->name == "tradeview" && sourceInfos->name == "inventoryview")
	{
	  (**_wMan->getTrade())->putPlayerStack(new Stack<AItem>(*stack));
	  (**_wMan->getMainPlayer())->deleteItem(stack);
	  (**_wMan->getTrade())->setChanged(true);
	  Client::getInstance()->putItem((**_wMan->getTrade())->getId(), idStack);
	  // _wMan->getSFMLView()->getTradeView()->putStackToTrade(&_source->getStack());
	}
      else if (destInfos->name == "inventoryview" && sourceInfos->name == "tradeview")
	{
	  (**_wMan->getMainPlayer())->addItem(new Stack<AItem>(_source->getStack()));
	  (**_wMan->getTrade())->setChanged(true);
	  Client::getInstance()->getItem((**_wMan->getTrade())->getId(), _source->getStack().getId());
	  // _wMan->getSFMLView()->getTradeView()->getStackFromTrade(&_source->getStack());
	}
      _wMan->getSFMLView()->getInventoryView()->initInventory();
    }
  hide();
}

void				SplitStackView::on_b_cancel_clicked()
{
  hide();
}

void				SplitStackView::setInfos(StackView *source, StackView *dest)
{
  _source = source;
  _dest = dest;
  ui.sb_nb->setMaximum(source->getStack().getNb());
  ui.sb_nb->setValue(source->getStack().getNb());
}

