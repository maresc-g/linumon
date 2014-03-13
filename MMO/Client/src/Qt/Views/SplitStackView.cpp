//
// SplitStackView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Wed Mar 12 13:59:24 2014 guillaume marescaux
// Last update Thu Mar 13 14:03:35 2014 guillaume marescaux
//

#include			<QValidator>
#include			"Qt/Views/SplitStackView.hh"

SplitStackView::SplitStackView(QWidget *parent, WindowManager *wMan):
  QWidget(parent), _wMan(wMan), _stack(NULL)
{
  ui.setupUi(this);
  ui.le_nb->setValidator(new QIntValidator);
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

void				SplitStackView::on_b_accept_clicked()
{
  unsigned int			nb = ui.le_nb->text().toUInt();

  if (nb > _stack->getNb())
    ui.le_nb->setText(std::to_string(_stack->getNb()).c_str());
  else
    {
      (**_wMan->getMainPlayer())->newStack(_stack->getId(), nb);
      Client::getInstance()->newStack(_stack->getId(), nb);
      _wMan->getSFMLView()->getInventoryView()->initInventory();
      hide();
    }
}

void				SplitStackView::on_b_cancel_clicked()
{
  hide();
}

void				SplitStackView::setInfos(Stack const *stack)
{
  _stack = stack;
}
