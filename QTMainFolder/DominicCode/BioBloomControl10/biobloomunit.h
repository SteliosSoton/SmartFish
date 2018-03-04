/*      Define Header File      */
#ifndef BIOBLOOMUNIT_H
#define BIOBLOOMUNIT_H

/*      Library Classes         */
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QInputDialog>
#include <QDir>
#include <QUrl>
#include <QUrlQuery>
#include <QtNetwork\QNetworkAccessManager>

#include "unitwindow.h"
#include "unitribbon.h"
#include "configurewindow.h"
#include "plantprofile.h"

/*          Class Declarations          */
class UnitRibbon;
class UnitWindow;
class ConfigureWindow;
class PlantProfile;
class BioBloomUnit : public QObject
{
    Q_OBJECT

public:
    explicit BioBloomUnit(QObject *parent = nullptr);           //Constructor
    UnitWindow* windowAddress;                                 //Unit's personal window
    ConfigureWindow* configureWindowAddress;

    QNetworkAccessManager *unitNetworkManagerAddress;

    void setPlantProfileTemplate(PlantProfile* inputPlantProfile);
    PlantProfile* unitPlantProfile;

    bool batteryLevelLowFlag;
    bool batteryWarningGivenFlag;

    bool waterLevelLowFlag;
    bool waterLevelEmptyFlag;
    bool waterWarningGivenFlag;

    bool disablePumpFlag;

    /*          Identity Accessor Methods           */
    int getUnitNumber();
    QString getMacAddress();
    QString getPlantName();
    QString getPlantType();

    /*          Reference Accessor Methods          */
    int getIdealTemp();
    int getIdealMoisture();
    int getIdealHumidity();

    /*          Data Accessor Methods               */
    double getCurrentTemp();
    double getCurrentLight();
    double getCurrentMoisture();
    double getCurrentHumidity();

    /*          Identity Mutator Methods            */
    void setUnitNumber(int inputUnitNumber);
    void setMacAddress(QString inputMacAddress);
    void setPlantName(QString inputPlantName);
    void setPlantType(QString inputPlantType);

    /*          Reference Mutator Methods           */
    void setIdealTemp(int inputTemp);
    void setIdealMoisture(int inputMoisture);
    void setIdealHumidity(int inputHumidity);

    /*          Data Mutator Methods                */
    void changeCurrentTemp(double inputTemp);
    void changeCurrentLight(double inputLight);
    void changeCurrentMoisture(double inputMoisture);
    void changeCurrentHumidity(double inputHumidity);

public slots:
    void unitRibbonPressSlot();
    void unitRibbonConfigureButtonPressSlot();
    void threadNetworkPostSlot(QNetworkRequest inputRequest, QByteArray inputArray);

private:
    /*              Identity Objects                */
    int unitNumber;
    QString macAddress;
    QString plantName;
    QString plantType;

    /*              Reference Objects               */
    int idealTemp;
    int idealMoisture;
    int idealHumidity;

    /*              Data Objects                    */
    double currentTemp;
    double currentLight;
    double currentMoisture;
    double currentHumidity;
};

#endif // BIOBLOOMUNIT_H
