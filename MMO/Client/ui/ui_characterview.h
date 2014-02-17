/********************************************************************************
** Form generated from reading UI file 'characterview.ui'
**
** Created: Mon Feb 17 14:21:44 2014
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHARACTERVIEW_H
#define UI_CHARACTERVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CharacterView
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *layoutScroll;
    QPushButton *b_play;
    QPushButton *b_back;
    QPushButton *b_new;

    void setupUi(QWidget *CharacterView)
    {
        if (CharacterView->objectName().isEmpty())
            CharacterView->setObjectName(QString::fromUtf8("CharacterView"));
        CharacterView->resize(1194, 877);
        gridLayoutWidget = new QWidget(CharacterView);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(110, 280, 311, 421));
        layoutScroll = new QGridLayout(gridLayoutWidget);
        layoutScroll->setObjectName(QString::fromUtf8("layoutScroll"));
        layoutScroll->setSizeConstraint(QLayout::SetDefaultConstraint);
        layoutScroll->setContentsMargins(0, 0, 0, 0);
        b_play = new QPushButton(CharacterView);
        b_play->setObjectName(QString::fromUtf8("b_play"));
        b_play->setGeometry(QRect(257, 710, 161, 51));
        b_back = new QPushButton(CharacterView);
        b_back->setObjectName(QString::fromUtf8("b_back"));
        b_back->setGeometry(QRect(30, 20, 201, 61));
        b_new = new QPushButton(CharacterView);
        b_new->setObjectName(QString::fromUtf8("b_new"));
        b_new->setGeometry(QRect(110, 710, 141, 51));

        retranslateUi(CharacterView);

        QMetaObject::connectSlotsByName(CharacterView);
    } // setupUi

    void retranslateUi(QWidget *CharacterView)
    {
        CharacterView->setWindowTitle(QApplication::translate("CharacterView", "Form", 0, QApplication::UnicodeUTF8));
        b_play->setText(QString());
        b_back->setText(QString());
        b_new->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CharacterView: public Ui_CharacterView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHARACTERVIEW_H
