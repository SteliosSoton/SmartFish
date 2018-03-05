#ifndef UNITWORKER_H
#define UNITWORKER_H

#include <QObject>
#include <QtNetwork\QNetworkAccessManager>

#include "biobloomunit.h"

class BioBloomUnit;
class UnitWorker : public QObject
{
    Q_OBJECT

public:
    explicit UnitWorker(BioBloomUnit* inputParentUnit, QObject *parent = nullptr);
    ~UnitWorker();
    
    
    void potDataRequest();

signals:
    void finishedSignal(int);                //Passes unit number for the unit
    void networkPostSignal(QNetworkRequest outputRequest, QByteArray outputArray);
    void databaseDataRequest();

public slots:
    void process();

private:
    BioBloomUnit* parentUnitAddress;

};

#endif // UNITWORKER_H
