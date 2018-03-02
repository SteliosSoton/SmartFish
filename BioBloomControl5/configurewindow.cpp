#include "configurewindow.h"
#include "ui_configurewindow.h"

ConfigureWindow::ConfigureWindow(QString unitMacAddress, BioBloomUnit* inputParentUnit, QWidget *parent) : QWidget(parent), ui(new Ui::ConfigureWindow), unitMacAddress(unitMacAddress)
{
    ui->setupUi(this);

    parentUnitImage = inputParentUnit;

    QPalette WindowPalette;                                                                         //Create a Palette
    WindowPalette.setColor(QPalette::Background, Qt::white);                                       //Configure the palette to fill the background with white
    this->setPalette(WindowPalette);                                                              //Set the palette

    setupPlantProfiles();
    setupComboBox();
}

ConfigureWindow::~ConfigureWindow()
{
    delete ui;
}

void ConfigureWindow::applyButtonPressSlot(QString plantName, QString plantProfile)
{

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));

    QUrl url;
    QByteArray postData;

    url.setUrl("http://192.168.5.1:80/personalise_plant.php");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    QString postKey = "mac";
    QString postValue = unitMacAddress;
    QString postKey2 = "name";
    QString postValue2 = plantName;
    QString postKey3 = "profile";
    QString postValue3 = plantProfile;

    postData.append(postKey).append("=").append(postValue).append("&").append(postKey2).append("=").append(postValue2).append("&").append(postKey3).append("=").append(postValue3).append("&");
    manager->post(request,postData);
}

void ConfigureWindow::setupPlantProfiles()
{
    /*      Default     */
    plantProfile.append(new PlantProfile("Default",24,70,60,45));

    /*      Cactus      */
    plantProfile.append(new PlantProfile("Aloe Cactus",26,65,35,45));

    /*   Spider Plant   */
    plantProfile.append(new PlantProfile("Spider Plant",22,65,60,45));

    /*    Peace Lily    */
    plantProfile.append(new PlantProfile("Peace Lily",24,65,60,50));

    /*  Venus Fly Trap  */
    plantProfile.append(new PlantProfile("Venus Fly Trap",27,65,75,60));
}

void ConfigureWindow::setupComboBox()
{
    ui->PlantTypeList->addItem("Please select plant type");
    ui->PlantTypeList->addItem("Default");
    ui->PlantTypeList->addItem("Aloe Cactus");
    ui->PlantTypeList->addItem("Spider Plant");
    ui->PlantTypeList->addItem("Peace Lily");
    ui->PlantTypeList->addItem("Venus Fly Trap");

    QObject::connect(ui->PlantTypeList, SIGNAL(currentIndexChanged(QString)), this, SLOT(plantTypeSelectionSlot(QString)));


}

void ConfigureWindow::plantTypeSelectionSlot(QString inputPlantType)
{
    if(inputPlantType == "Default")
        newPlantProfile = plantProfile[0];

    if(inputPlantType == "Aloe Cactus")
        newPlantProfile = plantProfile[1];

    if(inputPlantType == "Spider Plant")
        newPlantProfile = plantProfile[2];

    if(inputPlantType == "Peace Lily")
        newPlantProfile = plantProfile[3];

    if(inputPlantType == "Venus Fly Trap")
        newPlantProfile = plantProfile[4];

    else
        return;
}
