//
// CreateCharView.hh for  in /home/jourda_c/Documents/PFA/Sources
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Tue Dec 10 16:14:25 2013 cyril jourdain
// Last update Tue Jan 28 10:40:51 2014 cyril jourdain
//

#ifndef 		__CREATECHARVIEW_HH__
# define 		__CREATECHARVIEW_HH__

#include		<QWidget>
#include		<Qt/qpainter.h>
#include		"ui_createchar.h"

enum CharType {
  MALE,
  FEMALE
};

class			CreateCharView : public QWidget
{
  Q_OBJECT

public:
  CreateCharView(QWidget *);
  virtual ~CreateCharView();

private:
  Ui::CreateCharView	ui;
  CharType		_charType;

private:
  virtual void		paintEvent(QPaintEvent *);

public slots:
  void			on_b_spritePerso1_clicked();
  void			on_b_spritePerso2_clicked();
  void			on_b_validate_clicked();

};

#endif
