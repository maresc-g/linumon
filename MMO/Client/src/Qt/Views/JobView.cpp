//
// JobView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Tue Feb 25 14:55:36 2014 guillaume marescaux
// Last update Wed Feb 26 16:36:03 2014 guillaume marescaux
//

#include			"Qt/Views/JobView.hh"

JobView::JobView(QWidget *parent, WindowManager *wMan):
  QWidget(parent), _wMan(wMan), _currentCraft(NULL), _job(NULL)
{
  ui.setupUi(this);
  connect(ui.tw_crafts, SIGNAL(itemSelectionChanged()), this, SLOT(handleChange()));
  ui.tw_crafts->horizontalHeader()->setResizeMode(QHeaderView::Fixed);
  ui.tw_crafts->setColumnWidth(0, 455);
  ui.tw_crafts->setColumnWidth(1, 50);
  QTableWidgetItem *item=new QTableWidgetItem ("blaa");
  QTableWidgetItem *item2=new QTableWidgetItem ("blaa");
  QTableWidgetItem *item3=new QTableWidgetItem ("blaa");
  QTableWidgetItem *item4=new QTableWidgetItem ("blaa");
  QTableWidgetItem *item5=new QTableWidgetItem ("blaa");
  item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter); 
  item2->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter); 
  item3->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter); 
  item4->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter); 
  item5->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter); 
  ui.tw_crafts->insertRow(0);
  ui.tw_crafts->setItem(0, 0, item);
  ui.tw_crafts->setItem(0, 1, new QTableWidgetItem("30"));
  ui.tw_crafts->insertRow(1);
  ui.tw_crafts->setItem(1, 0, item2);
  ui.tw_crafts->setItem(1, 1, new QTableWidgetItem("30"));
  ui.tw_crafts->insertRow(2);
  ui.tw_crafts->setItem(2, 0, item3);
  ui.tw_crafts->setItem(2, 1, new QTableWidgetItem("30"));
  ui.tw_crafts->insertRow(3);
  ui.tw_crafts->setItem(3, 0, item4);
  ui.tw_crafts->setItem(3, 1, new QTableWidgetItem("30"));
  ui.tw_crafts->insertRow(4);
  ui.tw_crafts->setItem(4, 0, item5);
  ui.tw_crafts->setItem(4, 1, new QTableWidgetItem("30"));
}

JobView::~JobView()
{
}

void				JobView::handleChange()
{
  QList<QTableWidgetItem *>	list = ui.tw_crafts->selectedItems();
  Craft const			*craft = _job->getJobModel().getCraft(list.first()->text().toStdString());

  std::cout << list.first()->text().toStdString() << std::endl;
  if (_currentCraft)
    delete _currentCraft;
  _currentCraft = new CraftView(this, _wMan);
  _currentCraft->move(5, 460);
  _currentCraft->show();
}

void				JobView::paintEvent(QPaintEvent *)
{
  QStyleOption			opt;
  QPainter			p(this);

  opt.init(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void				JobView::setInfos(Job const &job)
{
  std::list<Craft *> const	crafts = job.getJobModel().getCrafts();
  int				i = 0;
  QTableWidgetItem		*item;

  _job = &job;
  ui.l_name->setText(job.getJobModel().getName().c_str());
  ui.l_level->setText(std::to_string(job.getLevel().getLevel()).c_str());
  ui.pb_exp->setMaximum(job.getLevel().getExp());
  ui.pb_exp->setValue(job.getCurrentExp());
  for (auto it = crafts.begin() ; it != crafts.end() ; it++)
    {
      ui.tw_crafts->insertRow(i);
      item = new QTableWidgetItem((*it)->getName().c_str());
      item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter); 
      ui.tw_crafts->setItem(i, 0, item);
      item = new QTableWidgetItem(std::to_string((*it)->getLevel().getLevel()).c_str());
      item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter); 
      ui.tw_crafts->setItem(i, 1, item);
      i++;
    }
}

void				JobView::on_b_craft_clicked()
{
}
