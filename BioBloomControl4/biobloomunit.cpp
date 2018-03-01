dz/*                  Header File                 */
#include "biobloomunit.h"
#include "ui_unitwindow.h"
#include "ui_configurewindow.h"

/*               Class Constructor              */
BioBloomUnit::BioBloomUnit(QObject *parent) : QObject(parent)
{
    windowAddress = new UnitWindow(macAddress);
    configureWindowAddress = new ConfigureWindow(macAddress, this);

    setPlantName("Unnamed");

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



/*         Class Methods                     */
void BioBloomUnit::dataUpdate()
{
    potDataRequest();



}

void BioBloomUnit::potDataRequest()
{


    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));

    QUrl url;
    QByteArray postData;

    url.setUrl("http://192.168.5.1:80/data_request.php");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    QString postKey = "mac";
    QString postValue = this->macAddress;

    postData.append(postKey).append("=").append(postValue).append("&");
    manager->post(request,postData);



}

void BioBloomUnit::databaseDataRequest()
{

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));

    QUrl url;
    QByteArray postData;

    url.setUrl("http://192.168.5.1:80/recent_entry.php");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    QString postKey = "mac";
    QString postValue = this->macAddress;

    postData.append(postKey).append("=").append(postValue).append("&");
    manager->post(request,postData);

    //returns comma seperated sensor values
    //i.e
    //light_level,39729,temperature,38938,soil_moisture,38387.....

}

void BioBloomUnit::batteryCheck()
{

    if(batteryLevel > 20)
    {
        batteryLevelLowFlag = 0;
        batteryWarningGivenFlag = 0;
    }


    if(batteryLevel <= 20)
    {
        batteryLevelLowFlag = 1;

        if(batteryWarningGivenFlag = 0)
            //shout warning

        batteryWarningGivenFlag = 1;
    }

}

void BioBloomUnit::waterLevelCheck()
{

    if(waterLevel > 20)
    {
        waterLevelLowFlag = 0;
        waterWarningGivenFlag = 0;
        disablePumpFlag = 0;
    }


    if(waterLevel <= 20)
    {
        waterLevelLowFlag = 1;

        if(waterWarningGivenFlag = 0)
            //shout warning

        waterWarningGivenFlag = 1;
    }


    if(waterLevel <= 10)
    {
        waterLevelEmptyFlag = 1;

        disablePumpFlag = 1;
    }

}

void BioBloomUnit::plantProfileTemplate(PlantProfile* inputPlantProfile)
{
    setPlantType(inputPlantProfile->plantTypeName);
    setIdealTemp(inputPlantProfile->idealTemp);
    setIdealMoisture(inputPlantProfile->idealTemp);
    setIdealHumidity(inputPlantProfile->idealHumidity);
}

