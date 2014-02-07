//
// SpellBarView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Thu Feb  6 15:42:00 2014 guillaume marescaux
// Last update Fri Feb  7 12:20:17 2014 guillaume marescaux
//

#include			"Qt/Views/SpellBarView.hh"

SpellBarView::SpellBarView(QWidget *parent, WindowManager *wMan):
  QWidget(parent), _wMan(wMan)
{
  ui.setupUi(this);
}

SpellBarView::~SpellBarView()
{
}

void				SpellBarView::paintEvent(QPaintEvent *)
{
  QStyleOption			opt;
  QPainter			p(this);

  opt.init(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void				SpellBarView::on_b_spell1_clicked()
{
  std::cout << "CLICKED 1" << std::endl;
}

void				SpellBarView::on_b_spell2_clicked()
{
  std::cout << "CLICKED 2" << std::endl;
}

void				SpellBarView::on_b_spell3_clicked()
{
  std::cout << "CLICKED 3" << std::endl;
}

void				SpellBarView::on_b_spell4_clicked()
{
  std::cout << "CLICKED 4" << std::endl;
}

void				SpellBarView::on_b_spell5_clicked()
{
  std::cout << "CLICKED 5" << std::endl;
}

void				SpellBarView::on_b_spell6_clicked()
{
  std::cout << "CLICKED 6" << std::endl;
}

void				SpellBarView::on_b_spell7_clicked()
{
  std::cout << "CLICKED 7" << std::endl;
}

void				SpellBarView::on_b_spell8_clicked()
{
  std::cout << "CLICKED 8" << std::endl;
}

void				SpellBarView::on_b_spell9_clicked()
{
  std::cout << "CLICKED 9" << std::endl;
}

void				SpellBarView::on_b_spell10_clicked()
{
  std::cout << "CLICKED 10" << std::endl;
}
