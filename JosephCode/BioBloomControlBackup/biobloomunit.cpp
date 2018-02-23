/*                  Header File                 */
#include "biobloomunit.h"

/*               Class Constructor              */
BioBloomUnit::BioBloomUnit(QObject *parent) : QObject(parent)
{
    windowAddress = new UnitWindow;
}

/*               Class Slots                    */
void BioBloomUnit::unitRibbonPressSlot()
{
    windowAddress->show();
}

/*         Class Accessors and Mutators         */
int BioBloomUnit::getUnitNumber()
{
    return unitNumber;
}

QString BioBloomUnit::getPlantName()
{
    return plantName;
}

QString BioBloomUnit::getPlantType()
{
    return plantType;
}

double BioBloomUnit::getCurrentTemp()
{
    return currentTemp;
}

double BioBloomUnit::getCurrentLight()
{
    return currentLight;
}

double BioBloomUnit::getCurrentMoisture()
{
    return currentMoisture;
}

double BioBloomUnit::getCurrentHumidity()
{
    return currentHumidity;
}

void BioBloomUnit::setUnitNumber(int inputUnitNumber)
{
    unitNumber = inputUnitNumber;
}

void BioBloomUnit::setPlantName(QString inputPlantName)
{
    plantName = inputPlantName;
}

void BioBloomUnit::setPlantType(QString inputPlantType)
{
    plantType = inputPlantType;
}

void BioBloomUnit::changeCurrentTemp(double inputTemp)
{
    currentTemp = inputTemp;
}

void BioBloomUnit::changeCurrentLight(double inputLight)
{
    currentLight = inputLight;
}

void BioBloomUnit::changeCurrentMoisture(double inputMoisture)
{
    currentMoisture = inputMoisture;
}

void BioBloomUnit::changeCurrentHumidity(double inputHumidity)
{
    currentHumidity = inputHumidity;
}
