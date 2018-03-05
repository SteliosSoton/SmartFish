/********************************************************************************
** Form generated from reading UI file 'dataribbon.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATARIBBON_H
#define UI_DATARIBBON_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DataRibbon
{
public:
    QLabel *dataTitle;
    QLabel *dataNumber;
    QPushButton *RibbonButton;

    void setupUi(QWidget *DataRibbon)
    {
        if (DataRibbon->objectName().isEmpty())
            DataRibbon->setObjectName(QStringLiteral("DataRibbon"));
        DataRibbon->resize(144, 68);
        dataTitle = new QLabel(DataRibbon);
        dataTitle->setObjectName(QStringLiteral("dataTitle"));
        dataTitle->setGeometry(QRect(10, 3, 121, 20));
        QFont font;
        font.setFamily(QStringLiteral("Calibri"));
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        dataTitle->setFont(font);
        dataTitle->setFrameShape(QFrame::NoFrame);
        dataNumber = new QLabel(DataRibbon);
        dataNumber->setObjectName(QStringLiteral("dataNumber"));
        dataNumber->setGeometry(QRect(30, 30, 81, 31));
        QFont font1;
        font1.setFamily(QStringLiteral("Calibri"));
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        dataNumber->setFont(font1);
        RibbonButton = new QPushButton(DataRibbon);
        RibbonButton->setObjectName(QStringLiteral("RibbonButton"));
        RibbonButton->setGeometry(QRect(4, 2, 141, 61));
        RibbonButton->setFlat(true);

        retranslateUi(DataRibbon);

        QMetaObject::connectSlotsByName(DataRibbon);
    } // setupUi

    void retranslateUi(QWidget *DataRibbon)
    {
        DataRibbon->setWindowTitle(QApplication::translate("DataRibbon", "Form", nullptr));
        dataTitle->setText(QApplication::translate("DataRibbon", "TextLabel", nullptr));
        dataNumber->setText(QApplication::translate("DataRibbon", "TextLabel", nullptr));
        RibbonButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DataRibbon: public Ui_DataRibbon {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATARIBBON_H
