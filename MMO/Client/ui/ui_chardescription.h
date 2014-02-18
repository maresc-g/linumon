/********************************************************************************
** Form generated from reading UI file 'chardescription.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHARDESCRIPTION_H
#define UI_CHARDESCRIPTION_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CharDescription
{
public:
    QLabel *l_name;
    QLabel *l_level;
    QLabel *charPic;

    void setupUi(QWidget *CharDescription)
    {
        if (CharDescription->objectName().isEmpty())
            CharDescription->setObjectName(QString::fromUtf8("CharDescription"));
        CharDescription->resize(324, 412);
        CharDescription->setMaximumSize(QSize(324, 412));
        l_name = new QLabel(CharDescription);
        l_name->setObjectName(QString::fromUtf8("l_name"));
        l_name->setGeometry(QRect(20, 320, 271, 31));
        l_level = new QLabel(CharDescription);
        l_level->setObjectName(QString::fromUtf8("l_level"));
        l_level->setGeometry(QRect(20, 360, 281, 21));
        charPic = new QLabel(CharDescription);
        charPic->setObjectName(QString::fromUtf8("charPic"));
        charPic->setGeometry(QRect(50, 50, 221, 261));

        retranslateUi(CharDescription);

        QMetaObject::connectSlotsByName(CharDescription);
    } // setupUi

    void retranslateUi(QWidget *CharDescription)
    {
        CharDescription->setWindowTitle(QApplication::translate("CharDescription", "Form", 0, QApplication::UnicodeUTF8));
        l_name->setText(QApplication::translate("CharDescription", "Ilyssa", 0, QApplication::UnicodeUTF8));
        l_level->setText(QApplication::translate("CharDescription", "Level 145", 0, QApplication::UnicodeUTF8));
        charPic->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CharDescription: public Ui_CharDescription {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHARDESCRIPTION_H
