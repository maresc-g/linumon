//
// ItemView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Feb  7 12:19:06 2014 guillaume marescaux
// Last update Mon Feb 24 16:18:49 2014 guillaume marescaux
//

#include			<qtooltip.h>
#include			<boost/algorithm/string.hpp>
#include			"Qt/Views/ItemView.hh"

ItemView::ItemView(QWidget *parent, WindowManager *wMan, unsigned int nb, AItem *item):
  QWidget(parent), _wMan(wMan), _item(item), _nb(nb)
{
  ui.setupUi(this);
  if (!item)
    {
      this->setObjectName("default");
      this->setStyleSheet("ItemView#default { border-image: url(./Res/Items/plastron_bouftou.png); }");
    }
  else
    {
      ui.l_nb->setText(std::to_string(nb).c_str());
      ui.l_nb->move(ITEM_SIZE - 20, ITEM_SIZE - 20);
      std::string name = item->getName();
      auto it = name.find(' ');
      while (it != std::string::npos)
	{
	  name.replace(it, 1, "_");
	  it = name.find(' ');
	}
      boost::algorithm::to_lower(name);
      this->setObjectName(name.c_str());
      this->setStyleSheet(std::string("ItemView#" + name + "{ border-image: url(./Res/Items/" + name + ".png); }").c_str());
    }
}

ItemView::ItemView(QWidget *parent, WindowManager *wMan, AItem *item):
  QWidget(parent), _wMan(wMan), _item(item), _nb(0)
{
  ui.setupUi(this);
  ui.l_nb->hide();
  if (!item)
    {
      this->setObjectName("default");
      this->setStyleSheet("ItemView#default { border-image: url(./Res/Items/bottes_bouftou.png); }");
    }
  else
    {
      std::string name = item->getName();
      auto it = name.find(' ');
      while (it != std::string::npos)
	{
	  name.replace(it, 1, "_");
	  it = name.find(' ');
	}
      boost::algorithm::to_lower(name);
      std::cout << "ITEM NAME = " << name << std::endl;
      this->setObjectName(name.c_str());
      this->setStyleSheet(std::string("ItemView#" + name + "{ border-image: url(./Res/Items/" + name + ".png); }").c_str());
    }
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

void				ItemView::enterEvent(QEvent *event)
{
  QToolTip::showText(this->mapToGlobal( QPoint( 0, 0 ) ), "ITEM DESCRIPTION" );
}
