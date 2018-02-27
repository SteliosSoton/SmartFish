#include "musicwindow.h"
#include "ui_musicwindow.h"

MusicWindow::MusicWindow(QWidget *parent) : QWidget(parent), ui(new Ui::MusicWindow)
{
    ui->setupUi(this);

    QPalette WindowPalette;                                                                 //Create a palette
    WindowPalette.setColor(QPalette::Background, Qt::white);                               //Configure the palette to fill the background with white
    this->setPalette(WindowPalette);                                                      //Set the palette

    setupPushButtonFunctions();
}

MusicWindow::~MusicWindow()
{
    delete ui;
}

void MusicWindow::backButtonPressSlot()
{
    this->close();
}

void MusicWindow::setupPushButtons()
{
}

void MusicWindow::setupPushButtonFunctions()
{
   connect(ui->BackButton, SIGNAL(released()), this, SLOT(backButtonPressSlot()) );
}
