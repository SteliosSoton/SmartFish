/*                          Header File                         */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_unitribbon.h"

/*                   Constructor and Destructor                 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPalette WindowPalette;                                                                     //Create a palette
    WindowPalette.setColor(QPalette::Background, Qt::white);                                   //Configure the palette to fill the background with white
    this->setPalette(WindowPalette);                                                          //Set the palette

    /*
     * Method connected to 'add a planter' that generates instances of BioBloomUnits and
     * adds their BioBloomButtons to a QScrollArea
     */

    setupPushButtons();

    unitTotal = 0;







}

MainWindow::~MainWindow()
{
    delete ui;
}


/*                          Class Slots                       */
void MainWindow::addButtonPressSlot()
{
    unitAddress.append(new BioBloomUnit(this));                                                                                                            //Instance a new unit class
    unitAddress[unitTotal]->setUnitNumber(unitTotal);
    unitAddress[unitTotal]->setMacAddress("2C:3A:E8:37:D8:6A");

    ribbonAddress.append(new UnitRibbon(unitAddress[unitTotal], this));                                                                                    //Instance a new unit ribbon class
    ribbonAddress[unitTotal]->setRibbonNumber(unitTotal);

    itemAddress.append(new QListWidgetItem(ui->UnitList));                                                                                                 //Instance a new list widget item

    itemAddress[unitTotal]->setSizeHint(ribbonAddress[unitTotal]->size());                                                                                 //Let list widget item know about size of unit ribbon
    ui->UnitList->setItemWidget(itemAddress[unitTotal], ribbonAddress[unitTotal]);                                                                        //Set the unit ribbon in the list widget item
    ui->UnitList->addItem(itemAddress[unitTotal]);                                                                                                       //Add the item to the list

    connect(ribbonAddress[unitTotal]->ui->RibbonButton, SIGNAL(released()), unitAddress[unitTotal], SLOT(unitRibbonPressSlot()) );                          //Connect the unit ribbon button to the unitRibbonPressSlot of the unit class
    connect(ribbonAddress[unitTotal]->ui->ConfigureButton, SIGNAL(released()), unitAddress[unitTotal], SLOT(unitRibbonConfigureButtonPressSlot()) );       //Connect the unit ribbon's configure button to the unitRibbonConfigureButtonPressSlot of the unit class

    unitAddress[unitTotal]->setPlantProfileTemplate(unitAddress[unitTotal]->configureWindowAddress->plantProfile[0]);

    ribbonAddress[unitTotal]->updateData();

    unitWorkerAddress.append(new UnitWorker(unitAddress[unitTotal]));                                                                       //Instance a new worker for the unit
    unitThreadAddress.append(new QThread);                                                                                                 //Instance a new thread for the worker

    unitWorkerAddress[unitTotal]->moveToThread(unitThreadAddress[unitTotal]);                                                               //Move the unit's worker to the unit's thread

    connect(unitWorkerAddress[unitTotal], SIGNAL(error(QString)), this, SLOT(errorString(QString)));
    connect(unitThreadAddress[unitTotal], SIGNAL(started()), unitWorkerAddress[unitTotal], SLOT(process()));
    //connect(unitWorkerAddress[unitTotal], SIGNAL(finished()), unitThreadAddress[unitTotal], SLOT(quit()));
    //connect(unitWorkerAddress[unitTotal], SIGNAL(finished()), unitWorkerAddress[unitTotal], SLOT(deleteLater()));
    //connect(unitThreadAddress[unitTotal], SIGNAL(finished()), unitThreadAddress[unitTotal], SLOT(deleteLater()));

    connect(unitWorkerAddress[unitTotal], SIGNAL(finishedSignal(int)), this, SLOT(threadFinishSlot(int)));
    connect(unitWorkerAddress[unitTotal], SIGNAL(networkPostSignal(QNetworkRequest, QByteArray)), unitAddress[unitTotal], SLOT(threadNetworkPostSlot(QNetworkRequest, QByteArray)) );

    unitThreadAddress[unitTotal]->start();

    unitTotal += 1;                                                                                                                                         //Increment the number of units on the system by 1

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(macRequestFinished(QNetworkReply*)),
            this, SLOT(macReplyFinished(QNetworkReply*)));

    QUrl url;
    QByteArray postData;
    qDebug() << "FUCK FUCK FUCK FUCK FUCK (IT'S HERE)";
    url.setUrl("http://192.168.5.1:80/return_macs.php");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    QString postKey = "pointless";
    QString postValue = "1";

    postData.append(postKey).append("=").append(postValue).append("&");
    manager->post(request,postData);

    //returns comma seperated mac addresses
}

void MainWindow::threadFinishSlot(int unitNumber)
{
    qDebug() << "threadFinishSlot" << unitNumber;
    ribbonAddress[unitNumber]->updateData();
    unitAddress[unitNumber]->windowAddress->updateData();
    unitWorkerAddress[unitNumber]->updateData();

    //SET BATTERY AND WATER LEVEL WARNING ICONS ON RIBBON
}

/*                         Class Methods                      */
void MainWindow::setupPushButtons()
{
    connect(ui->AddButton, SIGNAL(released()), this, SLOT(addButtonPressSlot()) );
}

void MainWindow:: macReplyFinished(QNetworkReply* reply)
{
    reply->deleteLater();
    QByteArray data_reply = reply->readAll();
    qDebug() << "START HERE";
    qDebug()<< data_reply;
    qDebug()<< "END HERE";

}
void MainWindow:: macRequestFinished(QNetworkReply*){}
