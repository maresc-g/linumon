/********************************************************************************
** Form generated from reading UI file 'chatview.ui'
**
** Created: Wed Feb 19 14:00:46 2014
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATVIEW_H
#define UI_CHATVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QTextBrowser>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatView
{
public:
    QTextBrowser *tb_chat;
    QLineEdit *le_chatText;

    void setupUi(QWidget *ChatView)
    {
        if (ChatView->objectName().isEmpty())
            ChatView->setObjectName(QString::fromUtf8("ChatView"));
        ChatView->resize(407, 279);
        ChatView->setStyleSheet(QString::fromUtf8(""));
        tb_chat = new QTextBrowser(ChatView);
        tb_chat->setObjectName(QString::fromUtf8("tb_chat"));
        tb_chat->setGeometry(QRect(-1, 0, 411, 241));
        le_chatText = new QLineEdit(ChatView);
        le_chatText->setObjectName(QString::fromUtf8("le_chatText"));
        le_chatText->setGeometry(QRect(-2, 240, 411, 41));

        retranslateUi(ChatView);

        QMetaObject::connectSlotsByName(ChatView);
    } // setupUi

    void retranslateUi(QWidget *ChatView)
    {
        ChatView->setWindowTitle(QApplication::translate("ChatView", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ChatView: public Ui_ChatView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATVIEW_H
