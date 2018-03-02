/********************************************************************************
** Form generated from reading UI file 'unitribbon.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UNITRIBBON_H
#define UI_UNITRIBBON_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UnitRibbon
{
public:
    QPushButton *RibbonButton;
    QLabel *plantNameLabel;
    QLabel *plantTypeLabel;
    QPushButton *ConfigureButton;
    QLabel *waterLevelWarning;
    QLabel *batteryLevelWarning;

    void setupUi(QWidget *UnitRibbon)
    {
        if (UnitRibbon->objectName().isEmpty())
            UnitRibbon->setObjectName(QStringLiteral("UnitRibbon"));
        UnitRibbon->resize(540, 60);
        RibbonButton = new QPushButton(UnitRibbon);
        RibbonButton->setObjectName(QStringLiteral("RibbonButton"));
        RibbonButton->setGeometry(QRect(4, 0, 531, 61));
        RibbonButton->setFlat(true);
        plantNameLabel = new QLabel(UnitRibbon);
        plantNameLabel->setObjectName(QStringLiteral("plantNameLabel"));
        plantNameLabel->setGeometry(QRect(10, 10, 81, 21));
        QFont font;
        font.setPointSize(10);
        plantNameLabel->setFont(font);
        plantTypeLabel = new QLabel(UnitRibbon);
        plantTypeLabel->setObjectName(QStringLiteral("plantTypeLabel"));
        plantTypeLabel->setGeometry(QRect(10, 30, 81, 21));
        plantTypeLabel->setFont(font);
        plantTypeLabel->setTextFormat(Qt::PlainText);
        ConfigureButton = new QPushButton(UnitRibbon);
        ConfigureButton->setObjectName(QStringLiteral("ConfigureButton"));
        ConfigureButton->setGeometry(QRect(484, 10, 51, 41));
        QIcon icon;
        icon.addFile(QStringLiteral(":/ConfigureButtonIcon.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        ConfigureButton->setIcon(icon);
        ConfigureButton->setIconSize(QSize(70, 70));
        ConfigureButton->setFlat(true);
        waterLevelWarning = new QLabel(UnitRibbon);
        waterLevelWarning->setObjectName(QStringLiteral("waterLevelWarning"));
        waterLevelWarning->setGeometry(QRect(350, 10, 47, 41));
        batteryLevelWarning = new QLabel(UnitRibbon);
        batteryLevelWarning->setObjectName(QStringLiteral("batteryLevelWarning"));
        batteryLevelWarning->setGeometry(QRect(420, 10, 47, 41));

        retranslateUi(UnitRibbon);

        QMetaObject::connectSlotsByName(UnitRibbon);
    } // setupUi

    void retranslateUi(QWidget *UnitRibbon)
    {
        UnitRibbon->setWindowTitle(QApplication::translate("UnitRibbon", "Form", nullptr));
        RibbonButton->setText(QString());
        plantNameLabel->setText(QApplication::translate("UnitRibbon", "TextLabel", nullptr));
        plantTypeLabel->setText(QApplication::translate("UnitRibbon", "TextLabel", nullptr));
        ConfigureButton->setText(QString());
        waterLevelWarning->setText(QString());
        batteryLevelWarning->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class UnitRibbon: public Ui_UnitRibbon {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UNITRIBBON_H
