/********************************************************************************
** Form generated from reading UI file 'loginview.ui'
**
** Created: Tue Feb 18 14:54:20 2014
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINVIEW_H
#define UI_LOGINVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_loginView
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QWidget *loginForm;
    QGridLayout *gridLayout_9;
    QGridLayout *gridLayout_8;
    QLineEdit *le_Login;
    QLineEdit *le_Pass;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QLabel *label;
    QPushButton *bConnect;
    QPushButton *bRegister;

    void setupUi(QWidget *loginView)
    {
        if (loginView->objectName().isEmpty())
            loginView->setObjectName(QString::fromUtf8("loginView"));
        loginView->resize(685, 610);
        loginView->setStyleSheet(QString::fromUtf8(""));
        gridLayout = new QGridLayout(loginView);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalSpacer = new QSpacerItem(20, 150, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer, 0, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 160, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_2, 3, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(160, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 2, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(160, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 2, 2, 1, 1);

        loginForm = new QWidget(loginView);
        loginForm->setObjectName(QString::fromUtf8("loginForm"));
        loginForm->setMinimumSize(QSize(335, 270));
        loginForm->setMaximumSize(QSize(335, 270));
        gridLayout_9 = new QGridLayout(loginForm);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        gridLayout_8 = new QGridLayout();
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        gridLayout_8->setSizeConstraint(QLayout::SetFixedSize);
        le_Login = new QLineEdit(loginForm);
        le_Login->setObjectName(QString::fromUtf8("le_Login"));

        gridLayout_8->addWidget(le_Login, 1, 2, 1, 1);

        le_Pass = new QLineEdit(loginForm);
        le_Pass->setObjectName(QString::fromUtf8("le_Pass"));
        le_Pass->setEchoMode(QLineEdit::Password);

        gridLayout_8->addWidget(le_Pass, 2, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_8->addItem(horizontalSpacer, 1, 1, 1, 1);

        label_2 = new QLabel(loginForm);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_8->addWidget(label_2, 2, 0, 1, 1);

        label = new QLabel(loginForm);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_8->addWidget(label, 1, 0, 1, 1);

        bConnect = new QPushButton(loginForm);
        bConnect->setObjectName(QString::fromUtf8("bConnect"));
        bConnect->setMaximumSize(QSize(100, 16777215));

        gridLayout_8->addWidget(bConnect, 3, 2, 1, 1);

        bRegister = new QPushButton(loginForm);
        bRegister->setObjectName(QString::fromUtf8("bRegister"));
        bRegister->setMaximumSize(QSize(100, 16777215));

        gridLayout_8->addWidget(bRegister, 4, 2, 1, 1);


        gridLayout_9->addLayout(gridLayout_8, 0, 0, 1, 1);


        gridLayout->addWidget(loginForm, 2, 1, 1, 1);


        retranslateUi(loginView);

        QMetaObject::connectSlotsByName(loginView);
    } // setupUi

    void retranslateUi(QWidget *loginView)
    {
        loginView->setWindowTitle(QApplication::translate("loginView", "Form", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("loginView", "Password :", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("loginView", "Login :", 0, QApplication::UnicodeUTF8));
        bConnect->setText(QApplication::translate("loginView", "Connect", 0, QApplication::UnicodeUTF8));
        bRegister->setText(QApplication::translate("loginView", "Register", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class loginView: public Ui_loginView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINVIEW_H
