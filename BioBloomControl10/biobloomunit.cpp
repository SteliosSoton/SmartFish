/*                  Header File                 */
#include "biobloomunit.h"
#include "ui_unitwindow.h"
#include "ui_configurewindow.h"

/*               Class Constructor              */
BioBloomUnit::BioBloomUnit(QObject *parent) : QObject(parent)
{
    windowAddress = new UnitWindow(this);
    configureWindowAddress = new ConfigureWindow(this);

    unitNetworkManagerAddress = new QNetworkAccessManager(this);

    disablePumpFlag = 0;

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

void BioBloomUnit::threadNetworkPostSlot(QNetworkRequest inputRequest, QByteArray inputArray)
{
    unitNetworkManagerAddress->post(inputRequest, inputArray);
}

void BioBloomUnit::dataRequestProcessSlot()
{
    
    qDebug() << "88";
    
    
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    
    connect(manager,
            SIGNAL(finished(QNetworkReply*)),
            this,
            SLOT(recentEntryFinished(QNetworkReply*)));
    
    QUrl url;
    QByteArray postData;


    url.setUrl("http://192.168.5.1:80/recent_entry.php");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");


    QString postKey = "mac";
    QString postValue = this->getMacAddress();

    postData.append(postKey).append("=").append(postValue).append("&");  
    manager->post(request, postData);
}

void BioBloomUnit::recentEntryFinished(QNetworkReply* reply)
{   
    qDebug() << "86";
    qDebug() <<"87";
    reply->deleteLater();
    QByteArray data_reply = reply->readAll();
    QString dataString(data_reply);
   QStringList points_list = dataString.split( "," );
   
   for(int i=0;i<points_list.count();i++)
       if(points_list[i].isEmpty())
       {
           points_list.takeAt(i);
       }
   
   
   double light_level = points_list[0].toDouble();
   double air_humidity = points_list[1].toDouble();
   double soil_moisture = points_list[2].toDouble();
   double temperature = points_list[3].toDouble();
   double water_level = points_list[4].toDouble();
   double battery_level = points_list[5].toDouble();
   
   qDebug() << light_level;
   qDebug() << air_humidity;
   qDebug() << soil_moisture;
   qDebug() << temperature;
   qDebug() << water_level;
   qDebug() << battery_level;
   
   receivedCurrentLight = (light_level/10);
   receivedCurrentHumidity = (air_humidity/10);
   receivedCurrentMoisture = (soil_moisture/10);
   receivedCurrentTemp = (temperature/10);
   waterLevel = (water_level/10);
   batteryLevel = (battery_level/10);
   
   qDebug() << "new values";
   
   qDebug() << receivedCurrentLight;
   qDebug() << receivedCurrentHumidity;
   qDebug() << receivedCurrentMoisture;
   qDebug() << receivedCurrentTemp;
   qDebug() << waterLevel;
   qDebug() << batteryLevel;
   
   this->changeCurrentTemp(receivedCurrentTemp);
   this->changeCurrentLight(receivedCurrentLight);
   this->changeCurrentMoisture(receivedCurrentMoisture);
   this->changeCurrentHumidity(receivedCurrentHumidity);
   
   batteryCheck();

   waterLevelCheck();
   
   moistureCheck();
   
   //QString nextTemp.setNum(receivedCurrentTemp);
   //QString nextLight.setNum(receivedCurrentTemp);
   //QString nextTemp.setNum(receivedCurrentTemp);
   //QString nextTemp.setNum(receivedCurrentTemp);
   
   //this->windowAddress->tempRibbonAddress->ui->dataNumber->setText()
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
    unitPlantProfile = new PlantProfile(inputPlantProfile->plantTypeName,
                                        inputPlantProfile->idealTemp,
                                        inputPlantProfile->idealLight,
                                        inputPlantProfile->idealMoisture,
                                        inputPlantProfile->idealHumidity);
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

void BioBloomUnit::moistureCheck()
{
    if(!(disablePumpFlag))
        if(receivedCurrentMoisture < unitPlantProfile->idealMoisture)
            emit waterPlant();
}

void BioBloomUnit::waterPlantSlot()
{
    QString actionID = "water";
    
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));
            
    QUrl url;
    QByteArray postData;

    url.setUrl("http://192.168.5.1:80/action_request.php");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    QString postKey = "mac";
    QString postKey2 = "id";

    postData.append(postKey).append("=").append(this->getMacAddress()).append("&").append(postKey2).append("=").append(actionID).append("&");

    manager->post(request, postData);
}

