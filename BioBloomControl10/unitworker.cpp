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
        QThread::msleep(1000);

        potDataRequest();

        qDebug() << "worker loop" << parentUnitAddress->getUnitNumber();

        QThread::msleep(5000);
        
        emit databaseDataRequest();
        
        QThread::msleep(5000);

        emit finishedSignal(parentUnitAddress->getUnitNumber());        //Updates eveeerryyything

        QThread::msleep(49000);

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
