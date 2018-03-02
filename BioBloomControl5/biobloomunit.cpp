/*                  Header File                 */
#include "biobloomunit.h"
#include "ui_unitwindow.h"
#include "ui_configurewindow.h"

/*               Class Constructor              */
BioBloomUnit::BioBloomUnit(QObject *parent) : QObject(parent)
{
    windowAddress = new UnitWindow(macAddress);
    configureWindowAddress = new ConfigureWindow(macAddress, this);

    unitNetworkManagerAddress = new QNetworkAccessManager(this);

    setPlantName("Unnamed");

    connect(this->configureWindowAddress->ui->ApplyButton, SIGNAL(released()), this, SLOT(configureApplyButtonPressSlot()) );

}



/*               Class Slots                    */
void BioBloomUnit::unitRibbonPressSlot()
{
    windowAddress->show();
}

void BioBloomUnit::unitRibbonConfigureButtonPressSlot()
{
    configureWindowAddress->show();
}

void BioBloomUnit::configureApplyButtonPressSlot()
{
    setPlantName(configureWindowAddress->newUnitName);
    setPlantProfileTemplate(configureWindowAddress->newPlantProfile);
}

/*         Class Accessors and Mutators         */
int BioBloomUnit::getUnitNumber()                           //Identity Variable Accessors
{
    return unitNumber;
}

QString BioBloomUnit::getMacAddress()
{
    return macAddress;
}

QString BioBloomUnit::getPlantName()
{
    return plantName;
}

QString BioBloomUnit::getPlantType()
{
    return plantType;
}

int BioBloomUnit::getIdealTemp()                          //Reference Variable Accessors
{
    return idealTemp;
}

int BioBloomUnit::getIdealMoisture()
{
    return idealMoisture;
}

int BioBloomUnit::getIdealHumidity()
{
    return idealHumidity;
}

double BioBloomUnit::getCurrentTemp()                         //Data Variable Accessors
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

void BioBloomUnit::setUnitNumber(int inputUnitNumber)         //Identity Variable Mutators
{
    unitNumber = inputUnitNumber;
}

void BioBloomUnit::setMacAddress(QString inputMacAddress)
{
    macAddress = inputMacAddress;
}

void BioBloomUnit::setPlantName(QString inputPlantName)
{
    plantName = inputPlantName;
}

void BioBloomUnit::setPlantType(QString inputPlantType)
{
    plantType = inputPlantType;
}

void BioBloomUnit::setIdealTemp(int inputTemp)                //Reference Variable Mutators
{
    idealTemp = inputTemp;
}

void BioBloomUnit::setIdealMoisture(int inputMoisture)
{
    idealMoisture = inputMoisture;
}

void BioBloomUnit::setIdealHumidity(int inputHumidity)
{
    idealHumidity = inputHumidity;
}

void BioBloomUnit::changeCurrentTemp(double inputTemp)           //Data Variable Mutators
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



/*              Class Methods               */
void BioBloomUnit::setPlantProfileTemplate(PlantProfile* inputPlantProfile)
{
    setPlantType(inputPlantProfile->plantTypeName);
    setIdealTemp(inputPlantProfile->idealTemp);
    setIdealMoisture(inputPlantProfile->idealTemp);
    setIdealHumidity(inputPlantProfile->idealHumidity);
}

