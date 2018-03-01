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
#include "biobloomunit.h"
#include "settingswindow.h"
#include "plantprofile.h"

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

    QVector<PlantProfile> plantProfile;

    //void setupUnitAddresses();  //Reads data from SQL database and sets up units
    void setupOtherWindows();
    void setupPushButtons();
    void setupPlantProfiles();

};

#endif // MAINWINDOW_H
