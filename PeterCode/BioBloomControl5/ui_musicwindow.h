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
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MusicWindow
{
public:
    QPushButton *BackButton;
    QListWidget *SongList;
    QPushButton *VolumeUp;
    QPushButton *VolumeDown;
    QLabel *label;

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
        SongList = new QListWidget(MusicWindow);
        SongList->setObjectName(QStringLiteral("SongList"));
        SongList->setGeometry(QRect(100, 0, 541, 481));
        VolumeUp = new QPushButton(MusicWindow);
        VolumeUp->setObjectName(QStringLiteral("VolumeUp"));
        VolumeUp->setGeometry(QRect(30, 150, 41, 41));
        VolumeDown = new QPushButton(MusicWindow);
        VolumeDown->setObjectName(QStringLiteral("VolumeDown"));
        VolumeDown->setGeometry(QRect(30, 260, 41, 41));
        label = new QLabel(MusicWindow);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 210, 61, 31));

        retranslateUi(MusicWindow);

        QMetaObject::connectSlotsByName(MusicWindow);
    } // setupUi

    void retranslateUi(QWidget *MusicWindow)
    {
        MusicWindow->setWindowTitle(QApplication::translate("MusicWindow", "Form", nullptr));
        BackButton->setText(QString());
        VolumeUp->setText(QApplication::translate("MusicWindow", "PushButton", nullptr));
        VolumeDown->setText(QApplication::translate("MusicWindow", "PushButton", nullptr));
        label->setText(QApplication::translate("MusicWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MusicWindow: public Ui_MusicWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MUSICWINDOW_H
