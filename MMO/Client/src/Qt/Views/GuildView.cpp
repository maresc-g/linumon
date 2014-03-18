//
// GuildView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Thu Mar 13 16:29:23 2014 guillaume marescaux
// Last update Mon Mar 17 17:05:09 2014 guillaume marescaux
//

#include			"Qt/Views/GuildView.hh"

GuildView::GuildView(QWidget *parent, WindowManager *wMan):
  QWidget(parent), _wMan(wMan)
{
  ui.setupUi(this);
  ui.tw_members->horizontalHeader()->setResizeMode(QHeaderView::Fixed);
  ui.tw_members->setColumnWidth(0, 167);
  ui.tw_members->setColumnWidth(1, 167);
  ui.tw_members->setColumnWidth(2, 167);
}

GuildView::~GuildView()
{
}

void				GuildView::paintEvent(QPaintEvent *)
{
  QStyleOption			opt;
  QPainter			p(this);

  opt.init(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void				GuildView::initGuild(Guild const *guild)
{
  QTableWidgetItem		*item;

  int				count = ui.tw_members->rowCount();
  for (int i = 0 ; i < count ; i++)
    ui.tw_members->removeRow(0);
  ui.tw_members->clearContents();
  if (guild)
    {
      ui.l_name->setText(guild->getName().c_str());
      unsigned int		i = 0;
      for (auto it = guild->getContainer().begin() ; it != guild->getContainer().end() ; it++)
	{
	  ui.tw_members->insertRow(i);
	  item = new QTableWidgetItem((*it)->name.c_str());
	  item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter); 
	  ui.tw_members->setItem(i, 0, item);
	  item = new QTableWidgetItem((*it)->faction.c_str());
	  item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter); 
	  ui.tw_members->setItem(i, 1, item);
	  item = new QTableWidgetItem(std::to_string((*it)->level).c_str());
	  item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter); 
	  ui.tw_members->setItem(i, 2, item);
	  i++;
	}
      ui.tw_members->show();
      ui.l_gname->hide();
      ui.le_gname->hide();
      ui.b_create->hide();
    }
  else
    {
      ui.l_name->setText("CREATE YOUR GUILD");
      ui.tw_members->hide();
      ui.l_gname->show();
      ui.le_gname->show();
      ui.b_create->show();
    }
}
