//
// ChatView.cpp for  in /home/jourda_c/GIT/linumon/MMO
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Mon Feb 17 12:55:28 2014 cyril jourdain
// Last update Sat Mar 22 22:57:00 2014 cyril jourdain
//

#include		<QMessageBox>
#include		<QPalette>
#include		<QPixmap>
#include		"Qt/Views/ChatView.hh"

ChatView::ChatView(QWidget *parent, WindowManager *man) :
  QWidget(parent), _wMan(man), _focused(false)
{
  ui.setupUi(this);
  ui.le_chatText->clearFocus();
  ui.le_chatText->installEventFilter(this);
  ui.tb_chat->installEventFilter(this);
}

ChatView::~ChatView()
{
}

void		ChatView::setLineFocus()
{
  std::cout << "FOCUS" << std::endl;
  setFocused(true);
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
  parentWidget()->setFocus(Qt::OtherFocusReason);
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

void		ChatView::update()
{
  if ((**(Client::getInstance()->getChat()))->getNewMessage())
    {
      ui.tb_chat->clear();
      std::list<std::string> text = (**(Client::getInstance()->getChat()))->getMsgs();
      for (auto it = text.begin(); it != text.end(); ++it)
	  ui.tb_chat->append(QString((*it).c_str()));
      (**(Client::getInstance()->getChat()))->setNewMessage(false);
    }
}

bool		ChatView::eventFilter(QObject *w, QEvent *e)
{
  if (w == ui.le_chatText || w == ui.tb_chat)
    {
      if (e->type() == QEvent::FocusIn || e->type() == QEvent::MouseButtonPress)
	setFocused(true);
    }
  return QWidget::eventFilter(w, e);
}
