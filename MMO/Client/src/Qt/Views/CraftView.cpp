//
// CraftView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Wed Feb 26 14:24:07 2014 guillaume marescaux
// Last update Wed Feb 26 16:51:17 2014 guillaume marescaux
//

#include			"Qt/Views/CraftView.hh"

CraftView::CraftView(QWidget *parent, WindowManager *wMan):
  QWidget(parent), _wMan(wMan), _craft(NULL)
{
  ui.setupUi(this);
}

CraftView::~CraftView()
{
}

void				CraftView::paintEvent(QPaintEvent *)
{
  QStyleOption			opt;
  QPainter			p(this);

  opt.init(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void				CraftView::setInfos(Craft const &craft)
{
  _craft = &craft;
  ui.l_name->setText(craft.getName().c_str());
  std::list<AItem *>		items = craft.getIngredients();

  for (auto it = items.begin() ; it != items.end() ; it++)
    {
      item = new ItemView(ui.frame, _wMan, it->second, it->first);
      // if (ingredients != "")
      // 	ingredients += ", ";
      // ingredients += (*it)->getName();
    }
}
