/*      Header Files        */
#include "unitwindow.h"
#include "ui_unitwindow.h"

/*              Constructor and Destructor          */
UnitWindow::UnitWindow(QWidget *parent) : QWidget(parent), ui(new Ui::UnitWindow)
{
    ui->setupUi(this);                                                                              //Setup UI

    QPalette WindowPalette;                                                                         //Create a palette
    WindowPalette.setColor(QPalette::Background, Qt::white);                                       //Configure the palette to fill the background with white
    this->setPalette(WindowPalette);                                                              //Set the palette

    musicWindowAddress = new MusicWindow;

    setupPushButtons();
    setupPushButtonFunctions();
}

UnitWindow::~UnitWindow()
{
    delete ui;
}

/*              Class Method Definitions            */
void UnitWindow::setupPushButtons()
{
}

void UnitWindow::setupPushButtonFunctions()
{
    connect(ui->BackButton, SIGNAL(released()), this, SLOT(backButtonPressSlot()) );
    connect(ui->MusicButton, SIGNAL(released()), this, SLOT(musicButtonPressSlot()) );
}

void UnitWindow::backButtonPressSlot()
{
    this->close();
}

void UnitWindow::musicButtonPressSlot()
{
    musicWindowAddress->show();
}
