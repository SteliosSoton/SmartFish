/*                          Header File                         */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_unitribbon.h"

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

    setupOtherWindows();
    setupPushButtons();

    unitTotal = 0;
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
    //addWindowAddress->show();

    unitAddress.append(new BioBloomUnit(this));                                                                                             //Instance a new unit class
    ribbonAddress.append(new UnitRibbon(this));                                                                                            //Instance a new unit ribbon class
    itemAddress.append(new QListWidgetItem(ui->UnitList));                                                                                //Instance a new list widget item

    itemAddress[unitTotal]->setSizeHint(ribbonAddress[unitTotal]->size());                                                                  //Let list widget item know about size of unit ribbon
    ui->UnitList->setItemWidget(itemAddress[unitTotal], ribbonAddress[unitTotal]);                                                         //Set the unit ribbon in the list widget item
    ui->UnitList->addItem(itemAddress[unitTotal]);                                                                                        //Add the item to the list

    connect(ribbonAddress[unitTotal]->ui->RibbonButton, SIGNAL(released()), unitAddress[unitTotal], SLOT(unitRibbonPressSlot()) );          //Connect the unit ribbon button to the unitRibbonPressSlot of the unit class

    unitTotal += 1;                                                                                                                         //Increment the number of units on the system by 1
}

void MainWindow::unitAddedSlot()
{

}

/*                         Member Methods                      */
void MainWindow::setupOtherWindows()
{
    addWindowAddress = new AddWindow;
}

void MainWindow::setupPushButtons()
{
    connect(ui->AddButton, SIGNAL(released()), this, SLOT(addButtonPressSlot()) );
}
