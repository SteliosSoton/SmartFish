/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *ExampleButton;
    QListWidget *UnitList;
    QPushButton *AddButton;
    QPushButton *SettingsButton;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(640, 480);
        MainWindow->setAutoFillBackground(true);
        MainWindow->setDockOptions(QMainWindow::AllowNestedDocks|QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        ExampleButton = new QPushButton(centralWidget);
        ExampleButton->setObjectName(QStringLiteral("ExampleButton"));
        ExampleButton->setGeometry(QRect(0, 200, 91, 101));
        UnitList = new QListWidget(centralWidget);
        UnitList->setObjectName(QStringLiteral("UnitList"));
        UnitList->setGeometry(QRect(90, 0, 551, 451));
        AddButton = new QPushButton(centralWidget);
        AddButton->setObjectName(QStringLiteral("AddButton"));
        AddButton->setEnabled(true);
        AddButton->setGeometry(QRect(0, 0, 91, 101));
        QIcon icon;
        icon.addFile(QStringLiteral(":/AddButtonIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        AddButton->setIcon(icon);
        AddButton->setIconSize(QSize(85, 101));
        AddButton->setFlat(true);
        SettingsButton = new QPushButton(centralWidget);
        SettingsButton->setObjectName(QStringLiteral("SettingsButton"));
        SettingsButton->setGeometry(QRect(0, 100, 91, 101));
        SettingsButton->setStyleSheet(QLatin1String("none\n"
""));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/SettingsButtonIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        SettingsButton->setIcon(icon1);
        SettingsButton->setIconSize(QSize(85, 101));
        SettingsButton->setFlat(true);
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        ExampleButton->setText(QApplication::translate("MainWindow", "example", nullptr));
        AddButton->setText(QString());
        SettingsButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
