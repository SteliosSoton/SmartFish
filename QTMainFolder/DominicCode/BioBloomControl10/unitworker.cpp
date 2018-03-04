#include "unitworker.h"
#include <qDebug>

UnitWorker::UnitWorker(BioBloomUnit* inputParentUnit, QObject *parent) : QObject(parent), parentUnitAddress(inputParentUnit)
{}

UnitWorker::~UnitWorker()
{}

/*              Class Thread            */
void UnitWorker::process()
{
    while(1)
    {
        QThread::msleep(50000);

        potDataRequest();

        qDebug() << "worker loop" << parentUnitAddress->getUnitNumber();

        QThread::msleep(10000);

        databaseDataRequest(); //NEEDS TO WRITE TO CURRENT DATA VALUES

        batteryCheck();

        waterLevelCheck();

        moistureCheck();

        updateData();

        emit finishedSignal(parentUnitAddress->getUnitNumber());        //Updates eveeerryyything

    }
}

/*              Class Methods              */
void UnitWorker::potDataRequest()
{
    connect(parentUnitAddress->unitNetworkManagerAddress,
            SIGNAL(finished(QNetworkReply*)),
            this, 
            SLOT(replyFinished(QNetworkReply*)));


    QUrl url;
    QByteArray postData;


    url.setUrl("http://192.168.5.1:80/data_request.php");


    QNetworkRequest request(url);


    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");


    QString postKey = "mac";


    QString postValue = parentUnitAddress->getMacAddress();

    postData.append(postKey).append("=").append(postValue).append("&");

    emit networkPostSignal(request, postData);
}

void UnitWorker::databaseDataRequest()
{

    connect(parentUnitAddress->unitNetworkManagerAddress,
            SIGNAL(finished(QNetworkReply*)),
            this,
            SLOT(replyFinished(QNetworkReply*)));


    QUrl url;
    QByteArray postData;


    url.setUrl("http://192.168.5.1:80/recent_entry.php");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");


    QString postKey = "mac";
    QString postValue = parentUnitAddress->getMacAddress();

    postData.append(postKey).append("=").append(postValue).append("&");

    emit networkPostSignal(request, postData);


      //returns comma seperated sensor values
     //i.e
    //light_level,39729,temperature,38938,soil_moisture,38387.....

}

void UnitWorker::batteryCheck()
{

    if(batteryLevel > 20)
    {
        parentUnitAddress->batteryLevelLowFlag = 0;
        parentUnitAddress->batteryWarningGivenFlag = 0;
    }


    if(batteryLevel <= 20)
    {
        parentUnitAddress->batteryLevelLowFlag = 1;

        if(parentUnitAddress->batteryWarningGivenFlag = 0)
            //shout warning

        parentUnitAddress->batteryWarningGivenFlag = 1;
    }

}

void UnitWorker::waterLevelCheck()
{

    if(waterLevel > 20)
    {
        parentUnitAddress->waterLevelLowFlag = 0;
        parentUnitAddress->waterWarningGivenFlag = 0;
        parentUnitAddress->disablePumpFlag = 0;
    }


    if(waterLevel <= 20)
    {
        parentUnitAddress->waterLevelLowFlag = 1;

        if(parentUnitAddress->waterWarningGivenFlag = 0)
            //shout warning

        parentUnitAddress->waterWarningGivenFlag = 1;
    }


    if(waterLevel <= 10)
    {
        parentUnitAddress->waterLevelEmptyFlag = 1;

        parentUnitAddress->disablePumpFlag = 1;
    }

}

void UnitWorker::moistureCheck()
{
    if(!(parentUnitAddress->disablePumpFlag))
        if(receivedCurrentMoisture < parentUnitAddress->unitPlantProfile->idealMoisture)
            emit waterPlant();
}

void UnitWorker::updateData()
{
    parentUnitAddress->changeCurrentTemp(receivedCurrentTemp);
    parentUnitAddress->changeCurrentLight(receivedCurrentLight);
    parentUnitAddress->changeCurrentMoisture(receivedCurrentMoisture);
    parentUnitAddress->changeCurrentHumidity(receivedCurrentHumidity);
}

/*                  Class Slots                 */
void UnitWorker::waterPlantSlot()
{
    QString actionID = "water";

    /*connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));
 */
    QUrl url;
    QByteArray postData;

    url.setUrl("http://192.168.5.1:80/action_request.php");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    QString postKey = "mac";
    QString postKey2 = "id";

    postData.append(postKey).append("=").append(parentUnitAddress->getMacAddress()).append("&").append(postKey2).append("=").append(actionID).append("&");

    emit networkPostSignal(request, postData);
}

void UnitWorker::getRecentFromDatabase()
{
    //emit networkPostSignal();

    /*
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));

    QUrl url;
    QByteArray postData;

    url.setUrl("http://192.168.5.1:80/recent_entry.php");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    QString postKey = "mac";





    postData.append(postKey).append("=").append(parentUnitAddress->getMacAddress()).append("&");
    manager->post(request,postData);

*/
}
