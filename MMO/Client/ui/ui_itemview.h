/********************************************************************************
** Form generated from reading UI file 'itemview.ui'
**
** Created: Mon Feb 17 14:21:44 2014
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ITEMVIEW_H
#define UI_ITEMVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_itemview
{
public:

    void setupUi(QWidget *itemview)
    {
        if (itemview->objectName().isEmpty())
            itemview->setObjectName(QString::fromUtf8("itemview"));
        itemview->resize(119, 79);

        retranslateUi(itemview);

        QMetaObject::connectSlotsByName(itemview);
    } // setupUi

    void retranslateUi(QWidget *itemview)
    {
        itemview->setWindowTitle(QApplication::translate("itemview", "Form", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        itemview->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        itemview->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
    } // retranslateUi

};

namespace Ui {
    class itemview: public Ui_itemview {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ITEMVIEW_H
