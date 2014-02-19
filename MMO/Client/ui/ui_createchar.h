/********************************************************************************
** Form generated from reading UI file 'createchar.ui'
**
** Created: Wed Feb 19 14:00:46 2014
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATECHAR_H
#define UI_CREATECHAR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CreateCharView
{
public:
    QGroupBox *charBox;
    QLabel *label;
    QPushButton *b_validate;
    QLineEdit *le_name;
    QPushButton *b_spritePerso1;
    QPushButton *b_spritePerso2;
    QLabel *l_faction1;
    QLabel *l_faction2;

    void setupUi(QWidget *CreateCharView)
    {
        if (CreateCharView->objectName().isEmpty())
            CreateCharView->setObjectName(QString::fromUtf8("CreateCharView"));
        CreateCharView->resize(469, 324);
        CreateCharView->setMinimumSize(QSize(469, 324));
        CreateCharView->setMaximumSize(QSize(469, 324));
        charBox = new QGroupBox(CreateCharView);
        charBox->setObjectName(QString::fromUtf8("charBox"));
        charBox->setGeometry(QRect(0, 0, 471, 321));
        label = new QLabel(charBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 190, 66, 31));
        b_validate = new QPushButton(charBox);
        b_validate->setObjectName(QString::fromUtf8("b_validate"));
        b_validate->setGeometry(QRect(300, 254, 98, 27));
        le_name = new QLineEdit(charBox);
        le_name->setObjectName(QString::fromUtf8("le_name"));
        le_name->setGeometry(QRect(90, 194, 311, 27));
        b_spritePerso1 = new QPushButton(charBox);
        b_spritePerso1->setObjectName(QString::fromUtf8("b_spritePerso1"));
        b_spritePerso1->setGeometry(QRect(67, 30, 131, 101));
        b_spritePerso2 = new QPushButton(charBox);
        b_spritePerso2->setObjectName(QString::fromUtf8("b_spritePerso2"));
        b_spritePerso2->setGeometry(QRect(270, 30, 131, 101));
        l_faction1 = new QLabel(charBox);
        l_faction1->setObjectName(QString::fromUtf8("l_faction1"));
        l_faction1->setGeometry(QRect(100, 140, 91, 21));
        l_faction2 = new QLabel(charBox);
        l_faction2->setObjectName(QString::fromUtf8("l_faction2"));
        l_faction2->setGeometry(QRect(300, 140, 91, 21));

        retranslateUi(CreateCharView);

        QMetaObject::connectSlotsByName(CreateCharView);
    } // setupUi

    void retranslateUi(QWidget *CreateCharView)
    {
        CreateCharView->setWindowTitle(QApplication::translate("CreateCharView", "Form", 0, QApplication::UnicodeUTF8));
        charBox->setTitle(QString());
        label->setText(QApplication::translate("CreateCharView", "Name :", 0, QApplication::UnicodeUTF8));
        b_validate->setText(QApplication::translate("CreateCharView", "Validate", 0, QApplication::UnicodeUTF8));
        b_spritePerso1->setText(QString());
        b_spritePerso2->setText(QString());
        l_faction1->setText(QApplication::translate("CreateCharView", "Faction1", 0, QApplication::UnicodeUTF8));
        l_faction2->setText(QApplication::translate("CreateCharView", "Faction2", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CreateCharView: public Ui_CreateCharView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATECHAR_H
