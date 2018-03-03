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

    void updateData();

        void potDataRequest();
        void databaseDataRequest();
        void batteryCheck();
        void waterLevelCheck();

    double receivedCurrentTemp;
    double receivedCurrentLight;
    double receivedCurrentMoisture;
    double receivedCurrentHumidity;

    int batteryLevel;
    int waterLevel;

signals:
    void finishedSignal(int);                //Passes unit number for the unit
    void networkPostSignal(QNetworkRequest outputRequest, QByteArray outputArray);
    void waterPlant();

public slots:
    void process();
    void waterPlantSlot();

private:
    BioBloomUnit* parentUnitAddress;

    void moistureCheck();
};

#endif // UNITWORKER_H
