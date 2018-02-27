/*                  Header File                 */
#include "biobloomunit.h"
#include "ui_unitwindow.h"

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

void BioBloomUnit::plantNamePressSlot()
{
    QInputDialog* PlantNameInputWindow = new QInputDialog;

    QPalette WindowPalette;                                                                         //Create a Palette
    WindowPalette.setColor(QPalette::Background, Qt::white);                                       //Configure the palette to fill the background with white
    PlantNameInputWindow->setPalette(WindowPalette);                                              //Set the palette

    QString newPlantName = PlantNameInputWindow->getText(this,
                                                         tr("Plant Name"),
                                                         tr("New Plant Name:"),
                                                         QLineEdit::Normal,
                                                         QDir::home().dirName(),
                                                         &ok);

    if(ok && !newPlantName.isEmpty())
        this->setPlantName(newPlantName);
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

double BioBloomUnit::getIdealTemp()                          //Reference Variable Accessors
{
    return idealTemp;
}

double BioBloomUnit::getIdealMoisture()
{
    return idealMoisture;
}

double BioBloomUnit::getIdealHumidity()
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

void BioBloomUnit::setIdealTemp(double inputTemp)               //Reference Variable Mutators
{
    idealTemp = inputTemp;
}

void BioBloomUnit::setIdealMoisture(double inputMoisture)
{
    idealMoisture = inputMoisture;
}

void BioBloomUnit::setIdealHumidity(double inputHumidity)
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
