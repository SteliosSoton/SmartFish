/*      Header Files        */
#include "unitwindow.h"
#include "ui_unitwindow.h"
#include "ui_dataribbon.h"

/*              Constructor and Destructor          */
UnitWindow::UnitWindow(QWidget *parent) : QWidget(parent), ui(new Ui::UnitWindow)
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
    musicWindowAddress = new MusicWindow;
    settingsWindowAddress = new SettingsWindow;
}

void UnitWindow::setupDataDisplay()
{
    tempRibbonAddress = new DataRibbon;
    lightRibbonAddress = new DataRibbon;
    moistureRibbonAddress = new DataRibbon;
    humidityRibbonAddress = new DataRibbon;

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

    //connect(tempRibbonAddress->ui->RibbonButton, SIGNAL(released()), DomGraph, SLOT(tempRibbonPressSlot()) );
    //connect(lightRibbonAddress, SIGNAL(released()), GraphDom, SLOT(lightRibbonPressSlot()) );
    //connect(moistureRibbonAddress, SIGNAL(released()), GraphOfDom, SLOT(moistureRibbonPressSlot()) );
    //connect(humidityRibbonAddress, SIGNAL(released()), KeepOftheGraph, SLOT(humidityRibbonPressSlot()) );
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

void UnitWindow::tempButtonPressSlot()
{

}

void UnitWindow::lightButtonPressSlot()
{

}

void UnitWindow::moitureButtonPressSlot()
{

}

void UnitWindow::humidityButtonPressSlot()
{

}

