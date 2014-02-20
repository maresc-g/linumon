//
// CreateCharView.cpp for  in /home/jourda_c/Documents/PFA/Sources
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Tue Dec 10 16:16:06 2013 cyril jourdain
// Last update Wed Feb 19 14:37:44 2014 guillaume marescaux
//

#include		"Qt/Views/CreateCharView.hh"
#include		"Entities/Faction.hh"
#include		<QMessageBox>
#include		"Client.hh"

CreateCharView::CreateCharView(QWidget *parent, WindowManager *man) :
  QWidget(parent)
{
  ui.setupUi(this);
  _charType = FACTION1;
  ui.l_faction1->setText(FACTION1);
  ui.l_faction2->setText(FACTION2);
  _wMan = man;
}

CreateCharView::~CreateCharView()
{
}

void		CreateCharView::paintEvent(QPaintEvent *)
{
  QStyleOption opt;
  QPainter p(this);

  opt.init(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void		CreateCharView::on_b_spritePerso1_clicked()
{
  ui.b_spritePerso1->setStyleSheet("background-color:#0000FF");
  ui.b_spritePerso2->setStyleSheet("background-color:#FFFFFF");
  _charType = FACTION1;
}

void		CreateCharView::on_b_spritePerso2_clicked()
{
  ui.b_spritePerso2->setStyleSheet("background-color:#0000FF");
  ui.b_spritePerso1->setStyleSheet("background-color:#FFFFFF");
  _charType = FACTION2;
}

void		CreateCharView::on_b_cancel_clicked()
{
  ui.le_name->clear();
  this->hide();
}

void		CreateCharView::on_b_validate_clicked()
{
  if (ui.le_name->text() == "")
    {
      QMessageBox::critical(this, "Error", "Please enter a name");
    }
  else
    {
      Client::getInstance()->create(ui.le_name->text().toStdString(), _charType);
      while (**(_wMan->getState()) == CLIENT::CREATE)
	usleep(1000);
      _wMan->showCharacter();
      // Maybe add state if error

      // _wMan->create();
      this->close();
    }
}
