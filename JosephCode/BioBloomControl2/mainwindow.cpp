/*                          Header File                         */
#include "mainwindow.h"
#include "ui_mainwindow.h"

/*                   Constructor and Destructor                 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPalette WindowPalette;                                                                     //Create a palette
    WindowPalette.setColor(QPalette::Background, Qt::white);                                   //Configure the palette to fill the background with white
    this->setPalette(WindowPalette);                                                          //Set the palette

    /*
     * Method connected to 'add a planter' that generates instances of BioBloomUnits and
     * adds their BioBloomButtons to a QScrollArea
     */

    exampleUnitAddress = new BioBloomUnit(this);        //instance example

    setupOtherWindows();
    setupPushButtons();

    UnitRibbon* exampleRibbonAddress = new UnitRibbon;
    QListWidgetItem* exampleItemAddress = new QListWidgetItem(ui->UnitList);
    exampleItemAddress->setSizeHint(exampleRibbonAddress->size());
    ui->UnitList->setItemWidget(exampleItemAddress, exampleRibbonAddress);
    ui->UnitList->addItem(exampleItemAddress);

    connect(ui->ExampleButton, SIGNAL(released()), exampleUnitAddress, SLOT(unitRibbonPressSlot()));

    //QListWidgetItem* exampleUnitQLWIAddress = new QListWidgetItem(tr("example"), ui->UnitList);

    //QListWidgetItem* exampleButtonAddress = new QListWidgetItem(tr("example"), ui->UnitList);

    //QPushButton* exampleButton = new QPushButton;

    //exampleUnitQLWIAddress->setSizeHint(ribbonAddresses[0]->sizeHint());

    ui->UnitList->setMovement(QListView::Free);
    //ui->UnitList->dragDropMode()QListView::Free);

    //ui->UnitList->setItemWidget(exampleUnitQLWIAddress, ribbonAddresses[0]);

    //ui->UnitList->addItem(exampleUnitQLWIAddress);

    //ui->UnitList->addItem(exampleButtonAddress);

    //ui->UnitList->setItemWidget(exampleButtonAddress, exampleButton);
}

MainWindow::~MainWindow()
{
    delete ui;
}


/*                          Member Slots                       */
void MainWindow::buttonPressSlot()
{

}

void MainWindow::addButtonPressSlot()
{
    addWindowAddress->show();
}

void MainWindow::settingsButtonPressSlot()
{
    settingsWindowAddress->show();
}

void MainWindow::unitAddedSlot()
{

}

/*                         Member Methods                      */
void MainWindow::setupOtherWindows()
{
    addWindowAddress = new AddWindow;
    settingsWindowAddress = new SettingsWindow;
}

void MainWindow::setupPushButtons()
{
    connect(ui->AddButton, SIGNAL(released()), this, SLOT(addButtonPressSlot()) );
    connect(ui->SettingsButton, SIGNAL(released()), this, SLOT(settingsButtonPressSlot()) );
    connect(ui->ExampleButton, SIGNAL(released()), exampleUnitAddress, SLOT(unitButtonPressSlot()) );
}
