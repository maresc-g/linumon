//
// GuildView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Thu Mar 13 16:29:23 2014 guillaume marescaux
// Last update Fri Mar 14 11:56:28 2014 guillaume marescaux
//

#include			"Qt/Views/GuildView.hh"

GuildView::GuildView(QWidget *parent, WindowManager *wMan):
  QWidget(parent), _wMan(wMan)
{
  ui.setupUi(this);
  ui.tw_members->horizontalHeader()->setResizeMode(QHeaderView::Fixed);
  ui.tw_members->setColumnWidth(0, 510);
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

  int				count = ui.tw_crafts->rowCount();
  for (int i = 0 ; i < count ; i++)
    ui.tw_crafts->removeRow(0);
  ui.tw_crafts->clearContents();
  if (guild)
    {
      ui.l_name->setText(guild->getName().c_str());
      unsigned int		i = 0;
      for (auto it = guild->getContainer().begin() ; it != guild->getContainer().end() ; it++)
	{
	  ui.tw_members->insertRow(i);
	  item = new QTableWidgetItem((*it)->name.c_str());
	  item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter); 
	  i++;
	}
    }
  else
    {
      ui.l_name->setText("CREATE YOUR GUILD");
    }
}
