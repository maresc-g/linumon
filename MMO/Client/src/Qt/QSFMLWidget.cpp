//
// QSFMLWidget.cpp for  in /home/jourda_c/Documents/Projets/PFA/Graphics
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Thu Sep 26 13:44:43 2013 cyril jourdain
// Last update Wed Mar 26 14:29:24 2014 cyril jourdain
//

#include		"Qt/QSFMLWidget.hpp"
#include                <Qt/qx11info_x11.h>
#include                <X11/Xlib.h>

#include <iostream>

QSFMLWidget::QSFMLWidget(QWidget *parent, QPoint const &position, QSize const &size,
			 unsigned int frameTime) :
  QWidget(parent), sf::RenderWindow(), _timer(new QTimer), _mainView(new sf::View(sf::FloatRect(0,0, WIN_W, WIN_H))), _initialized(false)
{
  setAttribute(Qt::WA_PaintOnScreen);
  setAttribute(Qt::WA_OpaquePaintEvent);
  setAttribute(Qt::WA_NoSystemBackground);
 
  setFocusPolicy(Qt::StrongFocus);

  parent->installEventFilter(this);

  move(position);
  resize(size);
  _timer->setInterval(frameTime);
}

QSFMLWidget::~QSFMLWidget()
{
}

void			QSFMLWidget::showEvent(QShowEvent *)
{
  if (!_initialized)
    {
#ifdef Q_WS_X11
      XFlush(QX11Info::display());
#endif
      Window::create(winId());
      onInit();
      connect(_timer, SIGNAL(timeout()), this, SLOT(repaint()));
      _timer->start();
      _initialized = true;
      _mainView->setViewport(sf::FloatRect(0,0,1,1));
      setView(*_mainView);
    }
}

QPaintEngine*		QSFMLWidget::paintEngine() const
{
  return 0;
}

void			QSFMLWidget::paintEvent(QPaintEvent*)
{
  onUpdate();
  display();
}

bool			QSFMLWidget::eventFilter(QObject *, QEvent *event)
{
  if (event->type() == QEvent::Resize)
    {
      QResizeEvent *e = static_cast<QResizeEvent*>(event);
      onResize(e);
      //_mainView->setSize(e->size().width(), e->size().height());
      //std::cout << e->size().width() << " " << e->size().height() << std::endl;
      // setView(*_mainView);
    }
  return false;
}

sf::View		*QSFMLWidget::getMainView() const {return _mainView;}
