/*      Define Header File      */
#ifndef BIOBLOOMUNIT_H
#define BIOBLOOMUNIT_H

/*      Library Classes         */
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QInputDialog>
#include <QDir>
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
    UnitWindow* windowAddress;                                 //Unit's personal window

    /*          Identity Accessor Methods           */
    int getUnitNumber();
    QString getMacAddress();
    QString getPlantName();
    QString getPlantType();

    /*          Reference Accessor Methods          */
    double getIdealTemp();
    double getIdealMoisture();
    double getIdealHumidity();

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
    void setIdealTemp(double inputTemp);
    void setIdealMoisture(double inputMoisture);
    void setIdealHumidity(double inputHumidity);

    /*          Data Mutator Methods                */
    void changeCurrentTemp(double inputTemp);
    void changeCurrentLight(double inputLight);
    void changeCurrentMoisture(double inputMoisture);
    void changeCurrentHumidity(double inputHumidity);

signals:

public slots:
    void unitRibbonPressSlot();
    void plantNamePressSlot();

private:
    /*              Identity Objects                */
    int unitNumber;
    QString macAddress;
    QString plantName;
    QString plantType;

    /*              Reference Objects               */
    double idealTemp;
    double idealMoisture;
    double idealHumidity;

    /*              Data Objects                    */
    double currentTemp;
    double currentLight;
    double currentMoisture;
    double currentHumidity;

    /*              Class Methods                   */

    /*
     * Data Request
     */

    /*
     * BatteryCheck, decides whether to flash battery level warning and QIcon on UnitRibbon or not
     * sends a 'battery low' sound file to pot
     */

    /*
     * Same as above but for water level
     */


};

#endif // BIOBLOOMUNIT_H
