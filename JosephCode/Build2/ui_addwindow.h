/********************************************************************************
** Form generated from reading UI file 'addwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDWINDOW_H
#define UI_ADDWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddWindow
{
public:
    QPushButton *TestAddButton;

    void setupUi(QWidget *AddWindow)
    {
        if (AddWindow->objectName().isEmpty())
            AddWindow->setObjectName(QStringLiteral("AddWindow"));
        AddWindow->resize(640, 480);
        AddWindow->setAutoFillBackground(true);
        TestAddButton = new QPushButton(AddWindow);
        TestAddButton->setObjectName(QStringLiteral("TestAddButton"));
        TestAddButton->setGeometry(QRect(290, 160, 75, 23));

        retranslateUi(AddWindow);

        QMetaObject::connectSlotsByName(AddWindow);
    } // setupUi

    void retranslateUi(QWidget *AddWindow)
    {
        AddWindow->setWindowTitle(QApplication::translate("AddWindow", "Form", nullptr));
        TestAddButton->setText(QApplication::translate("AddWindow", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddWindow: public Ui_AddWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDWINDOW_H
