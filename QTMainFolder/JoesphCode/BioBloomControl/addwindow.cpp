#include "addwindow.h"
#include "ui_addwindow.h"

AddWindow::AddWindow(QWidget *parent) : QWidget(parent), ui(new Ui::AddWindow)
{
    ui->setupUi(this);

    QPalette WindowPalette;
    WindowPalette.setColor(QPalette::Background, Qt::white);
    this->setPalette(WindowPalette);
}

AddWindow::~AddWindow()
{
    delete ui;
}
