#include "unitworker.h"

UnitWorker::UnitWorker(BioBloomUnit* inputUnit, QObject *parent) : QObject(parent)
{
    inputUnitImageAddress = inputUnit;
}

UnitWorker::~UnitWorker()
{}

void UnitWorker::process()
{
    potDataRequest();

    QThread::msleep(10000);

    databaseDataRequest();

    batteryCheck();

    waterLevelCheck();
    
    finishedSignal();
}

/*              Class Methods              */
void UnitWorker::potDataRequest()
{
    connect(inputUnitImageAddress->unitNetworkManagerAddress, 
            SIGNAL(finished(QNetworkReply*)),
            this, 
            SLOT(replyFinished(QNetworkReply*)));

    QUrl url;
    QByteArray postData;

    url.setUrl("http://192.168.5.1:80/data_request.php");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    QString postKey = "mac";
    QString postValue = inputUnitImageAddress->getMacAddress();

    postData.append(postKey).append("=").append(postValue).append("&");
    inputUnitImageAddress->unitNetworkManagerAddress->post(request,postData);
}

void UnitWorker::databaseDataRequest()
{
    connect(inputUnitImageAddress->unitNetworkManagerAddress,
            SIGNAL(finished(QNetworkReply*)),
            this,
            SLOT(replyFinished(QNetworkReply*)));

    QUrl url;
    QByteArray postData;

    url.setUrl("http://192.168.5.1:80/recent_entry.php");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    QString postKey = "mac";
    QString postValue = inputUnitImageAddress->getMacAddress();

    postData.append(postKey).append("=").append(postValue).append("&");
    inputUnitImageAddress->unitNetworkManagerAddress->post(request,postData);

      //returns comma seperated sensor values
     //i.e
    //light_level,39729,temperature,38938,soil_moisture,38387.....

}

void UnitWorker::batteryCheck()
{

    if(batteryLevel > 20)
    {
        batteryLevelLowFlag = 0;
        batteryWarningGivenFlag = 0;
    }


    if(batteryLevel <= 20)
    {
        batteryLevelLowFlag = 1;

        if(batteryWarningGivenFlag = 0)
            //shout warning

        batteryWarningGivenFlag = 1;
    }

}

void UnitWorker::waterLevelCheck()
{

    if(waterLevel > 20)
    {
        waterLevelLowFlag = 0;
        waterWarningGivenFlag = 0;
        disablePumpFlag = 0;
    }


    if(waterLevel <= 20)
    {
        waterLevelLowFlag = 1;

        if(waterWarningGivenFlag = 0)
            //shout warning

        waterWarningGivenFlag = 1;
    }


    if(waterLevel <= 10)
    {
        waterLevelEmptyFlag = 1;

        disablePumpFlag = 1;
    }

}
