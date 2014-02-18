/********************************************************************************
** Form generated from reading UI file 'stuffview.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STUFFVIEW_H
#define UI_STUFFVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_stuffview
{
public:
    QLabel *labelPlastron;
    QLabel *labelAmu;
    QLabel *labelSac1;
    QLabel *labelAnneau;
    QLabel *labelCape;
    QLabel *labelCasque;
    QLabel *labelSac2;
    QLabel *labelArme;
    QLabel *labelBottes;
    QLabel *labelEpau;

    void setupUi(QWidget *stuffview)
    {
        if (stuffview->objectName().isEmpty())
            stuffview->setObjectName(QString::fromUtf8("stuffview"));
        stuffview->resize(500, 500);
        labelPlastron = new QLabel(stuffview);
        labelPlastron->setObjectName(QString::fromUtf8("labelPlastron"));
        labelPlastron->setGeometry(QRect(0, 200, 120, 20));
        labelPlastron->setAlignment(Qt::AlignCenter);
        labelAmu = new QLabel(stuffview);
        labelAmu->setObjectName(QString::fromUtf8("labelAmu"));
        labelAmu->setGeometry(QRect(380, 0, 120, 20));
        labelAmu->setAlignment(Qt::AlignCenter);
        labelSac1 = new QLabel(stuffview);
        labelSac1->setObjectName(QString::fromUtf8("labelSac1"));
        labelSac1->setGeometry(QRect(380, 300, 120, 20));
        labelSac1->setAlignment(Qt::AlignCenter);
        labelAnneau = new QLabel(stuffview);
        labelAnneau->setObjectName(QString::fromUtf8("labelAnneau"));
        labelAnneau->setGeometry(QRect(380, 100, 120, 20));
        labelAnneau->setAlignment(Qt::AlignCenter);
        labelCape = new QLabel(stuffview);
        labelCape->setObjectName(QString::fromUtf8("labelCape"));
        labelCape->setGeometry(QRect(0, 300, 120, 20));
        labelCape->setAlignment(Qt::AlignCenter);
        labelCasque = new QLabel(stuffview);
        labelCasque->setObjectName(QString::fromUtf8("labelCasque"));
        labelCasque->setGeometry(QRect(0, 0, 120, 20));
        labelCasque->setAutoFillBackground(false);
        labelCasque->setAlignment(Qt::AlignCenter);
        labelSac2 = new QLabel(stuffview);
        labelSac2->setObjectName(QString::fromUtf8("labelSac2"));
        labelSac2->setGeometry(QRect(380, 400, 120, 20));
        labelSac2->setAlignment(Qt::AlignCenter);
        labelArme = new QLabel(stuffview);
        labelArme->setObjectName(QString::fromUtf8("labelArme"));
        labelArme->setGeometry(QRect(380, 200, 120, 20));
        labelArme->setAlignment(Qt::AlignCenter);
        labelBottes = new QLabel(stuffview);
        labelBottes->setObjectName(QString::fromUtf8("labelBottes"));
        labelBottes->setGeometry(QRect(0, 400, 120, 20));
        labelBottes->setAlignment(Qt::AlignCenter);
        labelEpau = new QLabel(stuffview);
        labelEpau->setObjectName(QString::fromUtf8("labelEpau"));
        labelEpau->setGeometry(QRect(0, 100, 120, 20));
        labelEpau->setAlignment(Qt::AlignCenter);

        retranslateUi(stuffview);

        QMetaObject::connectSlotsByName(stuffview);
    } // setupUi

    void retranslateUi(QWidget *stuffview)
    {
        stuffview->setWindowTitle(QApplication::translate("stuffview", "Form", 0, QApplication::UnicodeUTF8));
        labelPlastron->setText(QApplication::translate("stuffview", "Plastron", 0, QApplication::UnicodeUTF8));
        labelAmu->setText(QApplication::translate("stuffview", "Amulette", 0, QApplication::UnicodeUTF8));
        labelSac1->setText(QApplication::translate("stuffview", "Sac", 0, QApplication::UnicodeUTF8));
        labelAnneau->setText(QApplication::translate("stuffview", "Anneau", 0, QApplication::UnicodeUTF8));
        labelCape->setText(QApplication::translate("stuffview", "Cape", 0, QApplication::UnicodeUTF8));
        labelCasque->setText(QApplication::translate("stuffview", "Casque", 0, QApplication::UnicodeUTF8));
        labelSac2->setText(QApplication::translate("stuffview", "Sac", 0, QApplication::UnicodeUTF8));
        labelArme->setText(QApplication::translate("stuffview", "Arme", 0, QApplication::UnicodeUTF8));
        labelBottes->setText(QApplication::translate("stuffview", "Bottes", 0, QApplication::UnicodeUTF8));
        labelEpau->setText(QApplication::translate("stuffview", "Epaulettes", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class stuffview: public Ui_stuffview {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STUFFVIEW_H
