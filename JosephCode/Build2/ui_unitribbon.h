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
    QPushButton *pushButton;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *UnitRibbon)
    {
        if (UnitRibbon->objectName().isEmpty())
            UnitRibbon->setObjectName(QStringLiteral("UnitRibbon"));
        UnitRibbon->resize(540, 60);
        pushButton = new QPushButton(UnitRibbon);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(250, 0, 75, 23));
        label = new QLabel(UnitRibbon);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 81, 21));
        label_2 = new QLabel(UnitRibbon);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 30, 81, 21));

        retranslateUi(UnitRibbon);

        QMetaObject::connectSlotsByName(UnitRibbon);
    } // setupUi

    void retranslateUi(QWidget *UnitRibbon)
    {
        UnitRibbon->setWindowTitle(QApplication::translate("UnitRibbon", "Form", nullptr));
        pushButton->setText(QApplication::translate("UnitRibbon", "PushButton", nullptr));
        label->setText(QApplication::translate("UnitRibbon", "TextLabel", nullptr));
        label_2->setText(QApplication::translate("UnitRibbon", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UnitRibbon: public Ui_UnitRibbon {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UNITRIBBON_H
