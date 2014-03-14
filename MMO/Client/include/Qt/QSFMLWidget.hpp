//
// QSFMLWidget.hpp for  in /home/jourda_c/Documents/Projets/PFA/Graphics
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Thu Sep 26 13:41:58 2013 cyril jourdain
// Last update Fri Mar 14 11:34:32 2014 cyril jourdain
//

#ifndef 		__QSFMLWIDGET_HPP__
# define 		__QSFMLWIDGET_HPP__

#include		<SFML/Graphics.hpp>
#include		<Qt/qwidget.h>
#include		<Qt/qtimer.h>
#include		<QResizeEvent>

#define			WIN_W	1920
#define			WIN_H	1000

class			QSFMLWidget : public QWidget, public sf::RenderWindow
{
private:
  QTimer                *_timer;
protected:
  sf::View		*_mainView;
  bool                  _initialized;

public:
  QSFMLWidget(QWidget *, const QPoint &, const QSize &, unsigned int frameTime = 60);
  virtual       ~QSFMLWidget();
  
private:
  virtual void          onInit() = 0;
  virtual void          onUpdate() = 0;
  virtual void		onResize(QResizeEvent *) = 0;
  virtual QPaintEngine  *paintEngine() const;
  virtual void          showEvent(QShowEvent *);
  virtual void          paintEvent(QPaintEvent *);
  virtual void		mousePressEvent(QMouseEvent *) {};
  virtual void		keyPressEvent(QKeyEvent *){};
  bool			eventFilter(QObject *w, QEvent *e);

public:
  sf::View		*getMainView() const;
};

#endif
