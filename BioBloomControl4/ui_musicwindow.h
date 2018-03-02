/********************************************************************************
** Form generated from reading UI file 'musicwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MUSICWINDOW_H
#define UI_MUSICWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MusicWindow
{
public:
    QPushButton *BackButton;
    QPushButton *BackButton_2;

    void setupUi(QWidget *MusicWindow)
    {
        if (MusicWindow->objectName().isEmpty())
            MusicWindow->setObjectName(QStringLiteral("MusicWindow"));
        MusicWindow->resize(640, 480);
        MusicWindow->setAutoFillBackground(true);
        BackButton = new QPushButton(MusicWindow);
        BackButton->setObjectName(QStringLiteral("BackButton"));
        BackButton->setGeometry(QRect(0, 0, 91, 101));
        QIcon icon;
        icon.addFile(QStringLiteral(":/BackButtonIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        BackButton->setIcon(icon);
        BackButton->setIconSize(QSize(85, 105));
        BackButton->setFlat(true);
        BackButton_2 = new QPushButton(MusicWindow);
        BackButton_2->setObjectName(QStringLiteral("BackButton_2"));
        BackButton_2->setGeometry(QRect(260, 200, 91, 101));
        BackButton_2->setIcon(icon);
        BackButton_2->setIconSize(QSize(85, 105));
        BackButton_2->setFlat(true);

        retranslateUi(MusicWindow);

        QMetaObject::connectSlotsByName(MusicWindow);
    } // setupUi

    void retranslateUi(QWidget *MusicWindow)
    {
        MusicWindow->setWindowTitle(QApplication::translate("MusicWindow", "Form", nullptr));
        BackButton->setText(QString());
        BackButton_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MusicWindow: public Ui_MusicWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MUSICWINDOW_H
