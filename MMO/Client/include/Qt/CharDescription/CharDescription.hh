//
// CharDescription.hh for  in /home/jourda_c/Documents/PFA/Sources
// 
// Made by cyril jourdain
// Login   <jourda_c@epitech.net>
// 
// Started on  Tue Dec  3 15:44:54 2013 cyril jourdain
// Last update Tue Feb  4 14:47:39 2014 guillaume marescaux
//

#ifndef 		__CHARDESCRIPTION_HH__
# define 		__CHARDESCRIPTION_HH__

#include		<Qt/qwidget.h>
#include		<Qt/qpainter.h>
#include		"ui_chardescription.h"
#include		"Entities/Views/PlayerView.hh"

class			CharDescription : public QWidget
{
  Q_OBJECT

public:
  CharDescription(QWidget *, PlayerView const &player);
  ~CharDescription();

public:
  Ui::CharDescription	ui;

private:
  virtual void		paintEvent(QPaintEvent *);

};

#endif
