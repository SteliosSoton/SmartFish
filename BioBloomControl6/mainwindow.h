#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListWidgetItem>
#include <QList>
#include <QVector>
#include <QMainWindow>
#include <QPushButton>
#include <QtNetwork\QNetworkAccessManager>
#include <QUrl>
#include <QUrlQuery>
#include <QThread>
#include "biobloomunit.h"
#include "settingswindow.h"
#include "plantprofile.h"
#include "unitworker.h"

namespace Ui {class MainWindow;}

class PlantProfile;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QVector<BioBloomUnit*> unitAddress;             //Vector storing all the units
    QVector<UnitRibbon*> ribbonAddress;            //Vector storing all the ribbons
    QVector<QListWidgetItem*> itemAddress;        //Vector storing the list items containing the ribbons
    QVector<UnitWorker*> unitWorkerAddress;      //Vector storing the worker functions for the units
    QVector<QThread*> unitThreadAddress;        //Vector storing the threads for the units

    int unitTotal;                                 //Number of units so far

    /*
     * on program startup, append this with pot information from database
     * fill scrollarea on MainWindow with UnitAddresses[i]->UnitRibbon
     * profit
     */

public slots:
    void addButtonPressSlot();
    void threadFinishSlot(int unitNumber);

private:
    Ui::MainWindow *ui;

    //void setupUnitAddresses();  //Reads data from SQL database and sets up units
    void setupPushButtons();


    void updateRibbon(int ribbonNumber, int unitNumber);                                //NEEDS TO HAPPEN WHEN FINISHED SIGNAL OF THREAD IS EMITTED

};

#endif // MAINWINDOW_H
