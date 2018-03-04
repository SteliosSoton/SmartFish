/*      Header Files        */
#include "unitwindow.h"
#include "ui_unitwindow.h"
#include "ui_dataribbon.h"

/*              Constructor and Destructor          */
UnitWindow::UnitWindow(BioBloomUnit *inputParentUnit, QWidget *parent) : QWidget(parent), ui(new Ui::UnitWindow), parentUnitAddress(inputParentUnit)
{
    ui->setupUi(this);                                                                              //Setup UI

    QPalette WindowPalette;                                                                         //Create a Palette
    WindowPalette.setColor(QPalette::Background, Qt::white);                                       //Configure the palette to fill the background with white
    this->setPalette(WindowPalette);                                                              //Set the palette

    setupOtherWindows();
    setupDataDisplay();
    setupPushButtonFunctions();
}

UnitWindow::~UnitWindow()
{
    delete ui;
}

/*              Class Method Definitions            */
void UnitWindow::setupOtherWindows()
{
    musicWindowAddress = new MusicWindow(parentUnitAddress);
    settingsWindowAddress = new SettingsWindow(parentUnitAddress);
}

void UnitWindow::setupDataDisplay()
{
    tempRibbonAddress = new DataRibbon(parentUnitAddress);
    lightRibbonAddress = new DataRibbon(parentUnitAddress);
    moistureRibbonAddress = new DataRibbon(parentUnitAddress);
    humidityRibbonAddress = new DataRibbon(parentUnitAddress);

    ui->DataList->clear();

    QListWidgetItem* tempItemAddress = new QListWidgetItem(ui->DataList);
    tempItemAddress->setSizeHint(tempRibbonAddress->size());
    ui->DataList->setItemWidget(tempItemAddress, tempRibbonAddress);
    ui->DataList->insertItem(0, tempItemAddress);

    tempRibbonAddress->setDataTitle("<font color = 'Red'> Temperature </font>");

    QListWidgetItem* lightItemAddress = new QListWidgetItem(ui->DataList);
    lightItemAddress->setSizeHint(lightRibbonAddress->size());
    ui->DataList->setItemWidget(lightItemAddress, lightRibbonAddress);
    ui->DataList->insertItem(1, lightItemAddress);

    lightRibbonAddress->setDataTitle("<font color = 'Orange'> Light </font>");

    QListWidgetItem* moistureItemAddress = new QListWidgetItem(ui->DataList);
    moistureItemAddress->setSizeHint(moistureRibbonAddress->size());
    ui->DataList->setItemWidget(moistureItemAddress, moistureRibbonAddress);
    ui->DataList->insertItem(2, moistureItemAddress);

    moistureRibbonAddress->setDataTitle("<font color = 'Light Green'>Moisture</font>");

    QListWidgetItem* humidityItemAddress = new QListWidgetItem(ui->DataList);
    humidityItemAddress->setSizeHint(humidityRibbonAddress->size());
    ui->DataList->setItemWidget(humidityItemAddress, humidityRibbonAddress);
    ui->DataList->insertItem(3, humidityItemAddress);

    humidityRibbonAddress->setDataTitle("<font color = 'Light Blue'>Humidity</font>");
}

void UnitWindow::setupPushButtonFunctions()
{
    connect(ui->BackButton, SIGNAL(released()), this, SLOT(backButtonPressSlot()) );
    connect(ui->MusicButton, SIGNAL(released()), this, SLOT(musicButtonPressSlot()) );
    connect(ui->SettingsButton, SIGNAL(released()), this, SLOT(settingsButtonPressSlot()) );

    connect(tempRibbonAddress->ui->RibbonButton, SIGNAL(released()), this, SLOT(tempRibbonPressSlot()) );
    connect(lightRibbonAddress->ui->RibbonButton, SIGNAL(released()), this, SLOT(lightRibbonPressSlot()) );
    connect(moistureRibbonAddress->ui->RibbonButton, SIGNAL(released()), this, SLOT(moistureRibbonPressSlot()) );
    connect(humidityRibbonAddress->ui->RibbonButton, SIGNAL(released()), this, SLOT(humidityRibbonPressSlot()) );
}

void UnitWindow::updateData()
{
    ui->PlantName->setText(parentUnitAddress->getPlantName());
}

/*              Class Slot Definitions              */
void UnitWindow::backButtonPressSlot()
{
    this->close();
}

void UnitWindow::musicButtonPressSlot()
{
    musicWindowAddress->show();
}

void UnitWindow::settingsButtonPressSlot()
{
    settingsWindowAddress->show();
}

void UnitWindow::tempRibbonPressSlot()
{
    graphAddress = new GraphDisplay("temperature", 28, this);

    //put graph in place
    graphAddress->setGeometry(210, 70, 440, 400);
    graphAddress->setIdeal(parentUnitAddress->unitPlantProfile->idealTemp);
    graphAddress->addPoint(QDateTime().currentDateTime(), 1);
    graphAddress->show();

    //int i=0;
    /*while (i<10) {//create test values over 5seconds
       // printf("in while loop\n");
        Sleep(500);
        graphAddress->addPoint(QDateTime().currentDateTime(), (rand()%100));
        //printf("appended value \n");

        i++;
    }*/
}

void UnitWindow::lightRibbonPressSlot()
{
    graphAddress = new GraphDisplay("light", 70, this);

    //put graph in place
    graphAddress->setGeometry(210, 70, 440, 400);
    graphAddress->setIdeal(parentUnitAddress->unitPlantProfile->idealLight);
    graphAddress->addPoint(QDateTime().currentDateTime(), 1);
    graphAddress->show();

    //int i=0;
    /*while (i<10) {//create test values over 5seconds
       // printf("in while loop\n");
        Sleep(500);
        graphAddress->addPoint(QDateTime().currentDateTime(), (rand()%100));
        //printf("appended value \n");

        i++;
    }*/
}

void UnitWindow::moistureRibbonPressSlot()
{
    graphAddress = new GraphDisplay("moisture", 70, this);

    //put graph in place
    graphAddress->setGeometry(210, 70, 440, 400);
    graphAddress->setIdeal(parentUnitAddress->unitPlantProfile->idealMoisture);
    graphAddress->addPoint(QDateTime().currentDateTime(), 1);
    graphAddress->show();

    //int i=0;
    /*while (i<10) {//create test values over 5seconds
       // printf("in while loop\n");
        Sleep(500);
        graphAddress->addPoint(QDateTime().currentDateTime(), (rand()%100));
        //printf("appended value \n");

        i++;
    }*/
}

void UnitWindow::humidityRibbonPressSlot()
{
    graphAddress = new GraphDisplay("humidity", 70, this);

    //put graph in place
    graphAddress->setGeometry(210, 70, 440, 400);
    graphAddress->setIdeal(parentUnitAddress->unitPlantProfile->idealHumidity);
    graphAddress->addPoint(QDateTime().currentDateTime(), 1);
    graphAddress->show();

   // int i=0;
    /*while (i<10) {//create test values over 5seconds
       // printf("in while loop\n");
        Sleep(500);
        graphAddress->addPoint(QDateTime().currentDateTime(), (rand()%100));
        //printf("appended value \n");

        i++;
    }*/
}

