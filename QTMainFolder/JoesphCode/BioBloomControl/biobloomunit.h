/*      Define Header File      */
#ifndef BIOBLOOMUNIT_H
#define BIOBLOOMUNIT_H

/*      Library Classes         */
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include "unitwindow.h"
#include "unitribbon.h"

/*          Class Declarations          */
class UnitRibbon;
class UnitWindow;
class BioBloomUnit : public QObject
{
    Q_OBJECT

public:
    explicit BioBloomUnit(QObject *parent = nullptr);           //Constructor

    /*          Identity Accessor Methods           */
    int getUnitNumber();
    QString getPlantName();
    QString getPlantType();

    /*          Data Accessor Methods               */
    double getCurrentTemp();
    double getCurrentLight();
    double getCurrentMoisture();
    double getCurrentHumidity();

    /*          Identity Mutator Methods            */
    void setUnitNumber(int inputUnitNumber);
    void setPlantName(QString inputPlantName);
    void setPlantType(QString inputPlantType);

    /*          Data Mutator Methods                */
    void changeCurrentTemp(double inputTemp);
    void changeCurrentLight(double inputLight);
    void changeCurrentMoisture(double inputMoisture);
    void changeCurrentHumidity(double inputHumidity);

signals:

public slots:
    void unitRibbonPressSlot();

private:
    UnitWindow* windowAddress;                                  //Unit's personal window

    /*              Identity Objects                */
    int unitNumber;
    QString plantName;
    QString plantType;

    /*              Data Objects                    */
    double currentTemp;
    double currentLight;
    double currentMoisture;
    double currentHumidity;

    /*
     * BatteryCheck, decides whether to flash battery level warning and QIcon on UnitRibbon or not
     * sends a 'battery low' sound file to pot
     */

    /*
     * Same as above but for water level
     */


};

#endif // BIOBLOOMUNIT_H
