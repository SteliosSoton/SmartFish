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

    //ownedUnits = new QStringList;
    //unnamedMacAddresseses = new QStringList;
    imageForProfiles = new ConfigureWindow(NULL,NULL);

    unitTotal = 0;

    qDebug() << "3";

    connect(this, SIGNAL(macFindFinished()), this, SLOT(macFindFinishedSlot()));

    loadPreexistingUnits();

    qDebug() << "8";

}

MainWindow::~MainWindow()
{
    delete ui;
}


/*                          Class Slots                       */
void MainWindow::addButtonPressSlot()
{
    qDebug() << "9";

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(unnamedMacsFinished(QNetworkReply*)));

    QUrl url;
    QByteArray postData;
    url.setUrl("http://192.168.5.1:80/return_macs.php");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    QString postKey = "pointless";
    QString postValue = "1";

    qDebug() << request.url();
    postData.append(postKey).append("=").append(postValue).append("&");
    manager->post(request,postData);

    qDebug() << "10";

    //returns comma seperated mac addresses



}

void MainWindow::threadFinishSlot(int unitNumber)
{
    qDebug() << "threadFinishSlot" << unitNumber;
    ribbonAddress[unitNumber]->updateData();
    unitAddress[unitNumber]->windowAddress->updateData();
}

void MainWindow::macFindFinishedSlot()
{
    qDebug() << "7";

    for(int i = 0; i < ((ownedUnits.count())/3); i++)
    {

        qDebug() << "6";

        int macAddressLocation = 0+(3*unitTotal);
        int profile = 1+(3*unitTotal);
        int names = 2+(3*unitTotal);

        QString debugString1;
        QString debugString2;
        QString debugString3;

        unitAddress.append(new BioBloomUnit(this));                                                                                                            //Instance a new unit class
        unitAddress[unitTotal]->setUnitNumber(unitTotal);

        unitAddress[unitTotal]->setMacAddress((QString)ownedUnits.at(macAddressLocation));

        if(((QString)ownedUnits.at(profile)) == "Default")
            unitAddress[unitTotal]->setPlantProfileTemplate(imageForProfiles->plantProfile[0]);

        else if(((QString)ownedUnits.at(profile)) == "Aloe Cactus")
            unitAddress[unitTotal]->setPlantProfileTemplate(imageForProfiles->plantProfile[1]);

        else if(((QString)ownedUnits.at(profile)) == "Spider Plant")
            unitAddress[unitTotal]->setPlantProfileTemplate(imageForProfiles->plantProfile[2]);

        else if(((QString)ownedUnits.at(profile)) == "Peace Lily")
            unitAddress[unitTotal]->setPlantProfileTemplate(imageForProfiles->plantProfile[3]);

        else if(((QString)ownedUnits.at(profile)) == "Venus Fly Trap")
            unitAddress[unitTotal]->setPlantProfileTemplate(imageForProfiles->plantProfile[4]);
        else
            unitAddress[unitTotal]->setPlantProfileTemplate(imageForProfiles->plantProfile[0]);

        unitAddress[unitTotal]->setPlantName((QString)ownedUnits.at(names));

        qDebug() << unitAddress[unitTotal]->getMacAddress();
        qDebug() << unitAddress[unitTotal]->getPlantName();
        qDebug() << unitAddress[unitTotal]->unitPlantProfile->plantTypeName;

        ribbonAddress.append(new UnitRibbon(unitAddress[unitTotal], this));                                                                                    //Instance a new unit ribbon class
        ribbonAddress[unitTotal]->setRibbonNumber(unitTotal);

        itemAddress.append(new QListWidgetItem(ui->UnitList));                                                                                                 //Instance a new list widget item

        itemAddress[unitTotal]->setSizeHint(ribbonAddress[unitTotal]->size());                                                                                 //Let list widget item know about size of unit ribbon
        ui->UnitList->setItemWidget(itemAddress[unitTotal], ribbonAddress[unitTotal]);                                                                        //Set the unit ribbon in the list widget item
        ui->UnitList->addItem(itemAddress[unitTotal]);                                                                                                       //Add the item to the list

        connect(ribbonAddress[unitTotal]->ui->RibbonButton, SIGNAL(released()), unitAddress[unitTotal], SLOT(unitRibbonPressSlot()) );                          //Connect the unit ribbon button to the unitRibbonPressSlot of the unit class
        connect(ribbonAddress[unitTotal]->ui->ConfigureButton, SIGNAL(released()), unitAddress[unitTotal], SLOT(unitRibbonConfigureButtonPressSlot()) );       //Connect the unit ribbon's configure button to the unitRibbonConfigureButtonPressSlot of the unit class

        qDebug() << unitAddress[unitTotal]->unitPlantProfile->plantTypeName;

        ribbonAddress[unitTotal]->updateData();

        qDebug() << "Ribbon Name" << ribbonAddress[unitTotal]->ui->plantTypeLabel->text();

        unitWorkerAddress.append(new UnitWorker(unitAddress[unitTotal]));                                                                       //Instance a new worker for the unit
        unitThreadAddress.append(new QThread);                                                                                                 //Instance a new thread for the worker

        unitWorkerAddress[unitTotal]->moveToThread(unitThreadAddress[unitTotal]);                                                               //Move the unit's worker to the unit's thread

        connect(unitWorkerAddress[unitTotal], SIGNAL(error(QString)), this, SLOT(errorString(QString)));
        connect(unitThreadAddress[unitTotal], SIGNAL(started()), unitWorkerAddress[unitTotal], SLOT(process()));
        connect(unitWorkerAddress[unitTotal], SIGNAL(finished()), unitThreadAddress[unitTotal], SLOT(quit()));
        connect(unitWorkerAddress[unitTotal], SIGNAL(finished()), unitWorkerAddress[unitTotal], SLOT(deleteLater()));
        connect(unitThreadAddress[unitTotal], SIGNAL(finished()), unitThreadAddress[unitTotal], SLOT(deleteLater()));

        connect(unitWorkerAddress[unitTotal], SIGNAL(finishedSignal(int)), this, SLOT(threadFinishSlot(int)));
        connect(unitWorkerAddress[unitTotal], SIGNAL(finishedSignal(int)), this, SLOT(updateDatabaseSlot(int)));
        connect(unitWorkerAddress[unitTotal], SIGNAL(databaseDataRequest()), unitAddress[unitTotal], SLOT(dataRequestProcessSlot()));
        connect(unitWorkerAddress[unitTotal], SIGNAL(networkPostSignal(QNetworkRequest, QByteArray)), unitAddress[unitTotal], SLOT(threadNetworkPostSlot(QNetworkRequest, QByteArray)) );

        unitThreadAddress[unitTotal]->start();

        unitTotal += 1;
    }
}

void MainWindow::unknownMacProcessSlot(QString mac)
{
    qDebug() << "17";
    qDebug() << mac;
    
    qDebug() << ownedUnitsMacAddresses[0];
    ownedUnitsMacAddresses.append(mac);

    unitAddress.append(new BioBloomUnit(this));                                                                                                            //Instance a new unit class
    unitAddress[unitTotal]->setUnitNumber(unitTotal);
    unitAddress[unitTotal]->setMacAddress(mac);

    qDebug() << "18";

    unitAddress[unitTotal]->setPlantName("Unnamed");
    unitAddress[unitTotal]->setPlantProfileTemplate(imageForProfiles->plantProfile[0]);

    qDebug() << "19";

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
    
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));

    QUrl url;
    QByteArray postData;

    url.setUrl("http://192.168.5.1:80/personalise_plant.php");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    QString postKey = "mac";
    QString postValue = mac;
    QString postKey2 = "name";
    QString postValue2 = "Unnamed";
    QString postKey3 = "profile";
    QString postValue3 = imageForProfiles->plantProfile[0]->plantTypeName;

    postData.append(postKey).append("=").append(postValue).append("&").append(postKey2).append("=").append(postValue2).append("&").append(postKey3).append("=").append(postValue3).append("&");
    manager->post(request,postData);
    

    unitWorkerAddress.append(new UnitWorker(unitAddress[unitTotal]));                                                                       //Instance a new worker for the unit
    unitThreadAddress.append(new QThread);                                                                                                 //Instance a new thread for the worker

    unitWorkerAddress[unitTotal]->moveToThread(unitThreadAddress[unitTotal]);                                                               //Move the unit's worker to the unit's thread

    connect(unitWorkerAddress[unitTotal], SIGNAL(error(QString)), this, SLOT(errorString(QString)));
    connect(unitThreadAddress[unitTotal], SIGNAL(started()), unitWorkerAddress[unitTotal], SLOT(process()));
    connect(unitWorkerAddress[unitTotal], SIGNAL(finished()), unitThreadAddress[unitTotal], SLOT(quit()));
    connect(unitWorkerAddress[unitTotal], SIGNAL(finished()), unitWorkerAddress[unitTotal], SLOT(deleteLater()));
    connect(unitThreadAddress[unitTotal], SIGNAL(finished()), unitThreadAddress[unitTotal], SLOT(deleteLater()));

    connect(unitWorkerAddress[unitTotal], SIGNAL(finishedSignal(int)), this, SLOT(threadFinishSlot(int)));
    connect(unitWorkerAddress[unitTotal], SIGNAL(finishedSignal(int)), this, SLOT(updateDatabaseSlot(int)));
    connect(unitWorkerAddress[unitTotal], SIGNAL(databaseDataRequest()), unitAddress[unitTotal], SLOT(dataRequestProcessSlot()));
    connect(unitWorkerAddress[unitTotal], SIGNAL(networkPostSignal(QNetworkRequest, QByteArray)), unitAddress[unitTotal], SLOT(threadNetworkPostSlot(QNetworkRequest, QByteArray)) );

    unitThreadAddress[unitTotal]->start();

    unitTotal += 1;
}

void MainWindow::unknownMacFindFinishedSlot()
{
    qDebug() << "14";

    for(int i=0;i< unnamedMacAddresses.count();i++)
        for(int j=0;j< ownedUnitsMacAddresses.count();j++)
            if(unnamedMacAddresses[i]== ownedUnitsMacAddresses[j])
                return;

    qDebug() << "15";
    
    QString unknownMac; 

    if(!unnamedMacAddresses.isEmpty())
        unknownMac = (QString)unnamedMacAddresses.at(0);
    else
        return;
    
    qDebug() << "16";

        emit foundUnknownMac(unknownMac);
}

/*                         Class Methods                      */
void MainWindow::setupPushButtons()
{
    connect(ui->AddButton, SIGNAL(released()), this, SLOT(addButtonPressSlot()) );
        connect(this, SIGNAL(unknownMacFindFinished()), this, SLOT(unknownMacFindFinishedSlot()));
        connect(this, SIGNAL(foundUnknownMac(QString)), this, SLOT(unknownMacProcessSlot(QString)));
}

void MainWindow::unnamedMacsFinished(QNetworkReply* reply)
{
    qDebug() << "11";

    reply->deleteLater();
    QByteArray data_reply = reply->readAll();
    QString dataString(data_reply);
   QStringList points_list = dataString.split( "," );
   for(int i=0;i<points_list.count();i++)
   if(points_list[i].isEmpty())
   {
       points_list.takeAt(i);
   }

   qDebug() << "12";

   unnamedMacAddresses = points_list;

   qDebug() << "13";

   emit unknownMacFindFinished();
}

void MainWindow::loadPreexistingUnits()
{
    qDebug() << "1";

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(preexistingMacsFinished(QNetworkReply*)));

    QUrl url;
    QByteArray postData;
    url.setUrl("http://192.168.5.1:80/ribbon_boot.php");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    QString postKey = "pointless";
    QString postValue = "1";

    qDebug() << request.url();
    postData.append(postKey).append("=").append(postValue).append("&");
    manager->post(request,postData);

    qDebug() << "2";
}

void MainWindow::preexistingMacsFinished(QNetworkReply* reply)
{
    qDebug() << "4";

    reply->deleteLater();
    QByteArray data_reply = reply->readAll();
    QString dataString(data_reply);
   QStringList points_list = dataString.split( "," );
   QStringList macs_list;
   QString temp_macs;
   
   qDebug() << "2";
   
   for(int i=0;i<points_list.count();i++)
       if(points_list[i].isEmpty())
       {
           points_list.takeAt(i);
       }
   for(int i=0;i<points_list.count();i++)
       qDebug()<< points_list[i];

   qDebug() << "1";
   
   for (int i=0; i< points_list.count() ; i=i+3)
   {
       qDebug() << points_list[i];
       ownedUnitsMacAddresses.append(points_list[i]);
       macs_list << points_list[i];
    }

   ownedUnits = points_list;
   ownedUnitsMacAddresses = macs_list;
   replyImage = reply;

   qDebug() << "5";

   emit macFindFinished();
}
