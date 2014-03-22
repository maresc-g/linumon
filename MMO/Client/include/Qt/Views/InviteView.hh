//
// InviteView.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Fri Mar 21 19:30:29 2014 guillaume marescaux
// Last update Fri Mar 21 19:43:21 2014 guillaume marescaux
//

#ifndef 		__INVITEVIEW_HH__
# define 		__INVITEVIEW_HH__

#include		<Qt/qwidget.h>
#include		<Qt/qpainter.h>
#include		"ui_inviteview.h"
#include		"Qt/WindowManager.hh"

class			InviteView : public QWidget
{
  Q_OBJECT

public:

  InviteView(QWidget *, WindowManager *wMan);
  virtual ~InviteView();

private:

  Ui::inviteview	ui;
  WindowManager		*_wMan;
  std::string		_name;

private:

  virtual void		paintEvent(QPaintEvent *);

private slots:

  void			on_b_join_clicked();
  void			on_b_decline_clicked();

public:

  void			setInfos(std::string const &name);
};

#endif
