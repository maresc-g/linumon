//
// CreateCharView.hh for  in /home/jourda_c/Documents/PFA/Sources
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Tue Dec 10 16:14:25 2013 cyril jourdain
// Last update Wed Feb 19 14:36:37 2014 guillaume marescaux
//

#ifndef 		__CREATECHARVIEW_HH__
# define 		__CREATECHARVIEW_HH__

#include		<QWidget>
#include		<Qt/qpainter.h>
#include		"ui_createchar.h"

class WindowManager;

class			CreateCharView : public QWidget
{
  Q_OBJECT

public:
  CreateCharView(QWidget *, WindowManager *);
  virtual ~CreateCharView();

private:
  Ui::CreateCharView	ui;
  std::string		_charType;
  WindowManager		*_wMan;

private:
  virtual void		paintEvent(QPaintEvent *);

public slots:
  void			on_b_spritePerso1_clicked();
  void			on_b_spritePerso2_clicked();
  void			on_b_cancel_clicked();
  void			on_b_validate_clicked();
};

#endif
