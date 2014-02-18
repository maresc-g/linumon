/********************************************************************************
** Form generated from reading UI file 'inventoryview.ui'
**
** Created: Tue Feb 18 14:54:20 2014
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INVENTORYVIEW_H
#define UI_INVENTORYVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_inventoryview
{
public:
    QLabel *money;
    QFrame *frame;

    void setupUi(QWidget *inventoryview)
    {
        if (inventoryview->objectName().isEmpty())
            inventoryview->setObjectName(QString::fromUtf8("inventoryview"));
        inventoryview->resize(400, 300);
        money = new QLabel(inventoryview);
        money->setObjectName(QString::fromUtf8("money"));
        money->setGeometry(QRect(270, 270, 121, 21));
        money->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        frame = new QFrame(inventoryview);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 0, 381, 251));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        retranslateUi(inventoryview);

        QMetaObject::connectSlotsByName(inventoryview);
    } // setupUi

    void retranslateUi(QWidget *inventoryview)
    {
        inventoryview->setWindowTitle(QApplication::translate("inventoryview", "Form", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        inventoryview->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        inventoryview->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        money->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class inventoryview: public Ui_inventoryview {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INVENTORYVIEW_H
