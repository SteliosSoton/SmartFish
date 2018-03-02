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
    explicit UnitWorker(BioBloomUnit* inputUnit, QObject *parent = nullptr);
    ~UnitWorker();

    BioBloomUnit* inputUnitImageAddress;

    void process();
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

    bool batteryLevelLowFlag;
    bool batteryWarningGivenFlag;

    bool waterLevelLowFlag;
    bool waterLevelEmptyFlag;
    bool waterWarningGivenFlag;

    bool disablePumpFlag;

signals:
    finishedSignal(int);                //Passes unit number for the unit

public slots:

};

#endif // UNITWORKER_H
