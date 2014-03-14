//
// SplitStackView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Wed Mar 12 13:59:24 2014 guillaume marescaux
<<<<<<< HEAD
// Last update Fri Mar 14 15:55:05 2014 guillaume marescaux
=======
// Last update Fri Mar 14 13:00:37 2014 laurent ansel
>>>>>>> 13796ed8b9ed7e84e0c0e9042b0250140186fbe3
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

  if (!(destInfos->name == "tradeview" && sourceInfos->name == "tradeview"))
    {
      (**_wMan->getMainPlayer())->newStack(_source->getStack().getId(), nb);
      Client::getInstance()->newStack(_source->getStack().getId(), nb);
      _wMan->getSFMLView()->getInventoryView()->initInventory();
      if (destInfos->name == "tradeview" && sourceInfos->name == "inventoryview")
	{
	  (**_wMan->getTrade())->putPlayerStack(&_source->getStack());
	  // _wMan->getSFMLView()->getTradeView()->putStackToTrade(&_source->getStack());
	}
      else if (destInfos->name == "inventoryview" && destInfos->name == "tradeview")
	{
	  (**_wMan->getTrade())->getPlayerStack(&_source->getStack());
	  // _wMan->getSFMLView()->getTradeView()->getStackFromTrade(&_source->getStack());
	}
    }
  hide();
}

void				SplitStackView::on_b_cancel_clicked()
{
  hide();
}

<<<<<<< HEAD
void				SplitStackView::setInfos(StackView *source, StackView *dest)
=======
void				SplitStackView::setInfos(Stack<AItem> const *stack)
>>>>>>> 13796ed8b9ed7e84e0c0e9042b0250140186fbe3
{
  _source = source;
  _dest = dest;
  ui.sb_nb->setMaximum(source->getStack().getNb());
  ui.sb_nb->setValue(source->getStack().getNb());
}
