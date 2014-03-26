//
// JobView.cpp for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Tue Feb 25 14:55:36 2014 guillaume marescaux
// Last update Wed Mar 26 14:04:19 2014 guillaume marescaux
//

#include			<QMessageBox>
#include			"Qt/Views/JobView.hh"

JobView::JobView(QWidget *parent, WindowManager *wMan):
  QWidget(parent), _wMan(wMan), _currentCraft(new CraftView(this, _wMan)), _job(NULL)
{
  ui.setupUi(this);
  connect(ui.tw_crafts, SIGNAL(itemSelectionChanged()), this, SLOT(handleChange()));
  ui.tw_crafts->horizontalHeader()->setResizeMode(QHeaderView::Fixed);
  ui.tw_crafts->setColumnWidth(0, 455);
  ui.tw_crafts->setColumnWidth(1, 50);
  _currentCraft->hide();
}

JobView::~JobView()
{
}

void				JobView::handleChange()
{
  QList<QTableWidgetItem *>	list = ui.tw_crafts->selectedItems();

  if (!list.isEmpty())
    {
      Craft const			*craft = _job->getJobModel().getCraft(list.first()->text().toStdString());
      auto				items = craft->getIngredients();
      auto				inventory = (**(_wMan->getMainPlayer()))->getInventory().getInventory();
      bool				ret = true;

      std::cout << list.first()->text().toStdString() << std::endl;
      _currentCraft->setInfos(*craft);
      _currentCraft->move(5, 460);
      _currentCraft->show();
      for (auto it = items.begin() ; it != items.end() ; it++)
	{
	  auto itb = inventory.begin();
	  auto end = inventory.end();
	  while (itb != end && **itb != (*it)->getItem()->getName())
	    itb++;
	  if (itb == end || (*it)->getNb() > (*itb)->getNb())
	    {
	      ret = false;
	      break;
	    }
	}
      if (ret && _currentCraft->getCraft().getLevel() <= _job->getLevel())
	ui.b_craft->setEnabled(true);
      else
	ui.b_craft->setEnabled(false);
    }
  else if (_currentCraft)
    _currentCraft->hide();
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
  ui.l_level->setText(std::to_string(job.getLevel()).c_str());
  ui.l_exp->setText(std::string("EXP : " + std::to_string(job.getCurrentExp()) + "/" + std::to_string(job.getExp())).c_str());
  ui.pb_exp->setMaximum(job.getExp());
  ui.pb_exp->setValue(job.getCurrentExp());
  int				count = ui.tw_crafts->rowCount();
  for (int i = 0 ; i < count ; i++)
    ui.tw_crafts->removeRow(0);
  ui.tw_crafts->clearContents();
  for (auto it = crafts.begin() ; it != crafts.end() ; it++)
    {
      ui.tw_crafts->insertRow(i);
      item = new QTableWidgetItem((*it)->getName().c_str());
      item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter); 
      ui.tw_crafts->setItem(i, 0, item);
      item = new QTableWidgetItem(std::to_string((*it)->getLevel()).c_str());
      item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter); 
      ui.tw_crafts->setItem(i, 1, item);
      i++;
    }
}

void				JobView::on_b_craft_clicked()
{
  Client::getInstance()->craft(_job->getJobModel().getName(), _currentCraft->getCraft().getName());
}

void				JobView::on_b_quit_clicked()
{
  _wMan->getSFMLView()->hideView(this);
}
