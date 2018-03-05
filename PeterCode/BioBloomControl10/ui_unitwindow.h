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
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UnitWindow
{
public:
    QPushButton *BackButton;
    QPushButton *MusicButton;
    QPushButton *SettingsButton;
    QListWidget *DataList;
    QPushButton *PlantName;

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
        SettingsButton = new QPushButton(UnitWindow);
        SettingsButton->setObjectName(QStringLiteral("SettingsButton"));
        SettingsButton->setGeometry(QRect(0, 200, 91, 101));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/SettingsButtonIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        SettingsButton->setIcon(icon2);
        SettingsButton->setIconSize(QSize(85, 110));
        SettingsButton->setFlat(true);
        DataList = new QListWidget(UnitWindow);
        DataList->setObjectName(QStringLiteral("DataList"));
        DataList->setGeometry(QRect(100, 190, 151, 280));
        DataList->setFrameShape(QFrame::NoFrame);
        PlantName = new QPushButton(UnitWindow);
        PlantName->setObjectName(QStringLiteral("PlantName"));
        PlantName->setGeometry(QRect(100, 10, 171, 41));
        QFont font;
        font.setFamily(QStringLiteral("Calibri"));
        font.setPointSize(20);
        PlantName->setFont(font);
        PlantName->setFlat(true);

        retranslateUi(UnitWindow);

        DataList->setCurrentRow(-1);


        QMetaObject::connectSlotsByName(UnitWindow);
    } // setupUi

    void retranslateUi(QWidget *UnitWindow)
    {
        UnitWindow->setWindowTitle(QApplication::translate("UnitWindow", "Form", nullptr));
        BackButton->setText(QString());
        MusicButton->setText(QString());
        SettingsButton->setText(QString());
        PlantName->setText(QApplication::translate("UnitWindow", "PlantName", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UnitWindow: public Ui_UnitWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UNITWINDOW_H
