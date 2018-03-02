/********************************************************************************
** Form generated from reading UI file 'configurewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGUREWINDOW_H
#define UI_CONFIGUREWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConfigureWindow
{
public:
    QLineEdit *lineEdit;
    QLabel *plantNameLabel;
    QPushButton *BackButton;
    QPushButton *ApplyButton;
    QComboBox *PlantTypeList;
    QLabel *plantPlantType;

    void setupUi(QWidget *ConfigureWindow)
    {
        if (ConfigureWindow->objectName().isEmpty())
            ConfigureWindow->setObjectName(QStringLiteral("ConfigureWindow"));
        ConfigureWindow->resize(640, 480);
        lineEdit = new QLineEdit(ConfigureWindow);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(260, 20, 231, 20));
        plantNameLabel = new QLabel(ConfigureWindow);
        plantNameLabel->setObjectName(QStringLiteral("plantNameLabel"));
        plantNameLabel->setGeometry(QRect(190, 20, 71, 20));
        BackButton = new QPushButton(ConfigureWindow);
        BackButton->setObjectName(QStringLiteral("BackButton"));
        BackButton->setGeometry(QRect(0, 0, 91, 101));
        QIcon icon;
        icon.addFile(QStringLiteral(":/BackButtonIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        BackButton->setIcon(icon);
        BackButton->setIconSize(QSize(85, 110));
        BackButton->setFlat(true);
        ApplyButton = new QPushButton(ConfigureWindow);
        ApplyButton->setObjectName(QStringLiteral("ApplyButton"));
        ApplyButton->setGeometry(QRect(0, 100, 91, 101));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/ApplyButtonIcon.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        ApplyButton->setIcon(icon1);
        ApplyButton->setIconSize(QSize(85, 110));
        ApplyButton->setFlat(true);
        PlantTypeList = new QComboBox(ConfigureWindow);
        PlantTypeList->setObjectName(QStringLiteral("PlantTypeList"));
        PlantTypeList->setGeometry(QRect(260, 50, 231, 21));
        plantPlantType = new QLabel(ConfigureWindow);
        plantPlantType->setObjectName(QStringLiteral("plantPlantType"));
        plantPlantType->setGeometry(QRect(190, 50, 71, 20));

        retranslateUi(ConfigureWindow);

        QMetaObject::connectSlotsByName(ConfigureWindow);
    } // setupUi

    void retranslateUi(QWidget *ConfigureWindow)
    {
        ConfigureWindow->setWindowTitle(QApplication::translate("ConfigureWindow", "Form", nullptr));
        plantNameLabel->setText(QApplication::translate("ConfigureWindow", "Plant Name", nullptr));
        BackButton->setText(QString());
        ApplyButton->setText(QString());
        plantPlantType->setText(QApplication::translate("ConfigureWindow", "Plant Type", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConfigureWindow: public Ui_ConfigureWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGUREWINDOW_H
