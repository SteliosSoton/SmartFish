#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListWidgetItem>
#include <QList>
#include <QVector>
#include <QMainWindow>
#include <QPushButton>
#include "biobloomunit.h"
#include "settingswindow.h"
#include "addwindow.h"

namespace Ui {class MainWindow;}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QVector<BioBloomUnit*> unitAddresses;
    QVector<UnitRibbon*> ribbonAddresses;

    BioBloomUnit* exampleUnitAddress;   //Test example unit
    /*
     * on program startup, append this with pot information from database
     * fill scrollarea on MainWindow with UnitAddresses[i]->UnitRibbon
     * profit
     */

public slots:
    void buttonPressSlot();                         //Non-discriminating slot that closes MainWindow when another opens
    void addButtonPressSlot();
    void settingsButtonPressSlot();
    void unitAddedSlot();

private:
    Ui::MainWindow *ui;

    SettingsWindow* settingsWindowAddress;
    AddWindow* addWindowAddress;

    //void setupUnitAddresses();  //Reads data from SQL database and sets up units
    void setupOtherWindows();
    void setupPushButtons();

};

#endif // MAINWINDOW_H
