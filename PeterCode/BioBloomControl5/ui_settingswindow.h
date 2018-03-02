/********************************************************************************
** Form generated from reading UI file 'settingswindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSWINDOW_H
#define UI_SETTINGSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingsWindow
{
public:
    QPushButton *BackButton;
    QPushButton *MuteButton;
    QPushButton *ToggleLEDButton;
    QPushButton *RGBControlButton;
    QPushButton *ToggleWaterButton;

    void setupUi(QWidget *SettingsWindow)
    {
        if (SettingsWindow->objectName().isEmpty())
            SettingsWindow->setObjectName(QStringLiteral("SettingsWindow"));
        SettingsWindow->resize(640, 480);
        SettingsWindow->setAutoFillBackground(true);
        BackButton = new QPushButton(SettingsWindow);
        BackButton->setObjectName(QStringLiteral("BackButton"));
        BackButton->setGeometry(QRect(30, 30, 161, 161));
        QIcon icon;
        icon.addFile(QStringLiteral(":/BackButtonIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        BackButton->setIcon(icon);
        BackButton->setIconSize(QSize(161, 161));
        BackButton->setFlat(true);
        MuteButton = new QPushButton(SettingsWindow);
        MuteButton->setObjectName(QStringLiteral("MuteButton"));
        MuteButton->setGeometry(QRect(450, 30, 161, 161));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/MuteButtonIcon.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        MuteButton->setIcon(icon1);
        MuteButton->setIconSize(QSize(141, 141));
        MuteButton->setFlat(true);
        ToggleLEDButton = new QPushButton(SettingsWindow);
        ToggleLEDButton->setObjectName(QStringLiteral("ToggleLEDButton"));
        ToggleLEDButton->setGeometry(QRect(240, 280, 161, 161));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/ToggleLEDButtonIcon.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        ToggleLEDButton->setIcon(icon2);
        ToggleLEDButton->setIconSize(QSize(161, 161));
        ToggleLEDButton->setFlat(true);
        RGBControlButton = new QPushButton(SettingsWindow);
        RGBControlButton->setObjectName(QStringLiteral("RGBControlButton"));
        RGBControlButton->setGeometry(QRect(450, 280, 161, 161));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/RGBControlButtonIcon.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        RGBControlButton->setIcon(icon3);
        RGBControlButton->setIconSize(QSize(161, 161));
        RGBControlButton->setFlat(true);
        ToggleWaterButton = new QPushButton(SettingsWindow);
        ToggleWaterButton->setObjectName(QStringLiteral("ToggleWaterButton"));
        ToggleWaterButton->setGeometry(QRect(30, 280, 161, 161));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/ToggleWaterButtonIcon.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        ToggleWaterButton->setIcon(icon4);
        ToggleWaterButton->setIconSize(QSize(200, 200));
        ToggleWaterButton->setFlat(true);

        retranslateUi(SettingsWindow);

        QMetaObject::connectSlotsByName(SettingsWindow);
    } // setupUi

    void retranslateUi(QWidget *SettingsWindow)
    {
        SettingsWindow->setWindowTitle(QApplication::translate("SettingsWindow", "Form", nullptr));
        BackButton->setText(QString());
        MuteButton->setText(QString());
        ToggleLEDButton->setText(QString());
        RGBControlButton->setText(QString());
        ToggleWaterButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SettingsWindow: public Ui_SettingsWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSWINDOW_H
