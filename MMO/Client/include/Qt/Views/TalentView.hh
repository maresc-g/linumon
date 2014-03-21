//
// TalentView.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Thu Mar 20 10:56:37 2014 guillaume marescaux
// Last update Thu Mar 20 16:10:23 2014 guillaume marescaux
//

#ifndef 		__TALENTVIEW_HH__
# define 		__TALENTVIEW_HH__

#include		<Qt/qwidget.h>
#include		<Qt/qpainter.h>
#include		"ui_talentview.h"
#include		"Qt/WindowManager.hh"
#include		"Stats/Talent.hh"

class			TalentView : public QWidget
{
  Q_OBJECT

public:

  TalentView(QWidget *, WindowManager *wMan, TalentModel const *talentModel, Talent const *talent);
  virtual ~TalentView();

private:

  Ui::talentview	ui;
  WindowManager		*_wMan;
  TalentModel const	*_talentModel;
  Talent const		*_talent;

private:

  virtual void		paintEvent(QPaintEvent *);
  void			setInfos(void);
  virtual void		mousePressEvent(QMouseEvent *);

public:

  TalentModel const	*getTalentModel(void) const;
  Talent const		*getTalent(void) const;
};

#endif
