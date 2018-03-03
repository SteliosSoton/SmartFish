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
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingsWindow
{
public:
    QPushButton *BackButton;
    QPushButton *MuteButton;
    QPushButton *ToggleLEDButton;
    QPushButton *ToggleWaterButton;
    QPushButton *ManualWaterButton;
    QLabel *WaterIcon;
    QPushButton *RedLEDButton;
    QPushButton *WhiteLEDButton;
    QPushButton *BlueLEDButton;
    QPushButton *CyanLEDButton;
    QPushButton *YellowLEDButton;
    QPushButton *GreenLEDButton;
    QPushButton *MagentaLEDButton;

    void setupUi(QWidget *SettingsWindow)
    {
        if (SettingsWindow->objectName().isEmpty())
            SettingsWindow->setObjectName(QStringLiteral("SettingsWindow"));
        SettingsWindow->resize(640, 480);
        SettingsWindow->setAutoFillBackground(true);
        BackButton = new QPushButton(SettingsWindow);
        BackButton->setObjectName(QStringLiteral("BackButton"));
        BackButton->setGeometry(QRect(0, 0, 91, 101));
        QIcon icon;
        icon.addFile(QStringLiteral(":/BackButtonIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        BackButton->setIcon(icon);
        BackButton->setIconSize(QSize(85, 110));
        BackButton->setFlat(true);
        MuteButton = new QPushButton(SettingsWindow);
        MuteButton->setObjectName(QStringLiteral("MuteButton"));
        MuteButton->setGeometry(QRect(0, 100, 91, 101));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/MuteButtonIcon.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        MuteButton->setIcon(icon1);
        MuteButton->setIconSize(QSize(85, 110));
        MuteButton->setFlat(true);
        ToggleLEDButton = new QPushButton(SettingsWindow);
        ToggleLEDButton->setObjectName(QStringLiteral("ToggleLEDButton"));
        ToggleLEDButton->setGeometry(QRect(320, 300, 91, 81));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/ToggleLEDButtonIcon.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        ToggleLEDButton->setIcon(icon2);
        ToggleLEDButton->setIconSize(QSize(161, 161));
        ToggleLEDButton->setFlat(true);
        ToggleWaterButton = new QPushButton(SettingsWindow);
        ToggleWaterButton->setObjectName(QStringLiteral("ToggleWaterButton"));
        ToggleWaterButton->setGeometry(QRect(160, 10, 161, 161));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/ToggleWaterButtonIcon.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        ToggleWaterButton->setIcon(icon3);
        ToggleWaterButton->setIconSize(QSize(200, 200));
        ToggleWaterButton->setFlat(true);
        ManualWaterButton = new QPushButton(SettingsWindow);
        ManualWaterButton->setObjectName(QStringLiteral("ManualWaterButton"));
        ManualWaterButton->setGeometry(QRect(400, 10, 171, 171));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/ManualWaterIcon.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        ManualWaterButton->setIcon(icon4);
        ManualWaterButton->setIconSize(QSize(200, 200));
        ManualWaterButton->setFlat(true);
        WaterIcon = new QLabel(SettingsWindow);
        WaterIcon->setObjectName(QStringLiteral("WaterIcon"));
        WaterIcon->setGeometry(QRect(320, 32, 101, 121));
        WaterIcon->setPixmap(QPixmap(QString::fromUtf8(":/WaterDroplet.png")));
        WaterIcon->setScaledContents(true);
        RedLEDButton = new QPushButton(SettingsWindow);
        RedLEDButton->setObjectName(QStringLiteral("RedLEDButton"));
        RedLEDButton->setGeometry(QRect(230, 230, 80, 51));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/RedLEDIcon.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        RedLEDButton->setIcon(icon5);
        RedLEDButton->setIconSize(QSize(80, 70));
        RedLEDButton->setFlat(true);
        WhiteLEDButton = new QPushButton(SettingsWindow);
        WhiteLEDButton->setObjectName(QStringLiteral("WhiteLEDButton"));
        WhiteLEDButton->setGeometry(QRect(330, 200, 80, 51));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/WhiteLEDIcon.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        WhiteLEDButton->setIcon(icon6);
        WhiteLEDButton->setIconSize(QSize(80, 70));
        WhiteLEDButton->setFlat(true);
        BlueLEDButton = new QPushButton(SettingsWindow);
        BlueLEDButton->setObjectName(QStringLiteral("BlueLEDButton"));
        BlueLEDButton->setGeometry(QRect(430, 230, 80, 51));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/BlueLEDIcon.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        BlueLEDButton->setIcon(icon7);
        BlueLEDButton->setIconSize(QSize(80, 70));
        BlueLEDButton->setFlat(true);
        CyanLEDButton = new QPushButton(SettingsWindow);
        CyanLEDButton->setObjectName(QStringLiteral("CyanLEDButton"));
        CyanLEDButton->setGeometry(QRect(460, 310, 80, 51));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/CyanLEDIcon.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        CyanLEDButton->setIcon(icon8);
        CyanLEDButton->setIconSize(QSize(80, 70));
        CyanLEDButton->setFlat(true);
        YellowLEDButton = new QPushButton(SettingsWindow);
        YellowLEDButton->setObjectName(QStringLiteral("YellowLEDButton"));
        YellowLEDButton->setGeometry(QRect(190, 310, 90, 60));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/YellowLEDIcon.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        YellowLEDButton->setIcon(icon9);
        YellowLEDButton->setIconSize(QSize(90, 80));
        YellowLEDButton->setFlat(true);
        GreenLEDButton = new QPushButton(SettingsWindow);
        GreenLEDButton->setObjectName(QStringLiteral("GreenLEDButton"));
        GreenLEDButton->setGeometry(QRect(250, 410, 80, 51));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/GreenLEDIcon.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        GreenLEDButton->setIcon(icon10);
        GreenLEDButton->setIconSize(QSize(80, 70));
        GreenLEDButton->setFlat(true);
        MagentaLEDButton = new QPushButton(SettingsWindow);
        MagentaLEDButton->setObjectName(QStringLiteral("MagentaLEDButton"));
        MagentaLEDButton->setGeometry(QRect(410, 410, 71, 51));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/MagentaLEDIcon.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        MagentaLEDButton->setIcon(icon11);
        MagentaLEDButton->setIconSize(QSize(80, 70));
        MagentaLEDButton->setFlat(true);

        retranslateUi(SettingsWindow);

        QMetaObject::connectSlotsByName(SettingsWindow);
    } // setupUi

    void retranslateUi(QWidget *SettingsWindow)
    {
        SettingsWindow->setWindowTitle(QApplication::translate("SettingsWindow", "Form", nullptr));
        BackButton->setText(QString());
        MuteButton->setText(QString());
        ToggleLEDButton->setText(QString());
        ToggleWaterButton->setText(QString());
        ManualWaterButton->setText(QString());
        WaterIcon->setText(QString());
        RedLEDButton->setText(QString());
        WhiteLEDButton->setText(QString());
        BlueLEDButton->setText(QString());
        CyanLEDButton->setText(QString());
        YellowLEDButton->setText(QString());
        GreenLEDButton->setText(QString());
        MagentaLEDButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SettingsWindow: public Ui_SettingsWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSWINDOW_H
