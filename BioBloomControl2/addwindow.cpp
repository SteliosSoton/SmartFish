#include "addwindow.h"
#include "ui_addwindow.h"

AddWindow::AddWindow(QWidget *parent) : QWidget(parent), ui(new Ui::AddWindow)
{
    ui->setupUi(this);

    QPalette WindowPalette;                                                             //Create a palette
    WindowPalette.setColor(QPalette::Background, Qt::white);                           //Configure the palette to fill the background with white
    this->setPalette(WindowPalette);                                                  //Set the palette
}

AddWindow::~AddWindow()
{
    delete ui;
}
