//
// StuffStatsView.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Tue Mar 18 10:53:24 2014 guillaume marescaux
// Last update Tue Mar 18 15:34:37 2014 guillaume marescaux
//

#ifndef 		__STUFFSTATSVIEW_HH__
# define 		__STUFFSTATSVIEW_HH__

#include		<Qt/qwidget.h>
#include		<Qt/qpainter.h>
#include		"ui_stuffstatsview.h"
#include		"Qt/WindowManager.hh"
#include		<QLabel>

class			WindowManager;

class			StuffStatsView : public QWidget
{
  Q_OBJECT

public:
  StuffStatsView(QWidget *, WindowManager *wman);
  virtual ~StuffStatsView();

private:
  Ui::stuffstatsview	ui;
  WindowManager		*_wMan;
  std::list<QLabel *>	*_labels;

private:
  virtual void		paintEvent(QPaintEvent *);

public:
  void			setInfos(AItem const *item);
};

#endif
