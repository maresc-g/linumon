//
// ChatView.cpp for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Mon Feb 17 12:55:28 2014 cyril jourdain
// Last update Tue Feb 18 15:18:56 2014 cyril jourdain
//

#include		<QMessageBox>
#include		"Qt/Views/ChatView.hh"

ChatView::ChatView(QWidget *parent, WindowManager *man) :
  QWidget(parent), _wMan(man), _focused(false)
{
  ui.setupUi(this);
  ui.le_chatText->clearFocus();
  // ui.le_chatText->installEventFilter(this);
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
  }
  ui.le_chatText->clear();
  ui.le_chatText->clearFocus();
  _focused = false;
}

bool		ChatView::getFocused() const
{
  return _focused;
}

void		ChatView::setFocused(bool f)
{
  _focused = f;
  if (_focused)
    ui.le_chatText->setFocus(Qt::OtherFocusReason);
  else
    ui.le_chatText->clearFocus();
}

bool		ChatView::eventFilter(QObject *watched, QEvent *e)
{
  std::cout << "wadafak" << std::endl;
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
      // else if (e->type() == QEvent::FocusIn)
      // 	{
      // 	    _focused = true;
      // 	    return true;
      // 	}
      // else if (e->type() == QEvent::FocusOut)
      // 	{
      // 	  std::cout << "test" << std::endl;
      // 	  _focused = false;
      // 	  return true;
      // 	}
    }
  return QWidget::eventFilter(watched, e);
}
