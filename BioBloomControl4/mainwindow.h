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

    QVector<BioBloomUnit*> unitAddress;
    QVector<UnitRibbon*> ribbonAddress;
    QVector<QListWidgetItem*> itemAddress;
    QVector<UnitWorker*> unitWorkerAddress;
    QVector<QThread*> unitThreadAddress;

    int unitTotal;

    /*
     * on program startup, append this with pot information from database
     * fill scrollarea on MainWindow with UnitAddresses[i]->UnitRibbon
     * profit
     */

public slots:
    void buttonPressSlot();                         //Non-discriminating slot that closes MainWindow when another opens
    void addButtonPressSlot();
    void unitAddedSlot();

private:
    Ui::MainWindow *ui;

    //void setupUnitAddresses();  //Reads data from SQL database and sets up units
    void setupOtherWindows();
    void setupPushButtons();


    void updateRibbon(int ribbonNumber, int unitNumber);

};

#endif // MAINWINDOW_H
