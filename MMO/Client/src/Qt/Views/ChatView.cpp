//
// ChatView.cpp for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Thu Feb  6 14:49:44 2014 cyril jourdain

//

#include		<QMessageBox>
#include		"Qt/Views/ChatView.hh"

ChatView::ChatView(QWidget *parent, WindowManager *man) :
  QWidget(parent), _wMan(man), _focused(false)
{
  ui.setupUi(this);
  ui.le_chatText->installEventFilter(this);
}

ChatView::~ChatView()
{
}

void		ChatView::paintEvent(QPaintEvent *)
{
  QStyleOption			opt;
  QPainter			p(this);

  opt.init(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void		ChatView::submitText()
{
  if (ui.le_chatText->text() != ""){
    std::cout << "send : " << ui.le_chatText->text().toStdString() << std::endl;
    Client::getInstance()->sendChat(ui.le_chatText->text().toStdString());
    ui.le_chatText->clear();
  }
  else
    {
      ui.le_chatText->clearFocus();
      _focused = false;
    }
}

bool		ChatView::getFocused() const
{
  return _focused;
}

bool		ChatView::eventFilter(QObject *watched, QEvent *e)
{
  if (watched == ui.le_chatText)
    {
      if (e->type() == QEvent::KeyPress)
	{
	  QKeyEvent *k = static_cast<QKeyEvent *>(e);
	  if (k->key() == Qt::Key_Enter || k->key() == Qt::Key_Return)
	    {
	      submitText();
	      return true;
	    }
	}
      else if (e->type() == QEvent::FocusIn)
	{
	    _focused = true;
	    return true;
	}
      else if (e->type() == QEvent::FocusOut)
	{
	    _focused = true;
	    return true;
	}
    }
  return QWidget::eventFilter(watched, e);
}
