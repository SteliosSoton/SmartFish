#include "settingswindow.h"
#include "ui_settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent) : QWidget(parent), ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);

    QPalette WindowPalette;                                                                     //Create a palette
    WindowPalette.setColor(QPalette::Background, Qt::white);                                   //Configure the palette to fill the background with white
    this->setPalette(WindowPalette);                                                          //Set the palette

    setupPushButtons();
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}


void SettingsWindow::backButtonPressSlot()
{
    this->close();
}

void SettingsWindow::muteButtonPressSlot()
{
    //Interfaces with matt's classes
}

void SettingsWindow::RGBControlButtonPressSlot()
{
    //Interfaces with matt's classes
}

void SettingsWindow::toggleLEDButtonPressSlot()
{
    //Interfaces with matt's classes
}

void SettingsWindow::toggleWaterButtonPressSlot()
{
    //Interfaces with matt's classes
}

/*              Member Methods                  */
void SettingsWindow::setupPushButtons()
{
    connect(ui->BackButton, SIGNAL(released()), this, SLOT(backButtonPressSlot()));
}
