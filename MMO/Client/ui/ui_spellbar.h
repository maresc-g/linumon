/********************************************************************************
** Form generated from reading UI file 'spellbar.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPELLBAR_H
#define UI_SPELLBAR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SpellBarView
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *b_spell1;
    QPushButton *b_spell2;
    QPushButton *b_spell3;
    QPushButton *b_spell4;
    QPushButton *b_spell5;
    QPushButton *b_spell6;
    QPushButton *b_spell7;
    QPushButton *b_spell8;
    QPushButton *b_spell9;
    QPushButton *b_spell10;

    void setupUi(QWidget *SpellBarView)
    {
        if (SpellBarView->objectName().isEmpty())
            SpellBarView->setObjectName(QString::fromUtf8("SpellBarView"));
        SpellBarView->resize(569, 52);
        SpellBarView->setStyleSheet(QString::fromUtf8(""));
        horizontalLayoutWidget = new QWidget(SpellBarView);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(4, 1, 561, 51));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(5);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        b_spell1 = new QPushButton(horizontalLayoutWidget);
        b_spell1->setObjectName(QString::fromUtf8("b_spell1"));
        b_spell1->setEnabled(false);

        horizontalLayout->addWidget(b_spell1);

        b_spell2 = new QPushButton(horizontalLayoutWidget);
        b_spell2->setObjectName(QString::fromUtf8("b_spell2"));
        b_spell2->setEnabled(false);

        horizontalLayout->addWidget(b_spell2);

        b_spell3 = new QPushButton(horizontalLayoutWidget);
        b_spell3->setObjectName(QString::fromUtf8("b_spell3"));
        b_spell3->setEnabled(false);

        horizontalLayout->addWidget(b_spell3);

        b_spell4 = new QPushButton(horizontalLayoutWidget);
        b_spell4->setObjectName(QString::fromUtf8("b_spell4"));
        b_spell4->setEnabled(false);

        horizontalLayout->addWidget(b_spell4);

        b_spell5 = new QPushButton(horizontalLayoutWidget);
        b_spell5->setObjectName(QString::fromUtf8("b_spell5"));
        b_spell5->setEnabled(false);

        horizontalLayout->addWidget(b_spell5);

        b_spell6 = new QPushButton(horizontalLayoutWidget);
        b_spell6->setObjectName(QString::fromUtf8("b_spell6"));
        b_spell6->setEnabled(false);

        horizontalLayout->addWidget(b_spell6);

        b_spell7 = new QPushButton(horizontalLayoutWidget);
        b_spell7->setObjectName(QString::fromUtf8("b_spell7"));
        b_spell7->setEnabled(false);

        horizontalLayout->addWidget(b_spell7);

        b_spell8 = new QPushButton(horizontalLayoutWidget);
        b_spell8->setObjectName(QString::fromUtf8("b_spell8"));
        b_spell8->setEnabled(false);

        horizontalLayout->addWidget(b_spell8);

        b_spell9 = new QPushButton(horizontalLayoutWidget);
        b_spell9->setObjectName(QString::fromUtf8("b_spell9"));
        b_spell9->setEnabled(false);

        horizontalLayout->addWidget(b_spell9);

        b_spell10 = new QPushButton(horizontalLayoutWidget);
        b_spell10->setObjectName(QString::fromUtf8("b_spell10"));
        b_spell10->setEnabled(false);

        horizontalLayout->addWidget(b_spell10);


        retranslateUi(SpellBarView);

        QMetaObject::connectSlotsByName(SpellBarView);
    } // setupUi

    void retranslateUi(QWidget *SpellBarView)
    {
        SpellBarView->setWindowTitle(QApplication::translate("SpellBarView", "Form", 0, QApplication::UnicodeUTF8));
        b_spell1->setText(QString());
        b_spell2->setText(QString());
        b_spell3->setText(QString());
        b_spell4->setText(QString());
        b_spell5->setText(QString());
        b_spell6->setText(QString());
        b_spell7->setText(QString());
        b_spell8->setText(QString());
        b_spell9->setText(QString());
        b_spell10->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SpellBarView: public Ui_SpellBarView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPELLBAR_H
