/********************************************************************************
** Form generated from reading UI file 'unitwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UNITWINDOW_H
#define UI_UNITWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UnitWindow
{
public:
    QPushButton *BackButton;
    QPushButton *MusicButton;
    QPushButton *pushButton;

    void setupUi(QWidget *UnitWindow)
    {
        if (UnitWindow->objectName().isEmpty())
            UnitWindow->setObjectName(QStringLiteral("UnitWindow"));
        UnitWindow->resize(640, 480);
        BackButton = new QPushButton(UnitWindow);
        BackButton->setObjectName(QStringLiteral("BackButton"));
        BackButton->setGeometry(QRect(0, 0, 91, 101));
        QIcon icon;
        icon.addFile(QStringLiteral(":/BackButtonIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        BackButton->setIcon(icon);
        BackButton->setIconSize(QSize(85, 110));
        BackButton->setFlat(true);
        MusicButton = new QPushButton(UnitWindow);
        MusicButton->setObjectName(QStringLiteral("MusicButton"));
        MusicButton->setGeometry(QRect(0, 100, 91, 101));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/MusicButtonIcon.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        MusicButton->setIcon(icon1);
        MusicButton->setIconSize(QSize(85, 110));
        MusicButton->setFlat(true);
        pushButton = new QPushButton(UnitWindow);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(110, 402, 121, 71));

        retranslateUi(UnitWindow);

        QMetaObject::connectSlotsByName(UnitWindow);
    } // setupUi

    void retranslateUi(QWidget *UnitWindow)
    {
        UnitWindow->setWindowTitle(QApplication::translate("UnitWindow", "Form", nullptr));
        BackButton->setText(QString());
        MusicButton->setText(QString());
        pushButton->setText(QApplication::translate("UnitWindow", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UnitWindow: public Ui_UnitWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UNITWINDOW_H
